#include "ofApp.h"
#include <windows.h>

//--------------------------------------------------------------
void ofApp::setup() {

	for (int i = 0; i < frame_num; i++) {
		char fp[100];
		//Debug mode: json file path is relative to bin/MD_visual_debug.exe
		sprintf(fp, "../data/atom_info_%03d.json", i);
		atom3d[i].load_from_json(string(fp));
	}

	ofSetFrameRate(60);
	ofEnableDepthTest();
	ofBackground(20);
	mycam.setDistance(atom3d[current_frame].axis_length * 2);
	ofResetElapsedTimeCounter();
}

//--------------------------------------------------------------
void ofApp::update() {
	current_time = ofGetElapsedTimeMicros();
	current_frame = (current_time / frame_every) % frame_num;
	axis.update(atom3d[current_frame].axis_length);
}

//--------------------------------------------------------------
void ofApp::draw() {
	mycam.begin();
	axis.draw();
	// here you will draw your object
	atom3d[current_frame].group_map[0].draw();

	mycam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

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
