//
//  ActiveWindow.hpp
//  CGActiveWindow1-0
//
//  Created by Tadashi Ohara on 2022/04/30.
//

#ifndef ActiveWindow_hpp
#define ActiveWindow_hpp

#include "ofMain.h"
#define S_SIZE 256
class ActiveWindow{
public:
    void init();
    void update();
    void clear();
    void show();

    //ウィンドウの変化回数を格納しておく変数
    int winchanged;
    //aw名称を格納しておくchar配列
    string winname, winnameold;

    //string-intの辞書型配列
    unordered_map<string, unsigned int> AW_Count;
    
    bool isFirst;
};

#endif /* ActiveWindow_hpp */
