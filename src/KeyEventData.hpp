//
//  KeyEventData.hpp
//  CGKeyEvents1-0
//
//  Created by Tadashi Ohara on 2022/04/29.
//

#ifndef KeyEventData_hpp
#define KeyEventData_hpp

#include "ofMain.h"
#define KEY_NUM 127

class KeyEventData{
    public:
        void update(CGEventRef event);
        void clear(void);
        void show(void);
        unordered_map<string, unsigned int> KeyCount;
        string KeyCodeStr[KEY_NUM]{
            "a",
            "s",
            "d",
            "f",
            "h",
            "g",
            "z",
            "x",
            "c",
            "v",
            "Unknown",
            "b",
            "q",
            "w",
            "e",
            "r",
            "y",
            "t",
            "1",
            "2",
            "3",
            "4",
            "6",
            "5",
            "=",
            "9",
            "7",
            "-",
            "8",
            "0",
            "]",
            "o",
            "u",
            "[",
            "i",
            "p",
            "RETURN",
            "l",
            "j",
            "'",
            "k",
            ";",
            "BACK_SLASH",
            "CAMMA",
            "/",
            "n",
            "m",
            ".",
            "TAB",
            "SPACE",
            "`",
            "DELETE",
            "ENTER",
            "ESCAPE",
            "R_COMMAND",
            "L_COMMAND",
            "L_SHIFT",
            "CAPS_LOCK",
            "L_OPTION",
            "L_CTRL",
            "R_SHIFT",
            "R_OPTION",
            "R_CTRL",
            "fn",
            "Unknown",
            ".",
            "Unknown",
            "*",
            "Unknown",
            "+",
            "Unknown",
            "CLEAR",
            "Unknown",
            "Unknown",
            "Unknown",
            "/",
            "ENTER",
            "Unknown",
            "-",
            "Unknown",
            "Unknown",
            "=",
            "0",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "Unknown",
            "8",
            "9",
            "Unknown",
            "Unknown",
            "Unknown",
            "F5",
            "F6",
            "F7",
            "F3",
            "F8",
            "F9",
            "Unknown",
            "F11",
            "Unknown",
            "F13",
            "Unknown",
            "F14",
            "Unknown",
            "F10",
            "Unknown",
            "F12",
            "Unknown",
            "F15",
            "HELP",
            "HOME",
            "PGUP",
            "DELETE",
            "F4",
            "END",
            "F2",
            "PGDN",
            "F1",
            "LEFT",
            "RIGHT",
            "DOWN",
            "UP",
        };
    private:
    
};
#endif /* KeyEventData_hpp */
