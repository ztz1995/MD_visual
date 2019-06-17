#pragma once

#include "atom_structure.h"
#include <cmath>

float cal_vdw(Atom atom1, Atom atom2, float r) {
	float r_i = atom1.f_r, r_j = atom2.f_r;
	float f_v = 0.;
	if (r < 9.5) {
		float r_ij = pow((pow(r_i, 6) + pow(r_j, 6) / 2), 1 / 6);
		float f_e = 2*sqrt(atom1.f_e * atom2.f_e) / pow(r_i, 3) / pow(r_j, 3);
		f_v = 18 * f_e / r_ij * (pow((r_ij / r), 5) - pow((r_ij / r), 8));
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

Atom::Atom() {};

Atom::Atom(json atm_js, float axis_length) {
	int id = atm_js["id"], group_id = atm_js["group_id"], mole_id = atm_js["mole_id"];
	string group_type = atm_js["group_type"], element = atm_js["element"];
	vector<float> co = atm_js["coordinate"];
	double f_e = atm_js["f_e"], f_r = atm_js["f_r"], charge = atm_js["charge"];
	this->id = id;
	this->group_id = group_id;
	this->group_type = group_type;
	this->element = element;
	this->coordinate = ofVec3f(co[0]-axis_length, co[1] - axis_length, co[2] - axis_length);
	this->f_e = f_e;
	this->f_r = f_r;
	this->charge = charge;
}

AtomGroup::AtomGroup() {};

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
	ifstream in_file(fp);
	json atom_info;
	in_file >> atom_info;
	this->axis_length = atom_info["length"];
	for (json::iterator it = atom_info.begin(); it != atom_info.end(); ++it) {
		if (it.key() != "length") {
			json atm_json = it.value();
			Atom new_atom(atm_json, this->axis_length);
			append_atom(new_atom);
		}
	}
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
	ofSetColor(200);
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