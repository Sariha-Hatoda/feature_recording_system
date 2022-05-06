#pragma once

#include "ofMain.h"

//for Webcam-info
#include "FaceDetect.hpp"
#include "WebcamDiff.hpp"
#include "ofxCsv.h"     //for Csv

//#include "ofxGraph.h"   //for Graph

//for Display-info
#include "ActiveWindow.hpp"
#include "ScreenGrab.hpp"

//for Operation-info
#include "myEvents.hpp"

//エクスポートのインターバル
#define INTERVAL 20

//for Webcam
#define CAM_W 1920
#define CAM_H 1080
#define CAM_R 3

//描画時のリサイズの基準
#define DRAW_R 0.5

//保存するファイルの上限
#define MAX_FILES 100


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

    ofTrueTypeFont font;//ttfフォント描画用

    FaceDetect ssd;     //顔検出を管理するクラス
    WebcamDiff camdiff; //輝度差分抽出を管理するクラス
    ActiveWindow aw;    //アクティブウィンドウを示すクラス
    ScreenGrab sc;      //スクショ管理用のクラス
    myEvents event;     //イベント管理用のクラス

    int old;            //時刻を格納しておく変数
    string start;       //開始時刻をstring型で格納

    //for csv-recording
    ofxCsvRow row;
    ofxCsv csvRecorder;
    
    unsigned int filenum;

    //指定時間が経過したかどうかを判断する論理関数
    bool isPassed(int* time){
        if((int)ofGetElapsedTimef()-(*time)==INTERVAL){
            *time = ofGetElapsedTimef();
            return true;
        }
        else
            return false;
    };

    //ofAppのウィンドウを収録する関数
    void savescr(string start, int resize, unsigned int filenum){
        ofImage savefig;
        savefig.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        savefig.resize(savefig.getWidth()/resize, savefig.getHeight()/resize);
        savefig.save(start+"_images/"+ofToString(filenum%MAX_FILES)+".jpg");
    };
};
