# feature_recording_system
* 修士研究において作成した特徴量記録システム
* openFrameworksで作成した，特徴量記録システムです．Gitリポジトリ化しているので，sourcetreeなどで可視化すると変更履歴が確認できます．
* 以下使用方法です．
* oFのmyAppsフォルダに追加後，project generatorでupdateします．その際，addonを追加します．
 ofxCsv
 ofxOpenCv
 ofxCv
 ofxGraph
 ofxGui
 ofxXmlSettings
* Xcodeでビルドします．その際，stand-aloneにするべくXcodeの以下の設定を施してください．

* cp -r bin/data "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Resources";
* For OF < 0.8 call ofSetDataPathRoot(“../Resources/”); in setup(), ofApp.cpp.
* and for OF >= 0.8 call ofSetDataPathRoot("../Resources/data/"); in setup(), ofApp.cpp

* また，Project Settingsからビルド設定を変更してください．しないとエラーになります．webcamが接続されていない場合でもエラーになります．
* 実行時に，スクリーンショットとキーログの許可を求められるので，システム環境設定から許可してください．
* 上記の手順で実行できない場合は私宛に連絡をください．
* hisarahatoda@gmail.com

* ofApp.hppの最初に各パラメタを設定しています．csv書き出しのインターバル，フレームレートなどの数値などです．
