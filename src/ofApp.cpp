#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	numberOfCircles = 50;
	speed = 2;
	circleDistance = 5000.f / 20;
	circlePosition = 0;

	cylinder.set(500, 5000, 16, 20, 0, false);
	cylinderOrientation.makeRotate(90, ofVec3f(1, 0, 0));

	cam.setDistance(cam.getDistance() * 1);
}

//--------------------------------------------------------------
void ofApp::update(){

	circleIncrement = circleDistance * (ofGetLastFrameTime() * speed);

	circlePosition += circleIncrement;
	if (circlePosition > circleDistance) {
		circlePosition -= circleDistance;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	cam.begin();

	ofBackground(0);
	ofNoFill();

	float x = 1.0 / ofGetWidth();
	float y = 1.0 / ofGetHeight();

	cylinder.setPosition(x, y, circlePosition);
	cylinder.setOrientation(cylinderOrientation);

	cylinder.drawWireframe();

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
