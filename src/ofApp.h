#pragma once

#include "atom_structure.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofEasyCam mycam;
	Axis axis;
	
	const static int FRAME_NUM = 5;
	Atom3D atom3d[FRAME_NUM];
	const static int CENT_ID = 29;    //50 Ph  100 TO
	const static int NUM_NEIGHBOR = 6;
	vector<int> neighbor_id;

	uint64_t current_time;
	int frame_every = 500000;
	int current_frame=0, last_frame=-1;

};
