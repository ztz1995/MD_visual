#pragma once
#include "atom_structure.h"
#include "settings.h"

class AtomModel {
	friend class Settings;
public:
	AtomModel(Settings* s = NULL);
	Axis axis;
	void setup(int frames, string path_prefix = "data/atom_data/atom_info_");
	void loadData(int frames, string path_prefix = "data/atom_data/atom_info_");
	void updateParams(int fr = -1, int opacity = -1);
	void draw();
	void update();
	float getAxisLength();
	//vector<int> neighbor_id;
	vector<Atom3D> model_frames;
	vector<vector<int>> frames_neighbor_id;
private:
	const static int CENT_ID = 29;    //50 Ph  100 TO
	const static int NUM_NEIGHBOR = 6;
	bool playing = true;
	void onPlayButton(ofxDatGuiButtonEvent e);
	void onPauseButton(ofxDatGuiButtonEvent e);
	void onStopButton(ofxDatGuiButtonEvent e);
	// data params: prefix&frame_num
	string path_prefix;
	int cur_frame = 0, init_frame = 0, last_frame = 0, frame_num = 0;
	// setting model params
	bool fully_dissolved;
	void onDissolvedToggle(ofxDatGuiToggleEvent e);
	int frame_rate;
	void onFrameRateSlider(ofxDatGuiSliderEvent e);
	int opacity;
	void onOpacitySlider(ofxDatGuiSliderEvent e);
	ofColor color;
	void onColorPicker(ofxDatGuiColorPickerEvent e);
};