//
//  FaceDetect.hpp
//  DNNtest
//
//  Created by Tadashi Ohara on 2022/04/29.
//

#ifndef FaceDetect_hpp
#define FaceDetect_hpp

#include "ofMain.h"
#include "ofxCv.h"      //for OpenCV
#include "ofxOpenCv.h"  //for OpenCV

class FaceDetect{
public:
    void init(int width, int height, int resize);
    void update(void);
    void clear(void);
    void show(int x, int y, float r);
    
    //カメラ映像
    ofVideoGrabber cam;

    //顔検出に渡す映像
    ofImage camframe;
    
    //描画用
    ofxCvColorImage cv_img;

    //描画時のサイズ指定
    int img_w, img_h;
    //顔検出の閾値
    float limit;
    
    //顔検出用変数の格納用
    string prototxt, model;
    cv::dnn::Net net;
    cv::Mat inputBlob, detection;
    
    //顔の検出数
    int facenum;

    //顔中心の管理
    ofPoint facenow, faceold;
    //移動量管理と顔中心の描画
    float facemoved;
    //顔中心の集合
    vector<vector<float>> facevec;
    //最初に実行したことを示すフラグ
    bool isFirst;

    //顔検出の実行可否を決めるカウンタ
    int detect_counter;

private:
};

#endif /* FaceDetect_hpp */
