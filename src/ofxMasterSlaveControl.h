#pragma once

#include "ofMain.h"
#include "ofxGuiExtended.h"

class MasterControl {

public:

	MasterControl(ofxGuiElement* _control) {
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

	~MasterControl(){}

	ofxGuiElement* control = 0;
	bool isActive = false;
	bool slider = false;
	float min=1, max=1;
};

class SlaveControl {

public:

	ofxGuiElement* control = 0;
	bool isControlled = false;
	bool isListening = false;
	bool slider = false;
	float min=0, max=1;
	MasterControl* master = 0;
	ofColor defaultBackgroundColor;
	ofColor defaultBorderColor;
	float defaultBorderWidth;

	SlaveControl(ofxGuiElement* _control) {
		this->control = _control;
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

	~SlaveControl() {
		cout << "slavecontrol destructor" << endl;
		removeControl();
	}

	void setListening(bool listening, MasterControl* master = nullptr) {
		if(!isListening && listening){
			defaultBorderColor = control->getBorderColor();
			defaultBorderWidth = control->getBorderWidth();
			control->setBorderColor(master->control->getFillColor());
			control->setBorderWidth(5);
		}
		if(isListening && listening){
			control->setBorderColor(master->control->getFillColor());
			control->setBorderWidth(5);
		}
		if(isListening && !listening){
			control->setBorderColor(defaultBorderColor);
			control->setBorderWidth(defaultBorderWidth);
		}
		isListening = listening;

	}

	void setControlledBy(MasterControl *master) {
		bool setC = true,removeC = false;
		if(isControlled) {
			removeC = true;
		}
		if(this->master == master) {
			setC = false;
		}

		if(removeC) {
			removeControl();
		}
		if(setC) {
			if(ofxGuiToggle* toggle = dynamic_cast<ofxGuiToggle*>(master->control)) {
				toggle->addListener(this, &SlaveControl::valueChanged<bool>);
				isControlled = true;
				this->master = master;
			}
			if(ofxGuiSlider<float>* slider = dynamic_cast<ofxGuiSlider<float>*>(master->control)) {
				slider->addListener(this, &SlaveControl::valueChanged<float>);
				isControlled = true;
				this->master = master;
			}
			if(ofxGuiSlider<int>* slider = dynamic_cast<ofxGuiSlider<int>*>(master->control)) {
				slider->addListener(this, &SlaveControl::valueChanged<int>);
				isControlled = true;
				this->master = master;
			}
			if(isControlled) {
				control->setBackgroundColor(master->control->getFillColor());
			}
		}
	}

	void removeControl() {
		if(master != 0) {
			if(ofxGuiToggle* toggle = dynamic_cast<ofxGuiToggle*>(master->control)) {
				toggle->removeListener(this, &SlaveControl::valueChanged<bool>);
			}
			if(ofxGuiSlider<float>* slider = dynamic_cast<ofxGuiSlider<float>*>(master->control)) {
				slider->removeListener(this, &SlaveControl::valueChanged<float>);
			}
			if(ofxGuiSlider<int>* slider = dynamic_cast<ofxGuiSlider<int>*>(master->control)) {
				slider->removeListener(this, &SlaveControl::valueChanged<int>);
			}
			isControlled = false;
			master = 0;
			control->setBackgroundColor(defaultBackgroundColor);
		}
	}

	template <class Tvalue>
	void valueChanged(Tvalue &value) {
		if(ofxGuiSlider<float>* slider = dynamic_cast<ofxGuiSlider<float>*>(control)) {
			*slider = ofMap(value, master->min, master->max,min,max);
		}
		else if(ofxGuiSlider<int>* slider = dynamic_cast<ofxGuiSlider<int>*>(control)) {
			*slider = ofMap(value, master->min, master->max,min,max);
		}
		else if(ofxGuiToggle* toggle = dynamic_cast<ofxGuiToggle*>(control)) {
			*toggle =  floor(ofMap(value, master->min, master->max,min,max)+0.5);
		}
	}

};

class ofxMasterSlaveControl {

	public:

		ofxMasterSlaveControl();
		~ofxMasterSlaveControl();

		void draw();

		void addSlave(ofxGuiElement* control);
		void addMaster(ofxGuiElement* control);

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

		void setActiveMaster(MasterControl *master);

		vector<MasterControl*> masters;
		vector<SlaveControl*> slaves;

		MasterControl* activeMaster;

};
