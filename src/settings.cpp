
#include "ofxDatGui.h"
#include "settings.h"
#include "atom_model.h"



Settings::Settings() {
	gui = new ofxDatGui();
}
void Settings::setup() {
	gui->addHeader("Setting Panel");
	gui->addFooter();
	gui->getFooter()->setLabelWhenExpanded("Setting Panel - CLOSE");
	gui->getFooter()->setLabelWhenCollapsed("Setting Panel - COLLAPSE");
	theme = new PanelTheme();
	gui->setTheme(theme);
	// play controls
	actions = gui->addFolder("Actions", ofColor::blue);
	playButton = actions->addButton(" ** Play");
	pauseButton = actions->addButton(" ** Pause");
	stopButton = actions->addButton(" ** Stop");
	actions->expand();
	gui->addBreak();
	//model settings
	modelFolder = gui->addFolder("Model Settings");
	modelRealFRM = modelFolder->addTextInput("Real FR", "0");
	modelRealFRM->setEnabled(false);
	modelFrameRateSlider = modelFolder->addSlider("Model FR", 1, 120, 60);
	modelFrameRateSlider->setPrecision(0);
	modelOpacitySlider = modelFolder->addSlider("Opacity", 0, 255, 60);
	modelOpacitySlider->setPrecision(0);
	modelColorPicker = modelFolder->addColorPicker("Primary Color", ofColor(3, 168, 158));
	dissolvedToggle = modelFolder->addToggle("Fully Dissolved");
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
	highResToggle = infoBoard->addToggle("High Resolution");
	highResToggle->onToggleEvent(this, &Settings::onHighResToggle);

	infoBoard->expand();
}
void Settings::update() {
	float real_fr = min(modelFrameRateSlider->getValue(), ofGetFrameRate());
	modelRealFRM->setText(ofToString(real_fr, 2));
}

void Settings::bindEventsToModel(AtomModel* model)
{
	//can also use bind(), but only for slider?
	//binding after setup
	playButton->onButtonEvent(model, &AtomModel::onPlayButton);
	pauseButton->onButtonEvent(model, &AtomModel::onPauseButton);
	stopButton->onButtonEvent(model, &AtomModel::onStopButton);

	dissolvedToggle->onToggleEvent(model, &AtomModel::onDissolvedToggle);
	modelFrameRateSlider->onSliderEvent(model, &AtomModel::onFrameRateSlider);
	modelOpacitySlider->onSliderEvent(model, &AtomModel::onOpacitySlider);
	modelColorPicker->onColorPickerEvent(model, &AtomModel::onColorPicker);
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

void Settings::onHighResToggle(ofxDatGuiToggleEvent e)
{
	theme->toggleHighRes(e.target->getChecked());
	gui->setTheme(theme, true);
}
