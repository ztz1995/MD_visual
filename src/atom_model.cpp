#include "atom_model.h"

AtomModel::AtomModel(Settings* s)
{
	if (s != NULL) {
		fully_dissolved = s->dissolvedToggle->getChecked();
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
			axis.update(model_frames[cur_frame].axis_length);
			model_frames[cur_frame].group_map[CENT_ID].update();
			int max_neighbors = min(int(frames_neighbor_id[cur_frame].size()), NUM_NEIGHBOR);
			for (int i = 0; i < max_neighbors; i++) {
				model_frames[cur_frame].group_map[frames_neighbor_id[cur_frame][i]].update();
			}
			//neighbor_id.clear();
			//neighbor_id = model_frames[cur_frame].get_neighbor_group_id(CENT_ID);
		}
		last_frame = cur_frame;
	}
}

void AtomModel::draw(){
	axis.draw();
	// here you will draw your object
	model_frames[cur_frame].group_map[CENT_ID].draw(ofColor(148, 0, 211, 240));
	////mmp, neighbor_id may be size 0 when draw() called first time.
	int max_neighbors = min(int(frames_neighbor_id[cur_frame].size()), NUM_NEIGHBOR);
	for (int i = 0; i < max_neighbors; i++) {
		model_frames[cur_frame].group_map[frames_neighbor_id[cur_frame][i]].draw(ofColor(color, opacity));
	}
}

void AtomModel::loadData(int frames, string prefix)
{
	// all filepaths must be absolute or relative to bin/MD_visual_debug.exe
	// please save data files to "bin/data/", not project root. And don't include them in project.
	if (prefix == path_prefix) {
		return;
	}

	for (int i = 0; i < frames; i++) {
		char fp[100];
		sprintf_s(fp, "%03d.json", i);
		string filepath = prefix + string(fp);
		ofLogNotice() << "loading json: " << filepath;
		if (i < frame_num) {
			if (prefix == path_prefix) {
				//already read, skip.
				continue;
			}
			else {
				// different path, update new Atom3D
				model_frames[i] = Atom3D(filepath);
				frames_neighbor_id[i] = model_frames[i].get_neighbor_group_id(CENT_ID, 100);
			}
		}
		else {
			// append the larger index items
			model_frames.push_back(Atom3D(filepath));
			frames_neighbor_id.push_back(model_frames[i].get_neighbor_group_id(CENT_ID, 100));
		}
	}
	frame_num = frames;
	path_prefix = prefix;
}

void AtomModel::updateParams(int frame_rate_new, int opacity_new)
{
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
	if (model_frames.size() > 0) {
		return model_frames[0].axis_length;
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
