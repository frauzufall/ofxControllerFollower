#pragma once

#include "ofMain.h"
#include "ofxGuiExtended.h"

class Controller {

public:

	Controller(ofxGuiElement* _control) {
		control = _control;
		if(ofxGuiSlider<float>* slider = dynamic_cast<ofxGuiSlider<float>*>(control)) {
			min = slider->getMin();
			max = slider->getMax();
		}
		if(ofxGuiSlider<int>* slider = dynamic_cast<ofxGuiSlider<int>*>(control)) {
			min = slider->getMin();
			max = slider->getMax();
		}
	}

	~Controller(){}

	ofxGuiElement* control = 0;
	bool isActive = false;
	bool slider = false;
	float min=1, max=1;
};

class Follower {

public:

	ofxGuiElement* control = 0;
	bool isControlled = false;
	bool isListening = false;
	bool slider = false;
	float min=0, max=1;
	Controller* controller = 0;
	ofColor defaultBackgroundColor;
	ofColor defaultBorderColor;
	float defaultBorderWidth;

	Follower(ofxGuiElement* guiElement) {
		this->control = guiElement;
		defaultBackgroundColor = control->getBackgroundColor();
		if(ofxGuiSlider<float>* slider = dynamic_cast<ofxGuiSlider<float>*>(control)) {
			min = slider->getMin();
			max = slider->getMax();
		}
		if(ofxGuiSlider<int>* slider = dynamic_cast<ofxGuiSlider<int>*>(control)) {
			min = slider->getMin();
			max = slider->getMax();
		}
	}

	~Follower() {
		removeControl();
	}

	void setListening(bool listening, Controller* controller = nullptr) {
		if(!isListening && listening){
			defaultBorderColor = control->getBorderColor();
			defaultBorderWidth = control->getBorderWidth();
			control->setBorderColor(controller->control->getFillColor());
			control->setBorderWidth(5);
		}
		if(isListening && listening){
			control->setBorderColor(controller->control->getFillColor());
			control->setBorderWidth(5);
		}
		if(isListening && !listening){
			control->setBorderColor(defaultBorderColor);
			control->setBorderWidth(defaultBorderWidth);
		}
		isListening = listening;

	}

	void setControlledBy(Controller *controller) {
		bool setC = true,removeC = false;
		if(isControlled) {
			removeC = true;
		}
		if(this->controller == controller) {
			setC = false;
		}

		if(removeC) {
			removeControl();
		}
		if(setC) {
			if(ofxGuiToggle* toggle = dynamic_cast<ofxGuiToggle*>(controller->control)) {
				toggle->addListener(this, &Follower::valueChanged<bool>);
				isControlled = true;
				this->controller = controller;
			}
			if(ofxGuiSlider<float>* slider = dynamic_cast<ofxGuiSlider<float>*>(controller->control)) {
				slider->addListener(this, &Follower::valueChanged<float>);
				isControlled = true;
				this->controller = controller;
			}
			if(ofxGuiSlider<int>* slider = dynamic_cast<ofxGuiSlider<int>*>(controller->control)) {
				slider->addListener(this, &Follower::valueChanged<int>);
				isControlled = true;
				this->controller = controller;
			}
			if(isControlled) {
				control->setBackgroundColor(controller->control->getFillColor());
			}
		}
	}

	void removeControl() {
		if(controller != 0) {
			if(ofxGuiToggle* toggle = dynamic_cast<ofxGuiToggle*>(controller->control)) {
				toggle->removeListener(this, &Follower::valueChanged<bool>);
			}
			if(ofxGuiSlider<float>* slider = dynamic_cast<ofxGuiSlider<float>*>(controller->control)) {
				slider->removeListener(this, &Follower::valueChanged<float>);
			}
			if(ofxGuiSlider<int>* slider = dynamic_cast<ofxGuiSlider<int>*>(controller->control)) {
				slider->removeListener(this, &Follower::valueChanged<int>);
			}
			isControlled = false;
			controller = 0;
			control->setBackgroundColor(defaultBackgroundColor);
		}
	}

	template <class Tvalue>
	void valueChanged(Tvalue &value) {
		if(ofxGuiSlider<float>* slider = dynamic_cast<ofxGuiSlider<float>*>(control)) {
			*slider = ofMap(value, controller->min, controller->max,min,max);
		}
		else if(ofxGuiSlider<int>* slider = dynamic_cast<ofxGuiSlider<int>*>(control)) {
			*slider = ofMap(value, controller->min, controller->max,min,max);
		}
		else if(ofxGuiToggle* toggle = dynamic_cast<ofxGuiToggle*>(control)) {
			*toggle =  floor(ofMap(value, controller->min, controller->max,min,max)+0.5);
		}
	}

};

class ofxControllerFollower {

	public:

		ofxControllerFollower();
		~ofxControllerFollower();

		void draw();

		void addFollower(ofxGuiElement* follower);
		void addController(ofxGuiElement* controller);

		ofColor getHighlightColor();
		void setHighlightColor(ofColor);

		virtual bool mouseMoved(ofMouseEventArgs & args);
		virtual bool mousePressed(ofMouseEventArgs & args);
		virtual bool mouseDragged(ofMouseEventArgs & args);
		virtual bool mouseReleased(ofMouseEventArgs & args);
		virtual bool mouseScrolled(ofMouseEventArgs & args);
		virtual bool mouseEntered(ofMouseEventArgs & args){return false;}
		virtual bool mouseExited(ofMouseEventArgs & args){return false;}

	private:

		void setActiveController(Controller *controller);

		vector<Controller*> controllers;
		vector<Follower*> followers;

		Controller* activeController;

};
