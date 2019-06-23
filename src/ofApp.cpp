#include "ofApp.h"
#include <windows.h>

//--------------------------------------------------------------
void ofApp::setup() {
	settings = Settings();
	settings.setup();
	model = new AtomModel(&settings);
	model->setup(1, "data/atom_data/atom_info_");
	settings.bindEventsToModel(model);


	mycam.setDistance(model->getAxisLength() * 2);
	ofResetElapsedTimeCounter();

	//light.setPointLight();
	//light2.setAmbientColor(225);


}

//--------------------------------------------------------------
void ofApp::update() {
	if (settings.gui->getMouseDown()) {
		mycam.disableMouseInput();
	}
	else {
		mycam.enableMouseInput();
	}
	model->update();
	settings.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofEnableDepthTest();
	ofBackgroundGradient(ofColor::white, ofColor::gray);
	ofEnableDepthTest();
	//ofEnableLighting();
	mycam.begin();


	model->draw();

	model->draw();
	//light.enable();
	//light2.enable();

	
	mycam.end();
	ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 's') {
		// WARNING: ofSaveScreen(fp), fp is default relative to data/, not relative to *.exe.
		string fp = "screenshots/screenshot-" + ofGetTimestampString() + ".png";
		ofLogNotice() << "take screenshot: " << fp;
		ofSleepMillis(1000);
		ofSaveScreen(fp);
	}
	else if (key == ' ') {
		ofLogNotice() << "reset camera.";
		mycam.reset();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}