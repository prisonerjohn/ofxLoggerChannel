//
//  ofApp.h
//  example-ScreenLoggerChannel
//
//  Created by Elias Zananiri on 2015-08-02.
//
//

#pragma once

#include "ofMain.h"
#include "ofxScreenLoggerChannel.h"

class ofApp
: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    
private:
    shared_ptr<ofxScreenLoggerChannel> screenLoggerChannel;
    
    int frameNum;
    int numTicks;
    float lineX;
    
    bool bShowLogger;
};
