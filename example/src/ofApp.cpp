#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetFrameRate(120);

	/*
	 * create panels
	 */

	ofxGuiPanel* panel1 = gui.addPanel("control");
	ofxGuiPanel* panel2 = gui.addPanel();
	panel2->setPosition(250, 10);


	/*
	 * add controllers
	 */

	ofxGuiElement* control = panel1->add(m_slider1.set("sinus",0,-1,1));
	control->setFillColor(ofColor::tomato);
	cf.addController(control);

	control = panel1->add(m_slider2.set("cosine",0,-1,1));
	control->setFillColor(ofColor::aqua);
	cf.addController(control);

	/*
	 * add followers
	 */

	control = panel2->add(s_slider1.set("follower1",0,0,1));
	cf.addFollower(control);

	control = panel2->add(s_slider2.set("follower2",0,10,20));
	cf.addFollower(control);

	control = panel2->add(s_toggle.set("follower3",false));
	cf.addFollower(control);

	/*
	 * add regular slider
	 */

	panel2->add(s_slider3.set("regular slider",0,-1,1));

}

//--------------------------------------------------------------
void ofApp::exit() {
}

//--------------------------------------------------------------
void ofApp::update() {
	m_slider1 = sin(ofGetElapsedTimef());
	m_slider2 = cos(ofGetElapsedTimef());
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(255);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch(key) {
	case 'f': {
		ofToggleFullscreen();
		break;
	}
	default: break;
	}

}

//--------------------------------------------------------------
void ofApp::mouseMoved(ofMouseEventArgs &args){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(ofMouseEventArgs &args){
}

//--------------------------------------------------------------
void ofApp::mousePressed(ofMouseEventArgs &args){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(ofMouseEventArgs &args){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
