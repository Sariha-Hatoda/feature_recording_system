//
//  MouseEventData.cpp
//  CGMouseEvents1-0
//
//  Created by Tadashi Ohara on 2022/04/26.
//

#include "MouseEventData.hpp"
//初期化メソッド(コンストラクタ)
void MouseEventData::init(){
    //カーソル座標と初回実行判定用のフラグのみ初期化
    cursor.x = 0.0;
    cursor.y = 0.0;
    isFirst = true;
}

//イベント発生時の更新処理
void MouseEventData::update(CGEventRef event, CGEventType type){
    //発生したイベント種別に回数をカウントアップ
    for ( int i=0; i<MOUSE_EVENT_NUM; i++) {
        if(EoI[i]==type){
            EventCount[EoIStr[i]]++;
            //cout<<EoIStr[i]<<":"<<EventCount[EoIStr[i]]<<endl;
        }
    }
    //初回の実行の場合，カーソル座標をイベントの座標と同期しフラグを下ろす
    if (isFirst) {
        isFirst = false;
    }
    //そうでない場合，移動量を算出
    else{
        float diffX,diffY;
        CGPoint cursornow;
        cursornow = CGEventGetLocation(event);
        diffX = cursornow.x -cursor.x;
        diffY = cursornow.y -cursor.y;
        cursor_moved += diffX*diffX + diffY*diffY;
        //cout<<"cursor_moved:"<<cursor_moved<<endl;
    }
    cursor = CGEventGetLocation(event);
}
void MouseEventData::clear(){
    //辞書方配列のキーと値をそれぞれ初期化(値は全て0)
    for (int i=0; i<MOUSE_EVENT_NUM; i++) {
        EventCount[EoIStr[i]]=0;
    }
    //移動量を初期化
    cursor_moved = 0.0;
}

void MouseEventData::show(){
    cout<<"cursor:"<<cursor.x<<","<<cursor.y<<endl;
    cout<<"flag:"<<isFirst<<endl;
    cout<<"cursor_moved:"<<cursor_moved<<endl;
    for ( int i=0; i<MOUSE_EVENT_NUM; i++) {
        cout<<EoIStr[i]<<":\t\t"<<EventCount[EoIStr[i]]<<endl;
    }
}
