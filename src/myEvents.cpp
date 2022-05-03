//
//  myEvents.cpp
//  integrated_events
//
//  Created by Tadashi Ohara on 2022/05/03.
//

#include "myEvents.hpp"
void myEvents::init(){
    //クラス変数を初期化
    mouse_data.init();
    mouse_data.clear();
    key_data.clear();

    //モードはCommonで固定
    mode = kCFRunLoopCommonModes;

    //イベントタップの設置場所を指定
    ETloc = kCGSessionEventTap;

    //イベントフラグの定義
    flags = CGEventSourceFlagsState(kCGEventSourceStateCombinedSessionState);

    //ランループは常に現在のランループを参照
    rlref = CFRunLoopGetCurrent();

    //マウスイベントマスクを定義
    for ( int i=0; i<MOUSE_EVENT_NUM; i++){
        Mouse_eventMask = Mouse_eventMask|CGEventMaskBit(mouse_data.EoI[i]);
    }
    //キーイベントマスクを定義
    Key_eventMask = CGEventMaskBit(kCGEventKeyDown)|CGEventMaskBit(kCGEventFlagsChanged);

    //イベントタップの設置場所を指定
    ETloc = kCGSessionEventTap;

    //マウスイベントタップの作成
    CFMachPortRef Mouse_eventTap = CGEventTapCreate(ETloc,
                 kCGHeadInsertEventTap,
                 kCGEventTapOptionListenOnly,
                 Mouse_eventMask,
                 MouseEventCallback,
                 &mouse_data);

    //マウスイベントタップの作成
    CFMachPortRef Key_eventTap = CGEventTapCreate(ETloc,
                 kCGHeadInsertEventTap,
                 kCGEventTapOptionListenOnly,
                 Key_eventMask,
                 KeyEventCallback,
                 &key_data);

    //CFMachPortオブジェクトでのCFRunLoopオブジェクトを作成
    CFRunLoopSourceRef runLoopSource_mouse = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, Mouse_eventTap, 0);
    CFRunLoopSourceRef runLoopSource_key = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, Key_eventTap, 0);

    //オブジェクトをランループに追加
    CFRunLoopAddSource(rlref, runLoopSource_mouse, mode);
    CFRunLoopAddSource(rlref, runLoopSource_key, mode);

    //ランループに追加した時点でランループオブジェクトを解放
    CFRelease(runLoopSource_key);
    CFRelease(runLoopSource_mouse);

    //イベントタップの有効化
    CGEventTapEnable(Mouse_eventTap, true);
    CGEventTapEnable(Key_eventTap, true);

    //ランループの実行
    CFRunLoopRun();
}

void myEvents::clear(){
    mouse_data.clear();
    key_data.clear();
}
