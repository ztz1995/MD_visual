#include "ofApp.h"
#include <windows.h>

//--------------------------------------------------------------
void ofApp::setup() {
	settings = Settings();
	settings.setup();
	model = new AtomModel(&settings);
	model->setup(5, "data/atom_data/atom_info_");
	settings.bindEventsToModel(model);

	// turn on smooth lighting //
	ofSetSmoothLighting(true);
	// Point lights emit light in all directions //
	// set the diffuse color, color reflected from the light source //
	pointLight.setDiffuseColor(ofColor(255, 255, 255));

	// specular color, the highlight/shininess color //
	pointLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
	pointLight.setPointLight();

	// turn the light into spotLight, emit a cone of light //
	spotLight.setSpotlight();
	// size of the cone of emitted light, angle between light axis and side of cone //
	// angle range between 0 - 90 in degrees //
	spotLight.setSpotlightCutOff(50);
	// rate of falloff, illumitation decreases as the angle from the cone axis increases //
	// range 0 - 128, zero is even illumination, 128 is max falloff //
	spotLight.setSpotConcentration(45);

	// Directional Lights emit light based on their orientation, regardless of their position //
	directionalLight.setDiffuseColor(ofColor(255, 255, 255));
	directionalLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
	directionalLight.setDirectional();
	// set the direction of the light
	// set it pointing from left to right -> //
	directionalLight.setOrientation(ofVec3f(0, 90, 0));

	mycam.setDistance(model->getAxisLength() * 2);
	ofResetElapsedTimeCounter();
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

	// enable lighting //
	ofEnableLighting();
	pointLight.enable();
	spotLight.enable();
	directionalLight.enable();

	mycam.begin();
	model->draw();
	mycam.end();

	pointLight.disable();
	spotLight.disable();
	directionalLight.disable();
	ofDisableLighting();
	//end light and model drawing
	ofDisableDepthTest();
	settings.draw();
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