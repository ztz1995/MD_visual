#include "atom_model.h"

AtomModel::AtomModel(Settings* s)
{
	if (s != NULL) {
		fully_dissolved = s->modelDissolvedToggle->getChecked();
		frame_rate = s->modelFrameRateSlider->getValue();
		opacity = s->modelOpacitySlider->getValue();
		color = s->modelColorPicker->getColor();
	}
	else {
		fully_dissolved = false;
		frame_rate = 60;
		opacity = 60;
		color = ofColor(3, 168, 158);
	}
	//for (int i = 0; i < 200; i++) {
	//	_rand_nums.push_back(ofRandom(100));
	//}
}

void AtomModel::loadData(int frames, string prefix)
{
	// all filepaths must be absolute or relative to bin/MD_visual_debug.exe
	// please save data files to "bin/data/", not project root. And don't include them in project.
	ofLogNotice() << "Ready to read " << frames << " frames with prefix " << prefix;
	//int old_len = model_frames.size();
	//int frame_no = -1;
	//while (true) {
	//	frame_no += 1;
	//	char fp[100];
	//	sprintf_s(fp, "%03d.json", frame_no);
	//	string filepath = prefix + string(fp);
	//	if (filesystem::exists(filepath)) {
	//		if (frame_no < frames) {
	//			if (frame_no < old_len) {
	//				if (prefix == path_prefix) {
	//					//already read, skip.
	//					continue;
	//				}
	//				else {
	//					// different path, update new Atom3D
	//					ofLogNotice() << "loading json: " << filepath;
	//					model_frames[frame_no] = Atom3D(filepath);
	//				}
	//			}
	//			else {
	//				// append the larger index items
	//				ofLogNotice() << "loading json: " << filepath;
	//				model_frames.push_back(Atom3D(filepath));
	//			}
	//		}
	//	}
	//	else {
	//		ofLogNotice() << filepath << " File not exist! stop reading!";
	//		break;
	//	}
	//}
	atom3d.load_data(prefix, frames);
	int frame_no = atom3d.frames;

	// update parameters
	frame_num = min(frame_no, frames);
	ofLogNotice() << "Load " << frame_num << " frames";
	//cout << "Load " << frame_num << " frames" << endl;
	updateNeighbors(center_id, neighbor_radius);
	path_prefix = prefix;
	if (atom3d.group_map.count(center_id) == 0) {
		center_id = atom3d.group_map.begin()->first;
	}
	//check max frame amount
	max_frame_num = frame_no;
	ofLogNotice() << "Total " << max_frame_num << " frames exist.";
}

void AtomModel::setup(int frames, string prefix)
{
	loadData(frames, prefix);
}

void AtomModel::update()
{
	if (playing) {
		cur_frame = (ofGetElapsedTimeMicros() / (1000000 / frame_rate) + init_frame) % frame_num;
		// only update when current frame changed
		if (cur_frame != last_frame) {
			axis.update(atom3d.axis_length[cur_frame]);
			atom3d.group_map[center_id].update(cur_frame);
			int max_neighbors = min(int(frames_neighbor_id[cur_frame].size()), neighbor_num);
			for (int i = 0; i < max_neighbors; i++) {
				atom3d.group_map[frames_neighbor_id[cur_frame][i]].update(cur_frame);
			}
			//neighbor_id.clear();
			//neighbor_id = model_frames[cur_frame].get_neighbor_group_id(center_id);
		}
		last_frame = cur_frame;
	}
}

