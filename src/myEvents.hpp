//
//  myEvents.hpp
//  integrated_events
//
//  Created by Tadashi Ohara on 2022/05/03.
//

#ifndef myEvents_hpp
#define myEvents_hpp

#include "ofMain.h"
#include "MouseEventData.hpp"
#include "KeyEventData.hpp"
class myEvents{
public:
    void init();
    void clear();
    void show();

    //イベントマスク
    CGEventMask Key_eventMask, Mouse_eventMask;

    //ランループの参照
    CFRunLoopRef rlref;

    //ランループのモード
    CFRunLoopMode mode;

    //イベントのタッピングポイント
    CGEventTapLocation ETloc;

    //イベントフラグ
    CGEventFlags flags;

    //キーイベントのクラス
    KeyEventData key_data;

    //マウスイベントのクラス
    MouseEventData mouse_data;

    //マウスイベント用のコールバック関数
    static CGEventRef MouseEventCallback(CGEventTapProxy proxy,
                        CGEventType type,
                        CGEventRef event,
                        void *refcon){
        //voidポインタをクラスのポインタにキャスト
        MouseEventData* datap = (MouseEventData*)refcon;

        //イベントデータクラス変数を更新
        datap->update(event, type);

        //戻り値はイベントもしくはNULL
        return event;
    };

    //キーイベント用のコールバック関数
    static CGEventRef KeyEventCallback(CGEventTapProxy proxy,
                        CGEventType type,
                        CGEventRef event,
                        void *refcon){
        //voidポインタをクラスのポインタにキャスト
        KeyEventData* datap = (KeyEventData*)refcon;

        //イベントデータクラス変数を更新
        datap->update(event);

        //戻り値はイベントもしくはNULL
        return event;
    };
};
#endif /* myEvents_hpp */
