//
//  WebcamDiff.cpp
//  webcam_diff_1-0
//
//  Created by Tadashi Ohara on 2022/04/29.
//

#include "WebcamDiff.hpp"
void WebcamDiff::init(int width, int height, int resize){
    //画像のサイズは，アスペクト比を保ったままリサイズ
    img_w = width  / resize;
    img_h = height / resize;

    //カメラ解像度の初期化
    camera.setDeviceID(0);
    camera.setup(img_w, img_h);

    //実行後最初の処理かどうかを管理するフラグ
    isFirst = true;

    //差分値を0で初期化
    diff = 0.0;
}

void WebcamDiff::update(){
    //カメラ映像入力のアップデート
    camera.update();
    
    //ofImageにコンバート
    image.setFromPixels(camera.getPixels().getData(), img_w, img_h, OF_IMAGE_COLOR);
    image.resize(img_w/DIFF_R, img_h/DIFF_R);

    //cv::Matに変換
    immat = ofxCv::toCv(image);
    //最初の実行時のみ，フレーム画像をコピー
    if(isFirst){
        immatold = immat.clone();
        isFirst = false;
    }
    //差分画像の生成
    DiffMat = graydiff(immat, immatold);

    //差分画像の要素の平均値を輝度差分に加算
    diff += reduceMat(DiffMat);
    //画像を更新
    immatold = immat.clone();
}

void WebcamDiff::clear(){
    diff = 0.0;
}

void WebcamDiff::show( int x, int y, int w, int h ){
    ofxCv::drawMat(DiffMat, x, y, w, h);
}
