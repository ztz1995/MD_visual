
#include "atom_structure.h"

Atom::Atom() {
	this->id = 0;
	this->group_id = 0;
	this->coordinate = ofVec3f(0.,0.,0.);
	this->element = "";
}

Atom::Atom(int _id, int _group_id, string _group_type, string _element, vector<float> _co, double _f_e, double _f_r, double _charge) {
	this->id = _id;
	this->group_id = _group_id;
	this->group_type = _group_type;
	this->element = _element;
	this->coordinate = ofVec3f(_co[0], _co[1], _co[2]);
	this->f_e = _f_e;
	this->f_r = _f_r;
	this->charge = _charge;
}

//string Atom::to_str() {
//	return string("Atom id: ") + to_string(id) + string(", group_id: ") + to_string(group_id) + string(", type: ") + type + string(", element: ") + element
//		+ string(", coordiante: [") + to_string(coordinate[0]) + string(", ") + to_string(coordinate[1]) + string(", ") + to_string(coordinate[2]) + string("]\n");
//}
//
//void Atom::print() {
//	cout << to_str();
//}

AtomGroup::AtomGroup() {};

AtomGroup::AtomGroup(int _group_id, string _group_type) {
	this->group_id = _group_id;
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
		AtomGroup new_group(_atom.group_id, _atom.group_type);
		new_group.append_atom(_atom);
		group_map.insert(make_pair(_atom.group_id, new_group));
	}
}

void Atom3D::load_from_json(string fp) {
	ifstream in_file(fp);
	json atom_info;
	in_file >> atom_info;
	for (json::iterator it = atom_info.begin(); it != atom_info.end(); ++it) {
		if (it.key() != "length") {
			json atm_json = it.value();
			int id = atm_json["id"], group_id = atm_json["group_id"];
			string group_type = atm_json["group_type"], element = atm_json["element"];
			vector<float> co = atm_json["coordinate"];
			double f_e = atm_json["f_e"], f_r = atm_json["f_r"], charge = atm_json["charge"];
			Atom new_atom(id, group_id, group_type, element, co, f_e, f_r, charge);
			append_atom(new_atom);
		}
		else {
			float _l = it.value();
			this->length = _l;
		}
	}
}

//void Atom3D::print() {
//	map<int, Atom>::iterator it;
//	for (it = atom_map.begin(); it != atom_map.end(); it++) {
//		it->second.print();
//	}
//}

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