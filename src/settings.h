#pragma once
#include "ofMain.h"
#include "ofxDatGui.h"
#include "atom_model.h"
class PanelTheme;
class AtomModel;

class Settings {
public:
	Settings();
	ofxDatGui* gui;
	PanelTheme* theme;
	void setup();
	void update();
	/*model setting items*/
	ofxDatGuiFolder* modelFolder;
	void bindEventsToModel(AtomModel* model);
	//actions
	ofxDatGuiFolder* actions;
	ofxDatGuiButton* playButton;
	ofxDatGuiButton* pauseButton;
	ofxDatGuiButton* stopButton;
	//dissolve toggle
	ofxDatGuiToggle* dissolvedToggle;
	//model frame rate
	ofxDatGuiSlider* modelFrameRateSlider;
	//model color&opacity
	ofxDatGuiSlider* modelOpacitySlider;
	ofxDatGuiColorPicker* modelColorPicker;
private:
	// for AtomModel
	ofxDatGuiTextInput* modelRealFRM;
	//frame rate setter
	void onSliderEvent(ofxDatGuiSliderEvent e);
	//for settings panel
	ofxDatGuiFolder* infoBoard;
	ofxDatGuiSlider* appFRSetter;
	ofxDatGuiSlider* opacitySlider;
	ofxDatGuiToggle* highResToggle;
	void onHighResToggle(ofxDatGuiToggleEvent e);
};


class PanelTheme :public ofxDatGuiThemeSmoke {
public:
	PanelTheme() {
		_theme = ofxDatGuiThemeSmoke();
		_isHighResolution = ofxDatGuiIsHighResolution();
	}
	void toggleHighRes(bool isHighRes) {
		if (isHighRes == _isHighResolution) {
			return;
		}
		_isHighResolution = isHighRes;
		if (isHighRes) {
			cout << "set HighResolution mode" << endl;
			float scale = 1.3f;
			font.size = _theme.font.size * 1.5;
			stripe.width = _theme.stripe.width * scale;
			layout.width = _theme.layout.width * scale;
			layout.height = _theme.layout.height * scale;
			layout.padding = _theme.layout.padding * scale;
			layout.vMargin = _theme.layout.vMargin * scale;
			layout.iconSize = _theme.layout.iconSize * scale;
			layout.labelWidth = _theme.layout.labelWidth * scale;
			layout.labelMargin = _theme.layout.labelMargin * scale;
			layout.graph.height = _theme.layout.graph.height * scale;
			layout.pad2d.height = _theme.layout.pad2d.height * scale;
			layout.pad2d.ballSize = _theme.layout.pad2d.ballSize * scale;
			layout.pad2d.lineWeight = _theme.layout.pad2d.lineWeight * scale;
			layout.matrix.height = _theme.layout.matrix.height * scale;
			layout.matrix.buttonSize = _theme.layout.matrix.buttonSize * scale;
			layout.matrix.buttonPadding = _theme.layout.matrix.buttonPadding * scale;
			layout.colorPicker.rainbowWidth = _theme.layout.colorPicker.rainbowWidth * scale;
			layout.textInput.highlightPadding = _theme.layout.textInput.highlightPadding * scale;

		}
		else {
			cout << "exit HighResolution mode" << endl;

			font.size = _theme.font.size;
			stripe.width = _theme.layout.width;
			layout.width = _theme.layout.width;
			layout.height = _theme.layout.height;
			layout.padding = _theme.layout.padding;
			layout.vMargin = _theme.layout.vMargin;
			layout.iconSize = _theme.layout.iconSize;
			layout.labelWidth = _theme.layout.labelWidth;
			layout.labelMargin = _theme.layout.labelMargin;
			layout.graph.height = _theme.layout.graph.height;
			layout.pad2d.height = _theme.layout.pad2d.height;
			layout.pad2d.ballSize = _theme.layout.pad2d.ballSize;
			layout.pad2d.lineWeight = _theme.layout.pad2d.lineWeight;
			layout.matrix.height = _theme.layout.matrix.height;
			layout.matrix.buttonSize = _theme.layout.matrix.buttonSize;
			layout.matrix.buttonPadding = _theme.layout.matrix.buttonPadding;
			layout.colorPicker.rainbowWidth = _theme.layout.colorPicker.rainbowWidth;
			layout.textInput.highlightPadding = _theme.layout.textInput.highlightPadding;
		}
		font.ptr = ofxSmartFont::add(font.file, font.size);
	}
private:
	// default theme
	ofxDatGuiThemeSmoke _theme;
	bool _isHighResolution;
};
