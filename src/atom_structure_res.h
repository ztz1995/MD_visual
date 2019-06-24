#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "ofMain.h"
#include "MarchingCubes.h"


class Atom {
public:
	int id = 0, group_id = 0, mole_id = 0;
	string group_type = "", element = "";
	double f_e = 0., f_r = 0., charge = 0., mass=0.;
	vector<ofVec3f> coordinate;
	//int cur_frame = 0;
	Atom();
	Atom(ofJson atm_js, float axis_length);
	void update(ofJson atm_js, float axis_length);
};

class AtomGroup {
public:
	int group_id = 0, mole_id = 0;
	int cur_frame = -1;
	string group_type = "";
	map<int, Atom> atom_map;
	AtomGroup();
	AtomGroup::AtomGroup(int _group_id, int _mole_id, string _group_type);
	void append_atom(Atom _atom);

	MarchingCubes iso;
	bool set_iso = FALSE;
	bool cal_iso = FALSE;
	ofVec3f iso_scale;
	void update(int frame_no);
	void draw(ofColor color = ofColor(3, 168, 158, 240));
	bool cal_center[1000] = { FALSE };
	ofVec3f center[1000];
	ofVec3f get_center(int cur_frame);
private:

};

class Atom3D {
public:
	Atom3D();
	Atom3D(string prefix, int frames);
	void setup(string prefix);
	void update(string prefix, int frames);
	//int cur_frame = 0, last_frame = -1; 
	vector<float> axis_length;
	map<int, AtomGroup> group_map;
	void append_atom(Atom input_atom);
	void load_from_json(string fp);
	vector<int> get_neighbor_group_id(const int center_group_id, float r = 15.f, int cur_frames = 0);
private:
	vector<int> _arg_sort(vector<float> ivec, vector<int> arg_vec);
};

class Axis {
public:
	Axis();
	Axis(float _l);
	void update(float _l);
	void draw();
	void draw(ofColor color);
	float length;

private:
	const int connect[12][2] = { {0,1}, {0,2}, {0,4}, {3,1}, {3,2}, {3,7}, {5,4}, {1,5}, {5,7}, {6,2}, {6,7}, {6,4} };
	ofPolyline line[12];
	ofNode node[8];

};

float cal_vdw(Atom atom1, Atom atom2, float r);
float cal_elec(Atom atom1, Atom atom2, float r);
float cal_frc(Atom atom1, Atom atom2);