#include "ofxControllerFollower.h"

ofxControllerFollower::ofxControllerFollower() {

	followers.clear();
	controllers.clear();
	activeController = 0;

	ofRegisterMouseEvents(this, -1);

}
ofxControllerFollower::~ofxControllerFollower() {
	ofUnregisterMouseEvents(this, -1);
}

void ofxControllerFollower::draw() {

	if(activeController != 0) {
		ofSetColor(activeController->control->getFillColor(), 133);
		ofFill();
		//ofSetLineWidth(3);
		for(unsigned int i = 0; i < followers.size(); i++) {
			ofDrawRectangle(followers.at(i)->control->getShape());
		}
		ofDrawRectangle(activeController->control->getShape());
	}
}

void ofxControllerFollower::addController(ofxGuiElement *control) {
	controllers.push_back(new Controller(control));
}

void ofxControllerFollower::addFollower(ofxGuiElement *control) {
	followers.push_back(new Follower(control));
}

void ofxControllerFollower::setActiveController(Controller* controller) {

	if(controller){
		if(activeController){
			if(activeController != controller){
				activeController->isActive = false;
			}
		}
		activeController = controller;
		controller->isActive = true;
		for(unsigned int i = 0; i < followers.size(); i++) {
			followers[i]->setListening(true, controller);
		}
	}else {
		if(activeController){
			activeController->isActive = false;
			activeController = nullptr;
		}
		for(unsigned int i = 0; i < followers.size(); i++) {
			followers[i]->setListening(false, controller);
		}
	}
}

bool ofxControllerFollower::mouseMoved(ofMouseEventArgs & args) {
	return false;
}

bool ofxControllerFollower::mousePressed(ofMouseEventArgs & args) {

	bool onElement = false;
	for(unsigned int i = 0; i < followers.size(); i++) {
		if(followers.at(i)->control->isMouseOver()) {
			onElement = true;
			if(activeController != 0) {
				followers.at(i)->setControlledBy(activeController);
			}
			else {
				followers.at(i)->removeControl();
			}
		}
	}
	for(unsigned int i = 0; i < controllers.size(); i++) {
		if(controllers.at(i)->control->isMouseOver()) {
			onElement = true;
			if(controllers.at(i)->isActive) {
				setActiveController(nullptr);
			}
			else {
				setActiveController(controllers.at(i));
			}
		}
	}
	if(!onElement) {
		setActiveController(nullptr);
	}
	return false;
}

bool ofxControllerFollower::mouseDragged(ofMouseEventArgs & args) {
	return false;
}

bool ofxControllerFollower::mouseReleased(ofMouseEventArgs & args) {
	return false;
}

bool ofxControllerFollower::mouseScrolled(ofMouseEventArgs & args) {
	return false;
}

