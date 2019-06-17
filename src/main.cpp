#pragma once

//#include "ofMain.h"
#include "ofApp.h"

//#include <iostream>

//========================================================================
int main() {

	//Atom3D atom3d;
	//// load atom information from json file
	//atom3d.load_from_json("C://OF_projects/MD_visual/src/data/atom_info_000.json");

	//// get single atom, id=1
	//// atom_map in a map<int, Atom> , atom_id: atom
	//atom3d.atom_map[1].coordinate;

	//// atom3d group info, map<int, vector<int>>, group_id: {atom_ids}
	//map<int, vector<int>>::iterator group_it;
	//for (group_it = atom3d.group_info.begin(); group_it != atom3d.group_info.end(); group_it++) {
	//	cout << "group type: " << atom3d.group_type_info[group_it->first] << ", id: " << group_it->first << ": ";
	//	for (auto i : group_it->second) {
	//		cout << i << ", ";
	//	}
	//	cout << endl;
	//}
	//cout << "new" << endl;

	ofSetupOpenGL(1024, 768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());


}
