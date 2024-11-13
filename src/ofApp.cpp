#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	numberOfSections = 6;
	speed = 0.1;
	tunnelPosition = 0;
	sectionDistance = 20;

	//cylinder.set(500, cylindeLength, 16, 20, 0, false);
	//cylinderOrientation.makeRotate(90, ofVec3f(1, 0, 0));

	cam.setDistance(cam.getDistance() * 2);

	tunnel.set(15, numberOfSections, sectionDistance, 8);
	tunnelOrientation.makeRotate(90, ofVec3f(1, 0, 0));

}

//--------------------------------------------------------------
void ofApp::update(){

	tunnelIncrement = sectionDistance * (ofGetLastFrameTime() * speed);

	tunnelPosition += tunnelIncrement;
	if (tunnelPosition > sectionDistance) {
		tunnel.removeSegment();
		tunnel.addSegment();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	cam.begin();

	ofBackground(0);
	ofNoFill();

	float x = 1.0 / ofGetWidth();
	float y = 1.0 / ofGetHeight();

	tunnel.setPosition(x, y, tunnelPosition - (sectionDistance * numberOfSections / 2));
	tunnel.setOrientation(tunnelOrientation);

	tunnel.drawWireframe();

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == 't') {
		tunnel.addSegment();
	}

	if (key == 'r') {
		tunnel.removeSegment();
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
