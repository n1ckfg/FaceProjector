#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    // All examples share data files from example-data, so setting data path to this folder
    // This is only relevant for the example apps
    //ofSetDataPathRoot(ofFile(__BASE_FILE__).getEnclosingDirectory()+"../../model/");
    
    // Setup grabber
    grabber.setup(1280,720);
    
    // Setup tracker
    tracker.setup();

	ofDisableArbTex();
	bloomFbo.allocate(ofGetWidth(), ofGetHeight());
	ofEnableArbTex();
	bloom.setup(ofGetWidth(), ofGetHeight(), bloomFbo);
	bloom.setScale(2.3);// min 0.1, max 16
	bloom.setBrightness(10); // min 0, max 30
	bloom.setThreshold(0); // min 0, max 2
}

//--------------------------------------------------------------
void ofApp::update() {
    grabber.update();
    
    // Update tracker when there are new frames
    if(grabber.isFrameNew()) {
        tracker.update(grabber);
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
	bloomFbo.begin();

    // Draw camera image
    //grabber.draw(0, 0);
	ofBackground(0);

    // Draw tracker landmarks
    tracker.drawDebug();
    
    // Draw estimated 3d pose
    //tracker.drawDebugPose();
    
    // Draw text UI
    //ofDrawBitmapStringHighlight("Framerate : "+ofToString(ofGetFrameRate()), 10, 20);
    //ofDrawBitmapStringHighlight("Tracker thread framerate : "+ofToString(tracker.getThreadFps()), 10, 40);
    
#ifndef __OPTIMIZE__
    //ofSetColor(ofColor::red);
    //ofDrawBitmapString("Warning! Run this app in release mode to get proper performance!",10,60);
    //ofSetColor(ofColor::white);
#endif

	bloomFbo.end();
	bloom.process();
	bloom.draw();
}