void AtomModel::draw() {
	axis.draw();
	// here you will draw your object
	atom3d.group_map[center_id].draw(ofColor(148, 0, 211, 240));
	////mmp, neighbor_id may be size 0 when draw() called first time.

	int max_neighbors = min(int(frames_neighbor_id[cur_frame].size()), neighbor_num);
	//ofColor rand_color = ofColor(0,0,0,opacity);
	//float rand_max = 50.;
	//ofSeedRandom(0);
	for (int i = 0; i < max_neighbors; i++) {
		// rand_max should limit to: rand_max<255
		//rand_color.r = color.r + _rand_nums[i % _rand_nums.size()] * ((color.r - 128 < 0) - 0.5);
		//rand_color.g = color.g + _rand_nums[(i + 1) % _rand_nums.size()] * ((color.g - 128 < 0) - 0.5);
		//rand_color.b = color.b + _rand_nums[(i + 2) % _rand_nums.size()] * ((color.b - 128 < 0) - 0.5);

		atom3d.group_map[frames_neighbor_id[cur_frame][i]].draw(ofColor(color, opacity));
	}
}

void AtomModel::updateNeighbors(int _center_id, float _radius)
{
	if (_radius < 0) {
		_radius = neighbor_radius;
	}
	frames_neighbor_id.clear();
	for (int i = 0; i < frame_num; i++) {
		frames_neighbor_id.push_back(atom3d.get_neighbor_group_id(_center_id, _radius));
	}
}

void AtomModel::updateParams(int frame_rate_new, int opacity_new)
{
	//not used yet
	// opacity = 0 ~ 255
	if (frame_rate_new > 0) {
		frame_rate = frame_rate_new;
	}
	if (opacity_new >= 0) {
		opacity = opacity_new;
	}
}

float AtomModel::getAxisLength()
{
	if (atom3d.frames > 0) {
		return atom3d.axis_length[0];
	}
	else {
		return 0.f;
	}
}

void AtomModel::onPlayButton(ofxDatGuiButtonEvent e)
{
	playing = true;
	ofLogNotice() << "hit Play button.";
}

void AtomModel::onPauseButton(ofxDatGuiButtonEvent e)
{
	playing = false;
	init_frame = cur_frame;
	ofLogNotice() << "hit Pause button. init_frame=" << init_frame;
}

void AtomModel::onStopButton(ofxDatGuiButtonEvent e)
{
	playing = false;
	cur_frame = 0;
	ofLogNotice() << "hit Stop button.";
}

void AtomModel::onFrameNumSlider(ofxDatGuiSliderEvent e)
{
	loadData(int(e.target->getValue()), path_prefix);
}

void AtomModel::onCenterIdSlider(ofxDatGuiSliderEvent e)
{
	int id = e.target->getValue();
	if (cur_frame >= 0) {
		if (atom3d.group_map.count(id) == 1) {
			center_id = id;
			updateNeighbors(center_id, neighbor_radius);
		}
		//else if (center_id >= 0) {
		//	// has been set before
		//	e.target->setValue(center_id);
		//	cout << "reset center_id from " << id << " to " << center_id << endl;
		//}
	}
}

void AtomModel::onNeighborNumSlider(ofxDatGuiSliderEvent e)
{
	if (e.target->getValue() >= 0) {
		neighbor_num = e.target->getValue();
	}
}

void AtomModel::onNeighborRadiusSlider(ofxDatGuiSliderEvent e)
{
	if (e.target->getValue() >= 0) {
		neighbor_radius = e.target->getValue();
	}
	updateNeighbors(center_id, neighbor_radius);
}

void AtomModel::onDissolvedToggle(ofxDatGuiToggleEvent e)
{
	//TODO: dissolve part not finished.
	fully_dissolved = e.target->getChecked();
	ofLogNotice() << "[NOT finished!]Dissolved toggle: " << fully_dissolved;
}

void AtomModel::onFrameRateSlider(ofxDatGuiSliderEvent e)
{
	frame_rate = e.target->getValue();
	ofLogNotice() << "Model frame rate: " << frame_rate;
}

void AtomModel::onOpacitySlider(ofxDatGuiSliderEvent e)
{
	opacity = e.target->getValue();
	ofLogNotice() << "Model opacity: " << opacity;
}

void AtomModel::onColorPicker(ofxDatGuiColorPickerEvent e)
{
	color = e.target->getColor();
	ofLogNotice() << "Model color: " << color;
}
