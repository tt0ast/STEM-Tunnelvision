#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	numberOfSections = 18;
	speed = 0.5;
	tunnelPosition = 0;

	sectionDistance = 20;

	tunnel.set(20, numberOfSections, sectionDistance, 12, 2);
	tunnelOrientation.makeRotate(90, ofVec3f(-1, 0, 0));

	tunnel.lineColorBlack();
	tunnel.buildTunnel();

	cam.setGlobalPosition(0.f, 0.f, 0.f);
	tunnel.setOrientation(tunnelOrientation);

	ofSetFrameRate(60);

	oscReceiver.setup(12345);

}

//--------------------------------------------------------------
void ofApp::update(){

	float x = 1.0 / ofGetWidth();
	float y = 1.0 / ofGetHeight();

	float bassGain = 0.f;
	float midsGain = 0.f;
	float highsGain = 0.f;

	while (oscReceiver.hasWaitingMessages()) {

		ofxOscMessage message;
		oscReceiver.getNextMessage(message);

		if (message.getAddress() == "/bassGain") {
			bassGain = message.getArgAsFloat(0);
		}

	}

	if (!audioReact) {
		bassGain = 0.f;
	}
	
	tunnel.updateTunnel(speed, ofGetLastFrameTime(), x, y, bassGain);

	//if (setIndex == 1) {

	//	if (ofGetFrameNum() % 5 == 0) {
	//		tunnel.buildTunnelInc(buildupIndex);
	//		buildupIndex++;

	//		if ((buildupIndex / 12) == numberOfSections) {
	//			setIndex = 2;
	//			tunnel.buildTunnel();
	//		}
	//	}
	//} 	

}

//--------------------------------------------------------------
void ofApp::draw(){

	cam.begin();

	ofBackground(0);
	ofNoFill();

	tunnel.drawWireframe();

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == 'f') {
		ofToggleFullscreen();
	}

	if (key == 's') {
		tunnel.lineColorWhite();
	}

	if (key == 'b') {
		if (audioReact) {
			audioReact = false;
		}
		else {
			audioReact = true;
		}
	}

	if (key == 'e') {
		tunnel.lineColorBlack();
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
