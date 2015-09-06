//
//  ofxMultiLoggerChannel.h
//  ofxLoggerChannel
//
//  Created by Elias Zananiri on 2015-09-05.
//
//

#pragma once

#include "ofMain.h"

class ofxMultiLoggerChannel : public ofBaseLoggerChannel
{
public:
    ofxMultiLoggerChannel();
    ~ofxMultiLoggerChannel();

    void log(ofLogLevel level, const string & module, const string & message);
    void log(ofLogLevel level, const string & module, const char* format, ...) OF_PRINTF_ATTR(4, 5);
    void log(ofLogLevel level, const string & module, const char* format, va_list args);

    void addLoggerChannel(std::shared_ptr<ofBaseLoggerChannel> channel);
    void removeLoggerChannel(std::shared_ptr<ofBaseLoggerChannel> channel);

    std::shared_ptr<ofConsoleLoggerChannel> addConsoleLoggerChannel();
    std::shared_ptr<ofFileLoggerChannel> addFileLoggerChannel(const string& path, bool append = false);

private:
    std::list<std::shared_ptr<ofBaseLoggerChannel>> _channels;
};