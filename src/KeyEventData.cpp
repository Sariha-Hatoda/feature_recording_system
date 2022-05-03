//
//  KeyEventData.cpp
//  CGKeyEvents1-0
//
//  Created by Tadashi Ohara on 2022/04/29.
//

#include "KeyEventData.hpp"

void KeyEventData::clear(){
    for ( int i=0; i<KEY_NUM; i++ ) {
        KeyCount[KeyCodeStr[i]] = 0;
    }
}

void KeyEventData::update(CGEventRef event){
    CGKeyCode key = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    KeyCount[KeyCodeStr[key]]++;
    //cout<<KeyCodeStr[key]<<":"<<KeyCount[KeyCodeStr[key]]<<endl;
}

void KeyEventData::show(){
    for( int i=0; i<KEY_NUM; i++ ){
        cout<<i<<":"<<KeyCodeStr[i]<<":"<<KeyCount[KeyCodeStr[i]]<<endl;
    }
}
