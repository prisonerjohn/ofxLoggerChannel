//
//  ofApp.cpp
//  example-ScreenLoggerChannel
//
//  Created by Elias Zananiri on 2015-08-02.
//
//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofSetBackgroundAuto(true);
    ofBackground(ofColor::blueSteel);
    
    screenLoggerChannel = shared_ptr<ofxScreenLoggerChannel>(new ofxScreenLoggerChannel());
    ofSetLoggerChannel(screenLoggerChannel);
    
    ofLogNotice("setup", "Screen logger set.");
    ofLogNotice("setup", "Press [SPACE] to toggle screen logger.");
    ofLogNotice("setup", "You can scroll in this window to see message history.");
    
    numTicks = 0;
    bShowLogger = true;
    
    ofLogNotice("setup", "Start the show!");
}

//--------------------------------------------------------------
void ofApp::update()
{
    // Move the line across the screen once per second.
    frameNum = ofGetFrameNum();
    ofLogVerbose("update", "Processing frame " + ofToString(frameNum));
    lineX = ofMap(frameNum % 60, 0, 59, 0, ofGetWidth());
    if (lineX == 0) {
        ofLogNotice("update", "Tick " + ofToString(++numTicks));
    }
    
    // Slide the logger screen in and out.
    ofRectangle bounds = screenLoggerChannel->getDrawBounds();
    if (bShowLogger) {
        bounds.y = ofLerp(bounds.y, 0, 0.2);
    }
    else {
        bounds.y = ofLerp(bounds.y, -bounds.height, 0.2);
    }
    screenLoggerChannel->setDrawBounds(bounds);
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(255);
    ofDrawRectangle(lineX, 0, ofGetWidth() / 60, ofGetHeight());
    
    screenLoggerChannel->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == ' ') {
        bShowLogger ^= 1;
    }
}
