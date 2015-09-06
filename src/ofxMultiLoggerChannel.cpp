#include "ofxMultiLoggerChannel.h"

//--------------------------------------------------------------
ofxMultiLoggerChannel::ofxMultiLoggerChannel()
: ofBaseLoggerChannel()
{

}

//--------------------------------------------------------------
ofxMultiLoggerChannel::~ofxMultiLoggerChannel()
{
    _channels.clear();
}

//--------------------------------------------------------------
void ofxMultiLoggerChannel::log(ofLogLevel level, const string & module, const string & message)
{
    for (std::shared_ptr<ofBaseLoggerChannel> channel : _channels) {
        channel->log(level, module, message);
    }
}

//--------------------------------------------------------------
void ofxMultiLoggerChannel::log(ofLogLevel level, const string & module, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    log(level, module, format, args);
    va_end(args);
}

//--------------------------------------------------------------
void ofxMultiLoggerChannel::log(ofLogLevel level, const string & module, const char* format, va_list args)
{
    for (std::shared_ptr<ofBaseLoggerChannel> channel : _channels) {
        channel->log(level, module, format, args);
    }
}

//--------------------------------------------------------------
void ofxMultiLoggerChannel::addLoggerChannel(std::shared_ptr<ofBaseLoggerChannel> channel)
{
    _channels.push_back(channel);
}

//--------------------------------------------------------------
void ofxMultiLoggerChannel::removeLoggerChannel(std::shared_ptr<ofBaseLoggerChannel> channel)
{
    _channels.remove(channel);
}

//--------------------------------------------------------------
std::shared_ptr<ofConsoleLoggerChannel> ofxMultiLoggerChannel::addConsoleLoggerChannel()
{
    std::shared_ptr<ofConsoleLoggerChannel> channel = std::shared_ptr<ofConsoleLoggerChannel>(new ofConsoleLoggerChannel());
    _channels.push_back(channel);
    return channel;
}

//--------------------------------------------------------------
std::shared_ptr<ofFileLoggerChannel> ofxMultiLoggerChannel::addFileLoggerChannel(const string& path, bool append)
{
    std::shared_ptr<ofFileLoggerChannel> channel = std::shared_ptr<ofFileLoggerChannel>(new ofFileLoggerChannel(path, append));
    _channels.push_back(channel);
    return channel;
}
