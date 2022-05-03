#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //スタンドアローンビルドのためのおまじない
    ofSetDataPathRoot("../Resources/data/");
    ofSetFrameRate(5);    //フレームレート指定

    filenum = 0;
    csvfilestr = ofGetTimestampString("%y%m%d%H%M")+".csv";

    ssd.init(CAM_W, CAM_H, CAM_R);    //顔検出用
    camdiff.init(CAM_W, CAM_H, CAM_R);//webcam輝度用

    aw.init();    //aw情報を初期化
    sc.init();    //scの初期化

    //イベント情報を初期化
    //マウスイベント，キーイベント管理クラス初期化~イベントタップ有効化・ランループ実行までを一括実行
    event.init();

    //csvファイル内部の初期化
    row.setString(0, "FileNo.");
    row.setString(1, "Time_Stamp");
    row.setString(2, "Elapsed_Time");
    row.setString(3, "Face_detected");
    row.setString(4, "Face_moved");
    row.setString(5, "Webcam_diff");

    row.setString(6, "Mouse_moved");

    for ( int i=0; i<MOUSE_EVENT_NUM; i++ ) {
        row.setString(7+i, event.mouse_data.EoIStr[i]);
    }
    for ( int i=0; i<KEY_NUM; i++ ) {
        row.setString(7+MOUSE_EVENT_NUM+i, event.key_data.KeyCodeStr[i]);
    }
    row.setString(7+MOUSE_EVENT_NUM+KEY_NUM, "disp_diff");
    int counter = 0;
    for(auto& p : aw.AW_Count){
        row.setString(8+MOUSE_EVENT_NUM+KEY_NUM+counter,p.first);
        counter++;
    }
    csvRecorder.addRow(row);
    csvRecorder.save(csvfilestr);
    //開始時刻を記録
    old = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
/*
    ssd.update();       //顔検出を更新
    camdiff.update();   //webcam輝度差分を更新

    aw.update();        //aw情報を更新
    sc.update();        //スクショ情報を更新

    //eventのみ，コールバック関数内部でupdateを定義
*/
}

//--------------------------------------------------------------
void ofApp::draw(){
/*
    if(isPassed(&old)){
        ssd.clear();
        camdiff.clear();
        sc.clear();
        aw.clear();
        event.clear();
    }
*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
