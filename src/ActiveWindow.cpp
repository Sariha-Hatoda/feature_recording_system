//
//  ActiveWindow.cpp
//  CGActiveWindow1-0
//
//  Created by Tadashi Ohara on 2022/04/30.
//

#include "ActiveWindow.hpp"

void ActiveWindow::init(){
    winchanged = 0;
    for(auto& p : AW_Count){
        p.second = 0;
    }
    isFirst = true;
}

void ActiveWindow::update(){
    //ウィンドウリストをCFArrayRef形式で取得．
    CFArrayRef windowList = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly| kCGWindowListExcludeDesktopElements, kCGNullWindowID);

    //CFArrayGetCountで配列の要素数を取得し，配列の要素を1つずつ参照．
    for (int i = 0; i < CFArrayGetCount(windowList); i++) {

        //ウィンドウリスト内の指定した要素を抽出(インデックスはループカウンタ)
        CFDictionaryRef winInfo = (CFDictionaryRef)CFArrayGetValueAtIndex(windowList, i);

        //ウィンドウのレイヤ(重なりの何番目か)をCFNumberRef形式で取得
        int layer;
        CFNumberRef windowLayerRef = (CFNumberRef)CFDictionaryGetValue(winInfo, kCGWindowLayer);

        //int型にコンバート
        CFNumberGetValue(windowLayerRef, kCFNumberIntType, &layer);

        //アプリの名称をCFStringRef形式で取得
        CFStringRef label = (CFStringRef)CFDictionaryGetValue(winInfo, kCGWindowOwnerName);

        //アプリ名を含んだ配列の長さ
        CFIndex strsize = CFStringGetLength(label);

        char buf[S_SIZE];
        //エンコードできたかどうかを判定
        bool isEncoded= CFStringGetCString(label, buf, S_SIZE, kCFStringEncodingUTF8);
        winname = (string)buf;

        //最前面のアプリかつエンコードに成功した場合，
        if(layer==0&&isEncoded==true){

            //リストに見つからなかったAWの場合，0で初期化
            if(AW_Count.find(winname) == AW_Count.end()){
                AW_Count[winname] = 0;
            }
            //見つかった場合，フレームごとにカウントアップ
            else{
                AW_Count[winname]++;
            }
            //最初の実行なら，フラグをfalseにして終了
            if(isFirst){
                isFirst = false;
            }
            //2回目以降の実行かつウィンドウ名称が一致していない場合，ウィンドウ変化回数をカウントアップ
            else if(winname!=winnameold){
                winchanged++;
            }
            //古いウィンドウ名称を更新
            winnameold = winname;
            break;
        }
    }
}

//リストの全要素を0でクリア
void ActiveWindow::clear(){
    winchanged = 0;
    for(auto& p : AW_Count){
        p.second = 0;
    }
}

void ActiveWindow::show(){
    for(const auto& p : AW_Count){
        cout << p.first << ":" << p.second << endl;
        cout << "changed:" << winchanged << endl;
    }
}
