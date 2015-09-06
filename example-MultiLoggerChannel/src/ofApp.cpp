//
//  ofApp.cpp
//  example-MultiLoggerChannel
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
    
    multiLoggerChannel = shared_ptr<ofxMultiLoggerChannel>(new ofxMultiLoggerChannel());
    multiLoggerChannel->addConsoleLoggerChannel();
    multiLoggerChannel->addFileLoggerChannel("log_" + ofGetTimestampString("%Y%m%d_%H%M%S") + ".log");
    screenLoggerChannel = shared_ptr<ofxScreenLoggerChannel>(new ofxScreenLoggerChannel());
    multiLoggerChannel->addLoggerChannel(screenLoggerChannel);
    ofSetLoggerChannel(multiLoggerChannel);
    
    ofLogNotice("setup", "Screen logger set.");
    ofLogNotice("setup", "Press [SPACE] to toggle screen logger.");
    ofLogNotice("setup", "You can scroll in this window to see message history.");
    
    numTicks = 0;
    
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
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(255);
    ofDrawRectangle(lineX, 0, ofGetWidth() / 60, ofGetHeight());
    
    screenLoggerChannel->draw();
}
