//
//  FaceDetect.cpp
//  DNNtest
//
//  Created by Tadashi Ohara on 2022/04/29.
//

#include "FaceDetect.hpp"
void FaceDetect::init(int width, int height, int resize){
    
    //描画用のサイズを指定
    img_w = width /resize;
    img_h = height/resize;

    cam.setup(img_w, img_h);
    limit = 0.3;

    //cv_img.allocate(img_w, img_h);

    //顔検出用ファイルパスを指定
    prototxt = "../Resources/data/deploy.prototxt";
    model = "../Resources/data/res10_300x300_ssd_iter_140000_fp16.caffemodel";
    
    //dnnモデルを指定
    net = cv::dnn::readNetFromCaffe(prototxt, model);

    //顔中心の初期化
    facenow.set(0.0, 0.0);
    faceold.set(0.0, 0.0);
    facemoved = 0.0;

    //顔の検出数を初期化
    facenum = 0;

    isFirst = true;
}

void FaceDetect::update(){
    cam.update();

    if (cam.isFrameNew()){
        //顔検出に渡す側のフレーム
        camframe.setFromPixels(cam.getPixels().getData(), img_w, img_h, OF_IMAGE_COLOR);
        //描画に使う側のフレーム
        //cv_img.setFromPixels(cam.getPixels().getData(), img_w, img_h);
        
        //300x　300にリサイズ
        camframe.resize(300, 300);

        //顔検出の下準備
        inputBlob = cv::dnn::blobFromImage(ofxCv::toCv(camframe));
        
        net.setInput(inputBlob, "data");
        detection = net.forward("detection_out");
    }

    //検出された顔の数を初期化
    facenum = 0;

    //顔検出の実行
    cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
/*
    //描画色の指定
    ofSetColor(ofColor::red);
    ofSetLineWidth(3);
    ofNoFill();
*/
    //検出されたデータに対する処理
    for (int i = 0; i < detectionMat.rows; i++) {
        float confidence = detectionMat.at<float>(i, 2);
        //信頼度がlimitを超えた場合
        if(confidence > limit){
            facenum+=1;
            //顔を囲う矩形を取得
            int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * img_w);
            
            int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * img_h);
            
            int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * img_w);

            int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * img_h);
            //ofDrawRectangle(x1, y1, x2-x1, y2-y1);
            //cv::Rect rect(x1, y1, x2-x1, y2-y1);
            //cv::rectangle(ofxCv::toCv(cv_img), cv::Point(x1, y1), cv::Point(x2,y2), cv::Scalar(0, 255, 0), 2, 4);
            //実際に矩形を描画
            //cv::rectangle(ofxCv::toCv(cv_img), rect, cv::Scalar(255, 0, 0), 1, cv::LINE_4);
            //顔中心(矩形の中心)の更新
            facenow.set((x1+x2)/2.0, (y1+y2)/2.0);
        }
    }
    //最初の実行の時のみ，古い顔中心をただちに更新
    if (isFirst==true || detectionMat.rows==0) {
        faceold = facenow;
        isFirst = false;
    }
    else{
        //移動量の算出
        facemoved += sqrt((facenow.x - faceold.x)*(facenow.x - faceold.x) + (facenow.y - faceold.y)*(facenow.y - faceold.y));
    }
    //顔中心の集合に追加
    //facevec.push_back({facenow.x, facenow.y});
    //顔中心の集合を描画
/*
    for (int vc = 0; vc < facevec.size(); vc++) {
        cv::circle(ofxCv::toCv(cv_img), cv::Point(facevec.at(vc).at(0), facevec.at(vc).at(1)), 2, cv::Scalar(0,255,0));
    }
*/
    //顔中心を更新
    faceold = facenow;
}

void FaceDetect::clear(){
    //facevec.clear();
    facemoved = 0;
}
