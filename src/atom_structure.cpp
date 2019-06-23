#pragma once

//#define DEBUG

#include "atom_structure.h"
#include <cmath>

// basic element
Atom::Atom() {}

Atom::Atom(json atm_js, float axis_length) {
	int id = atm_js["id"], group_id = atm_js["group_id"], mole_id = atm_js["mole_id"];
	string group_type = atm_js["group_type"], element = atm_js["element"];
	vector<float> co = atm_js["coordinate"];
	double f_e = atm_js["f_e"], f_r = atm_js["f_r"], charge = atm_js["charge"];
	this->id = id;
	this->mole_id = mole_id;
	this->group_id = group_id;
	this->group_type = group_type;
	this->element = element;
	this->coordinate = ofVec3f(co[0] - axis_length / 2, co[1] - axis_length / 2, co[2] - axis_length / 2);
	this->f_e = f_e;
	this->f_r = f_r;
	this->charge = charge;
}

// AtomGroup contains several atoms
AtomGroup::AtomGroup() {}

AtomGroup::AtomGroup(int _group_id, int _mole_id, string _group_type) {
	this->group_id = _group_id;
	this->mole_id = _mole_id;
	this->group_type = _group_type;
}

void AtomGroup::append_atom(Atom _atom) {
	if (this->atom_map.count(_atom.id)) {
		throw "Atom already exist!";
	}
	else {
		atom_map.insert(make_pair(_atom.id, _atom));
	}
}


void AtomGroup::draw(ofColor color) {
	ofSetColor(color);
	for (auto map_it = this->atom_map.begin(); map_it != this->atom_map.end(); map_it++) {
		ofDrawIcoSphere(map_it->second.coordinate, map_it->second.f_r / 4.);
	}
#ifdef DEBUG
	cout << "draw atom at: " << map_it->second.coordinate << endl;
#endif // DEBUG
}

ofVec3f AtomGroup::get_center() {
	if (this->cal_center == FALSE) {
#ifdef DEBUG
		cout << "get center called" << endl;
#endif // !DEBUG
		ofVec3f _center = ofVec3f(0., 0., 0.);
		for (auto map_it = this->atom_map.begin(); map_it != this->atom_map.end(); map_it++) {
			_center += map_it->second.coordinate;
		}
		_center /= this->atom_map.size();
		this->center = _center;
		this->cal_center = TRUE;
	}
	return this->center;
}

Atom3D::Atom3D()
{
}

Atom3D::Atom3D(string fp)
{
	load_from_json(fp);
}

// Atom3D contains all the atom groups for one frame
void Atom3D::append_atom(Atom _atom) {
	if (this->group_map.count(_atom.group_id)) {
		group_map[_atom.group_id].append_atom(_atom);
	}
	else {
		AtomGroup new_group(_atom.group_id, _atom.mole_id, _atom.group_type);
		new_group.append_atom(_atom);
		group_map.insert(make_pair(_atom.group_id, new_group));
	}
}

void Atom3D::load_from_json(string fp) {
	json atom_info;
	if (!std::filesystem::exists(fp)) {
		ofLogNotice() << "file not exist: " << fp;
		throw fp;
	}
	else {
		ifstream in_file(fp);
		in_file >> atom_info;
		//ofLogNotice() << "file loaded: " << fp;
	}
	this->axis_length = atom_info["length"];
	for (json::iterator it = atom_info.begin(); it != atom_info.end(); ++it) {
		if (it.key() != "length") {
			json atm_json = it.value();
			Atom new_atom(atm_json, this->axis_length);
			append_atom(new_atom);
		}
	}
}

vector<int> Atom3D::get_neighbor_group_id(const int center_group_id, float r) {
	AtomGroup c_grp = this->group_map[center_group_id];
	vector<float> distance;
	vector<int> arg_vec;
	for (auto it = this->group_map.begin(); it != this->group_map.end(); it++) {
		if ((it->first != center_group_id) & (it->second.mole_id != c_grp.mole_id)) {
			float _d = c_grp.get_center().distance(it->second.get_center());
			if (_d < r) {
				distance.push_back(_d);
				arg_vec.push_back(it->first);
			}
		}
	}
	return _arg_sort(distance, arg_vec);
}

vector<int> Atom3D::_arg_sort(vector<float> ivec, vector<int> arg_vec) {
	const int COUNT = ivec.size();
	for (int i = 1; i < COUNT; i++) {
		for (int j = 0; j < COUNT - i; j++) {
			if (ivec[j] > ivec[j + 1]) {
				swap(ivec[j], ivec[j + 1]);
				swap(arg_vec[j], arg_vec[j + 1]);
			}
		}
	}
	return arg_vec;
}

// Axis implement
Axis::Axis() {
	length = 300.0;
}

Axis::Axis(float _l) {
	length = _l;
}

void Axis::update(float _l) {
	this->length = _l;
	int i_node = 0;
	for (float x = -0.5; x < 1; x += 1) {
		for (float y = -0.5; y < 1; y += 1) {
			for (float z = -0.5; z < 1; z += 1) {
				node[i_node].setPosition(x * length, y * length, z * length);
				i_node++;
			}
		}
	}
	for (int i_line = 0; i_line < 12; i_line++) {
		line[i_line].addVertex(node[connect[i_line][0]].getGlobalPosition());
		line[i_line].addVertex(node[connect[i_line][1]].getGlobalPosition());
	}
}

void Axis::draw() {
	ofSetColor(0);
	for (int i_line = 0; i_line < 12; i_line++) {
		line[i_line].draw();
	}
}

void Axis::draw(ofColor color) {
	ofSetColor(color);
	for (int i_line = 0; i_line < 12; i_line++) {
		line[i_line].draw();
	}
}


float cal_vdw(Atom atom1, Atom atom2, float r) {
	float r_i = atom1.f_r, r_j = atom2.f_r;
	float f_v = 0.;
	if (r < 9.5) {
		float r_ij = pow((pow(r_i, 6) + pow(r_j, 6) / 2), 1 / 6);
		float f_e = 2 * sqrt(atom1.f_e * atom2.f_e) / pow(r_i, 3) / pow(r_j, 3);
		f_v = 18 * f_e / r_ij * (pow((r_ij / r), 10) - pow((r_ij / r), 7));
	}
	return f_v;
}

float cal_elec(Atom atom1, Atom atom2, float r) {
	float f_e = 0.;
	if (r < 9.5) {
		f_e = atom1.charge * atom2.charge / r / r;
	}
	return f_e;
}

float cal_frc(Atom atom1, Atom atom2) {
	float r = atom1.coordinate.distance(atom2.coordinate);
	return cal_vdw(atom1, atom2, r) + cal_elec(atom1, atom2, r);
}