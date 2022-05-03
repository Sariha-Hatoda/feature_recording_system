//
//  ScreenGrab.cpp
//  CGScreenshot4
//
//  Created by Tadashi Ohara on 2022/04/30.
//

#include "ScreenGrab.hpp"
//初期化
void ScreenGrab::init(){
    //色空間を定義
    colorSpace = CGColorSpaceCreateDeviceRGB();

    //オンラインディスプレイのリストを取得
    dErr = CGGetOnlineDisplayList(maxDisplays, onlineDisplays, &displayCount);

    //ofAppウィンドウサイズを初期化
    drawwidth =0;
    drawheight=0;

    //ディスプレイの解像度(配列の要素数)の総和
    all_disp_size = 0;

    //ディスプレイIDおよび幅と高さの初期化
    for (int i = 0; i < displayCount; i++) {

        //ディスプレイIDの取得
        dID = onlineDisplays[i];

        //リサイズ後の解像度を格納
        width[i] =CGDisplayPixelsWide(dID)/RESIZE;
        height[i] =CGDisplayPixelsHigh(dID)/RESIZE;

        //配列要素の総和を取得
        total_disp_size[i] = width[i]*height[i];
        all_disp_size+=total_disp_size[i];

        //ofAppウィンドウの横幅は単純に合計
        drawwidth+=width[i];
        //高さはどちらか高い方
        if(height[i]>drawheight)
            drawheight = height[i];

        //画像配列の定義
        cv::Mat im(cv::Size(width[i], height[i]), CV_8UC4);
        //配列要素を同様に定義
        imgs[i] = im;
        //imgsoldはimgsで初期化
        imgsold[i] = imgs[i].clone();
        //CGコンテクストを作成
        contextRef[i] = CGBitmapContextCreate(imgs[i].data, imgs[i].cols, imgs[i].rows, 8, imgs[i].step[0], colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrderDefault);
    }
    //差分値を0で初期化
    diff= 0.0;

    //フラグをtrueで初期化
    isFirst = true;
}

void ScreenGrab::update(){
    for (int i = 0; i < displayCount; i++) {
        //ディスプレイIDを取得
        dID = onlineDisplays[i];
        //該当IDのスクリーンショットを取得
        imageRef[i] = CGDisplayCreateImage(dID);
        //取得したスクリーンショットをcv::Mat形式で取得
        CGContextDrawImage(contextRef[i], CGRectMake(0, 0, width[i], height[i]), imageRef[i]);

        //最初の実行の場合，何もしないでフラグを下ろす
        if(isFirst){
            isFirst = false;
        }
        //2回目以降の実行の場合，実際に差分の計算
        else{
            //差分画像(gray)の生成
            imgsdiff[i] = graydiff(imgs[i], imgsold[i]);
            //差分値(平均値)の計算
            //平均値を求めた後，ディスプレイの解像度をかけ直して平均し直す
            diff+=reduceMat(imgsdiff[i])*total_disp_size[i];
        }
        //どちらの場合でも，古い画像は更新する
        imgsold[i] = imgs[i].clone();
    }
    //ディスプレイ全体の解像度で，輝度値の総和を割る
    diff/=all_disp_size;
}

void ScreenGrab::clear(){
    diff = 0.0;
}

void ScreenGrab::show(){
    //ディスプレイの数だけ繰り返す
    for (int i = 0; i < displayCount; i++) {
        //差分画像の描画
        ofxCv::drawMat(imgsdiff[i], 0+i*width[i-1], 0, width[i], height[i]);
        //画像の解放
        CGImageRelease(imageRef[i]);
    }
}
                        
