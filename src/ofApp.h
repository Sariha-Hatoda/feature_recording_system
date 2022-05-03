#pragma once

#include "ofMain.h"

//for Webcam-info
#include "FaceDetect.hpp"
#include "WebcamDiff.hpp"
#include "ofxGraph.h"   //for Graph
#include "ofxCsv.h"     //for Csv

//for Display-info
#include "ActiveWindow.hpp"
#include "ScreenGrab.hpp"

//for Operation-info
#include "myEvents.hpp"

#define INTERVAL 5

//for Webcam
#define CAM_W 1920
#define CAM_H 1080
#define CAM_R 3

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    FaceDetect ssd;     //顔検出を管理するクラス
    WebcamDiff camdiff; //輝度差分抽出を管理するクラス
    ActiveWindow aw;    //アクティブウィンドウを示すクラス
    ScreenGrab sc;      //スクショ管理用のクラス
    myEvents event;     //イベント管理用のクラス

    int old;            //時刻を格納しておく変数

    //指定時間が経過したかどうかを判断する論理関数
    bool isPassed(int* time){
        if((int)ofGetElapsedTimef()-(*time)==INTERVAL){
            *time = ofGetElapsedTimef();
            return true;
        }
        else
            return false;
    };
};
