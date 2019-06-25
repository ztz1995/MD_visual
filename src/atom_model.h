#pragma once
#include "atom_structure_res.h"
#include "settings.h"
#include "MarchingCubes.h"

class AtomModel {
	friend class Settings;
public:
	AtomModel(Settings* s = NULL);
	Axis axis;
	void setup(int frames, string path_prefix = "data/atom_data/atom_info_");
	void loadData(int frames, string path_prefix = "data/atom_data/atom_info_");
	void updateNeighbors(int center_id, float radius = -1.);
	void updateParams(int fr = -1, int opacity = -1);
	void draw();
	void update(bool force=false);
	float getAxisLength();
	//vector<Atom3D> model_frames;
	Atom3D atom3d;
	vector<vector<int>> frames_neighbor_id;
private:
	//TODO: make neighbor_num ,colors and neighbor R tunable.
	bool playing = true;
	void onPlayButton(ofxDatGuiButtonEvent e = NULL);
	void onPauseButton(ofxDatGuiButtonEvent e = NULL);
	void onStopButton(ofxDatGuiButtonEvent e = NULL);
	// data params: prefix
	string path_prefix;
	int cur_frame = 0, init_frame = 0, last_frame = -1;

	// setting model params
	//max_frame_num denpends on valid frame file amount
	int  frame_num = 5, max_frame_num = 5;
	void onFrameNumSlider(ofxDatGuiSliderEvent e);
	int center_id = 0;    //50 Ph  100 TO
	void onCenterIdSlider(ofxDatGuiSliderEvent e);
	int neighbor_num = 10;
	void onNeighborNumSlider(ofxDatGuiSliderEvent e);
	float neighbor_radius = 40.;
	void onNeighborRadiusSlider(ofxDatGuiSliderEvent e);
	int frame_rate;
	void onFrameRateSlider(ofxDatGuiSliderEvent e);
	int opacity;
	void onOpacitySlider(ofxDatGuiSliderEvent e);
	ofColor center_color;
	void onCenterColorPicker(ofxDatGuiColorPickerEvent e);
	ofColor neighbor_color;
	void onNeighborColorPicker(ofxDatGuiColorPickerEvent e);
	bool forcefield_toggle;
	void onForceFieldToggle(ofxDatGuiToggleEvent e);
	bool fully_dissolved;//not used?
	void onDissolvedToggle(ofxDatGuiToggleEvent e);
	//vector<float> _rand_nums;
};