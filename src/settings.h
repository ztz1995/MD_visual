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
	void draw();
	/*model setting items*/
	ofxDatGuiFolder* modelFolder;
	void bindEventsToModel(AtomModel* model);
	//actions
	ofxDatGuiFolder* actions;
	ofxDatGuiButton* playButton;
	ofxDatGuiButton* pauseButton;
	ofxDatGuiButton* stopButton;
	//dissolve toggle
	ofxDatGuiToggle* modelDissolvedToggle;
	ofxDatGuiSlider* modelFrameNumSlider, * modelNeighborNumSlider, * modelCentIdSlider, * modelRadiusSlider;

	//model frame rate
	ofxDatGuiSlider* modelFrameRateSlider;
	//model color&opacity
	ofxDatGuiSlider* modelOpacitySlider;
	ofxDatGuiColorPicker* modelColorPicker;
	/*end model setting items*/
private:
	//shared event handler
	void onSliderEvent(ofxDatGuiSliderEvent e);
	void onTextInputEvent(ofxDatGuiTextInputEvent e);
	//for settings panel
	ofxDatGuiFolder* infoBoard;
	ofxDatGuiSlider* appFRSetter;
	ofxDatGuiSlider* opacitySlider;
	ofxDatGuiTextInput* scaleInput;
};


class PanelTheme :public ofxDatGuiThemeSmoke {
public:
	PanelTheme(float scale = 1.3) {
		_theme = ofxDatGuiThemeSmoke();
		_scale = scale;
	}
	void setScale(float scale) {
		if (scale == _scale) {
			return;
		}
		ofLogNotice() << "set panel scale: ";
		font.size = _theme.font.size * scale * 1.2;
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

		font.ptr = ofxSmartFont::add(font.file, font.size);
	}
private:
	// default theme
	ofxDatGuiThemeSmoke _theme;
	float _scale;
};
