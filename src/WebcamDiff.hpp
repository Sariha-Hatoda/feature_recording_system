//
//  WebcamDiff.hpp
//  webcam_diff_1-0
//
//  Created by Tadashi Ohara on 2022/04/29.
//

#ifndef WebcamDiff_hpp
#define WebcamDiff_hpp

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"


class WebcamDiff{
public:
    void init(int resize);
    void update();
    void clear();
    void show( int x, int y, int w, int h );
    //webcam映像の取得

    ofVideoGrabber camera;
    
    //グレースケール化
    ofImage image;
    cv::Mat immat, immatold, DiffMat;

    //画像のサイズ格納
    int img_w, img_h;

    //輝度差分の出力
    float diff;

    //ピクセルデータ格納用の配列
    unsigned char* pixels;

    bool isFirst;

    //グレースケール化したのち差分画像を生成する関数
    cv::Mat graydiff(cv::Mat now, cv::Mat old){
        //グレースケール化
        cv::Mat nowg,oldg,diffg;
        cv::cvtColor(now, nowg, CV_RGBA2GRAY);
        cv::cvtColor(old, oldg, CV_RGBA2GRAY);
        cv::absdiff(nowg,oldg,diffg);
        return diffg;
    }

    //cv::Mat各要素の平均をとる関数(通常差分画像に用いる)
    float reduceMat(cv::Mat inputMat){
        float scalafloat;
        scalafloat = (float)cv::mean(inputMat)[0];
        return scalafloat;
    }
};

#endif /* WebcamDiff_hpp */
