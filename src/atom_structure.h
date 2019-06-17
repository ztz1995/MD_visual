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
	int id=0;
	int group_id=0;
	string group_type, element;
	double f_e=0., f_r=0., charge=0.;
	ofVec3f coordinate;
	Atom();
	Atom(int _id, int _group_id, string _group_type, string _element, vector<float> _co, double _f_e, double _f_r, double _charge);
	//string to_str();
	//void print();
};

class AtomGroup {
public:
	AtomGroup();
	AtomGroup(int _group_id, string _group_type);
	int group_id=0;
	string group_type = "";
	map<int, Atom> atom_map;
	//vector<int> group_info;
	void append_atom(Atom _atom);
};

class Atom3D {
public:
	map<int, AtomGroup> group_map;
	//map<int, string> group_type_map;
	void append_atom(Atom input_atom);
	void load_from_json(string fp);
	float length = 0.;
	//void print();
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

