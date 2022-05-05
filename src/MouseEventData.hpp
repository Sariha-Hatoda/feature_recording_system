//
//  MouseEventData.hpp
//  CGMouseEvents1-0
//
//  Created by Tadashi Ohara on 2022/04/26.
//

#ifndef MouseEventData_hpp
#define MouseEventData_hpp

#include "ofMain.h"
#define MOUSE_EVENT_NUM 11

class MouseEventData{
    public:
        //カーソル座標の初期化メソッド(コンストラクタ)
        void init(void);
        //イベント発生時の更新処理
        void update(CGEventRef event, CGEventType type);
        //移動量とイベント発生回数の初期化メソッド(指定時刻が経過するたびに呼び出す)
        void clear(void);
    
        //クラス内部を可視化するメソッド
        void show(int x, int y);

        //イベントの座標
        CGPoint cursor;
        //移動量の格納用
        float cursor_moved;
        
        //最初の実行かどうかを判断する論理変数
        bool isFirst;

        //イベント番号を格納
        unsigned int eventNo;
    
        //監視するイベントの列挙
    CGEventType EoI[MOUSE_EVENT_NUM]={
        kCGEventMouseMoved,
        kCGEventLeftMouseDown,
        kCGEventLeftMouseUp,
        kCGEventLeftMouseDragged,
        kCGEventRightMouseDown,
        kCGEventRightMouseUp,
        kCGEventRightMouseDragged,
        kCGEventOtherMouseDown,
        kCGEventOtherMouseUp,
        kCGEventOtherMouseDragged,
        kCGEventScrollWheel,
    };
    //string型のイベント名
    string EoIStr[MOUSE_EVENT_NUM]={
        "MouseMoved"       ,
        "LeftMouseDown"    ,
        "LeftMouseUp"      ,
        "LeftMouseDragged" ,
        "RightMouseDown"   ,
        "RightMouseUp"     ,
        "RightMouseDragged",
        "OtherMouseDown"   ,
        "OtherMouseUp"     ,
        "OtherMouseDragged",
        "ScrollWheel"      ,
    };
    //string-intの辞書型配列
    unordered_map<string, unsigned int> EventCount;
};

#endif /* MouseEventData_hpp */
