#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "ofMain.h"
#include "json.hpp"

using namespace std;
using namespace nlohmann;

class Atom {
public:
	int id=0, group_id=0, mole_id=0;
	string group_type="", element="";
	double f_e=0., f_r=0., charge=0.;
	ofVec3f coordinate = ofVec3f(0., 0., 0.);
	Atom();
	Atom::Atom(json atm_js, float axis_length);
};

class AtomGroup {
public:
	int group_id = 0, mole_id = 0;
	string group_type = "";
	map<int, Atom> atom_map;
	AtomGroup();
	AtomGroup::AtomGroup(int _group_id, int _mole_id, string _group_type);
	void append_atom(Atom _atom);

	void draw();
	void draw(ofColor color);
	bool cal_center = FALSE;
	ofVec3f center;
	ofVec3f get_center();
};

class Atom3D {
public:
	float axis_length = 0.;
	map<int, AtomGroup> group_map;
	void append_atom(Atom input_atom);
	void load_from_json(string fp);
};

class Axis {
public:
	Axis();
	Axis(float _l);
	void update(float _l);
	void draw();
	void draw(ofColor color);

private:
	const int connect[12][2] = { {0,1}, {0,2}, {0,4}, {3,1}, {3,2}, {3,7}, {5,4}, {1,5}, {5,7}, {6,2}, {6,7}, {6,4} };
	ofPolyline line[12];
	ofNode node[8];
	float length;
};

float cal_vdw(Atom atom1, Atom atom2, float r);
float cal_elec(Atom atom1, Atom atom2, float r);
float cal_frc(Atom atom1, Atom atom2);