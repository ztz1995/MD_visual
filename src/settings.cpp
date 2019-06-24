
#include "ofxDatGui.h"
#include "settings.h"
#include "atom_model.h"



Settings::Settings() {
	gui = new ofxDatGui();
}
void Settings::setup() {
	gui->setAutoDraw(FALSE);
	gui->addHeader("Setting Panel");
	gui->addFooter();
	gui->getFooter()->setLabelWhenExpanded("Setting Panel - CLOSE");
	gui->getFooter()->setLabelWhenCollapsed("Setting Panel - COLLAPSE");
	theme = new PanelTheme(1.3);
	gui->setTheme(theme, true);
	// play controls
	actions = gui->addFolder("Actions", ofColor::blue);
	playButton = actions->addButton(" ** Play");
	pauseButton = actions->addButton(" ** Pause");
	stopButton = actions->addButton(" ** Stop");
	actions->expand();
	gui->addBreak();
	//model settings:: FR, opacity, color, neighbor_num, cent_id
	modelFolder = gui->addFolder("Model Settings", ofColor::green);
	modelFrameNumSlider = modelFolder->addSlider("Frames", 1, 20, 5);
	modelFrameNumSlider->setPrecision(0);
	modelNeighborNumSlider = modelFolder->addSlider("Neighbor num", 0, 20, 8);
	modelNeighborNumSlider->setPrecision(0);
	modelCentIdSlider = modelFolder->addSlider("Center id", 0, 250, 29);
	modelCentIdSlider->setPrecision(0);
	modelRadiusSlider = modelFolder->addSlider("Radius", 0, 100, 50);
	modelRadiusSlider->setPrecision(1);
	modelFrameRateSlider = modelFolder->addSlider("Model FR", 1, 25, 1);
	modelFrameRateSlider->setPrecision(0);
	modelOpacitySlider = modelFolder->addSlider("Opacity", 0, 255, 200);
	modelOpacitySlider->setPrecision(0);
	modelColorPicker = modelFolder->addColorPicker("Primary Color", ofColor(3, 168, 158));
	modelDissolvedToggle = modelFolder->addToggle("Fully Dissolved");
	modelFolder->expand();
	gui->addBreak();


	//information board
	infoBoard = gui->addFolder("Panel Settings", ofColor::gray);
	//frame rate
	infoBoard->addFRM(0.1);
	appFRSetter = infoBoard->addSlider("App FR", 10, 120, 60);
	appFRSetter->onSliderEvent(this, &Settings::onSliderEvent);
	opacitySlider = infoBoard->addSlider("Panel opacity", 0, 1, 1);
	opacitySlider->onSliderEvent(this, &Settings::onSliderEvent);
	scaleInput = infoBoard->addTextInput("Panel Scale", "1.2");
	scaleInput->setInputType(ofxDatGuiInputType::NUMERIC);
	scaleInput->onTextInputEvent(this, &Settings::onTextInputEvent);

	//infoBoard->expand();

}
void Settings::update() {

}

void Settings::bindEventsToModel(AtomModel* model)
{
	//can also use bind(), but only for slider?
	//binding after setup
	playButton->onButtonEvent(model, &AtomModel::onPlayButton);
	pauseButton->onButtonEvent(model, &AtomModel::onPauseButton);
	stopButton->onButtonEvent(model, &AtomModel::onStopButton);

	modelDissolvedToggle->onToggleEvent(model, &AtomModel::onDissolvedToggle);
	// todo load data.
	//modelFrameNumSlider->onSliderEvent(model, &AtomModel::onFrameNumSlider);
	modelNeighborNumSlider->onSliderEvent(model, &AtomModel::onNeighborNumSlider);
	modelCentIdSlider->onSliderEvent(model, &AtomModel::onCenterIdSlider);
	modelRadiusSlider->onSliderEvent(model, &AtomModel::onNeighborRadiusSlider);
	modelFrameRateSlider->onSliderEvent(model, &AtomModel::onFrameRateSlider);
	modelOpacitySlider->onSliderEvent(model, &AtomModel::onOpacitySlider);
	modelColorPicker->onColorPickerEvent(model, &AtomModel::onColorPicker);

	//update panel like slider max value
	modelFrameNumSlider->setMax(model->max_frame_num);
}


void Settings::onSliderEvent(ofxDatGuiSliderEvent e)
{
	//cout << "Slider: " << e.target->getLabel() << " - " << e.target->getValue() << endl;
	if (e.target == appFRSetter) {
		float fr = e.target->getValue();
		ofSetFrameRate(fr);
		//cout << "Set frame rate to " << fr << endl;;
	}
	else if (e.target == opacitySlider) {

		gui->setOpacity(e.target->getValue());
	}

}

void Settings::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
	if (e.target == scaleInput) {
		string s = e.target->getText();
		if (s == "") {
			s = "1.3";
		}
		float scale = atof(s.c_str());
		if (scale > 0.5 && scale < 3) {
			theme->setScale(scale);
			gui->setTheme(theme, true);
		}
	}
}
