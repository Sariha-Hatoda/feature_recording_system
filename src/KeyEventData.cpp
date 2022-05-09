//
//  KeyEventData.cpp
//  CGKeyEvents1-0
//
//  Created by Tadashi Ohara on 2022/04/29.
//

#include "KeyEventData.hpp"

void KeyEventData::clear(){
    //font.load("arial.ttf", 28);
    for ( int i=0; i<KEY_NUM; i++ ) {
        KeyCount[KeyCodeStr[i]] = 0;
    }
}

void KeyEventData::update(CGEventRef event){
    key = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    KeyCount[KeyCodeStr[key]]++;
}

void KeyEventData::show(int x, int y){
    //ofDrawBitmapString(ofToString(KeyCodeStr[key]+":"+ofToString(KeyCount[KeyCodeStr[key]])), x, y);
    //font.drawString(ofToString(KeyCodeStr[key]+":"+ofToString(KeyCount[KeyCodeStr[key]])), x, y);
/*
    for( int i=0; i<KEY_NUM; i++ ){
        cout<<i<<":"<<KeyCodeStr[i]<<":"<<KeyCount[KeyCodeStr[i]]<<endl;
    }
*/
}
