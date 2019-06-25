
#include "ofxDatGui.h"
#include "settings.h"
#include "atom_model.h"



Settings::Settings() {
	gui = new ofxDatGui();
}
void Settings::setup() {
	theme = new PanelTheme();
	theme->setScale(1.3);
	gui->setAutoDraw(false);
	gui->addHeader("Setting Panel");
	gui->addFooter();
	gui->getFooter()->setLabelWhenExpanded("Setting Panel - COLLAPSE");
	gui->getFooter()->setLabelWhenCollapsed("Setting Panel - EXPAND");

	// play controls
	actions = gui->addFolder("Actions", ofColor::blue);
	playButton = actions->addButton("   ** Play");
	pauseButton = actions->addButton("   ** Pause");
	stopButton = actions->addButton("   ** Stop");
	actions->expand();
	gui->addBreak();

	//model settings:: FR, opacity, neighbor_color, neighbor_num, cent_id
	modelFolder = gui->addFolder("Model Settings", ofColor::green);
	modelFrameNumSlider = modelFolder->addSlider("  Frames", 1, 20, 5);
	modelFrameNumSlider->setPrecision(0);
	modelCenterIdSlider = modelFolder->addSlider("  Center id", 0, 250, 29);
	modelCenterIdSlider->setPrecision(0);
	modelNeighborNumSlider = modelFolder->addSlider("  Neighbor num", 0, 20, 8);
	modelNeighborNumSlider->setPrecision(0);
	modelNeighborRadiusSlider = modelFolder->addSlider("  Radius", 0, 100, 50);
	modelNeighborRadiusSlider->setPrecision(1);
	modelFrameRateSlider = modelFolder->addSlider("  Model FR", 1, 25, 1);
	modelFrameRateSlider->setPrecision(0);
	// change for Opacity to Color mixing
	//modelOpacitySlider = modelFolder->addSlider("  Opacity", 0, 255, 255);
	modelOpacitySlider = modelFolder->addSlider("  Color mixing", 0, 255, 255);
	modelOpacitySlider->setPrecision(0);
	modelCenterColorPicker = modelFolder->addColorPicker("  Center color", ofColor(148, 0, 211));
	modelNeighborColorPicker = modelFolder->addColorPicker("  Primary color", ofColor(3, 168, 158));
	modelDissolvedToggle = modelFolder->addToggle("  Fully dissolved");
	modelDissolvedToggle->setVisible(false); // hide 
	modelForceFieldToggle = modelFolder->addToggle("  Show force field");
	modelFolder->expand();
	gui->addBreak();
	
	lightingFolder = gui->addFolder("Lighting", ofColor::yellow);
	lightRotateX = lightingFolder->addSlider("  Theta x", -180, 180, -130);
	lightRotateY = lightingFolder->addSlider("  Theta y", -180, 180, 60);
	lightRotateZ = lightingFolder->addSlider("  Theta z", -180, 180, 30);
	gui->addBreak();
	
	//information board
	infoBoard = gui->addFolder("Panel Settings", ofColor::gray);
	//frame rate
	FRMonitor = infoBoard->addFRM(0.1);
	FRMonitor->setLabel("  Frame rate");
	appFRSetter = infoBoard->addSlider("  App FR", 10, 120, 60);
	appFRSetter->onSliderEvent(this, &Settings::onSliderEvent);
	opacitySlider = infoBoard->addSlider("  Panel opacity", 0, 1, 1);
	opacitySlider->onSliderEvent(this, &Settings::onSliderEvent);
	scaleInput = infoBoard->addTextInput("  Panel scale", "1.3");
	scaleInput->setInputType(ofxDatGuiInputType::NUMERIC);
	scaleInput->onTextInputEvent(this, &Settings::onTextInputEvent);
	gui->addBreak();

	hintLableShot = gui->addLabel("Press \"s\" to save screenshot.");
	hintLabelCamera = gui->addLabel("Press \"space\" to reset viewport.");
	gui->setTheme(theme, true);
}
void Settings::update() {
	gui->update();
}

void Settings::draw() {
	gui->draw();
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
	modelCenterIdSlider->onSliderEvent(model, &AtomModel::onCenterIdSlider);
	modelNeighborRadiusSlider->onSliderEvent(model, &AtomModel::onNeighborRadiusSlider);
	modelFrameRateSlider->onSliderEvent(model, &AtomModel::onFrameRateSlider);
	modelOpacitySlider->onSliderEvent(model, &AtomModel::onOpacitySlider);
	modelCenterColorPicker->onColorPickerEvent(model, &AtomModel::onCenterColorPicker);
	modelNeighborColorPicker->onColorPickerEvent(model, &AtomModel::onNeighborColorPicker);
	modelForceFieldToggle->onToggleEvent(model, &AtomModel::onForceFieldToggle);
	//update panel like slider max value
	modelFrameNumSlider->setMax(model->max_frame_num);
}


ofVec3f Settings::getLightOrientation()
{
	return ofVec3f(lightRotateX->getValue(), lightRotateY->getValue(), lightRotateZ->getValue());
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
		cout << "set theme scale from " << theme->getScale() << " to " << scale << endl;
		if (scale > 0.5 && scale < 3) {
			theme->setScale(scale);
			gui->setTheme(theme, true);
		}
	}
}
