//
//  ofxScreenLoggerChannel.cpp
//  Desktop
//
//  Created by Elias Zananiri on 2015-08-02.
//
//

#include "ofxScreenLoggerChannel.h"

//--------------------------------------------------------------
ofxScreenLoggerChannel::ofxScreenLoggerChannel()
: ofBaseLoggerChannel()
, _maxBufferCount(100)
, _drawBounds(0, 0, ofGetWidth(), ofGetHeight() / 4)
, _backgroundColor(0, 0, 0, 200)
, _textColor(0, 255, 0, 255)
, _bPrefixTimestamp(true)
, _bMouseInside(false)
, _scrollOffset(0)
{
    ofAddListener(ofEvents().mouseDragged, this, &ofxScreenLoggerChannel::mouseDragged);
    ofAddListener(ofEvents().mouseMoved, this, &ofxScreenLoggerChannel::mouseMoved);
    ofAddListener(ofEvents().mouseScrolled, this, &ofxScreenLoggerChannel::mouseScrolled);
}

//--------------------------------------------------------------
ofxScreenLoggerChannel::~ofxScreenLoggerChannel()
{
    clear();
}

//--------------------------------------------------------------
void ofxScreenLoggerChannel::log(ofLogLevel level, const string & module, const string & message)
{
    // Compose the message.
    std::ostringstream oss;
    if (_bPrefixTimestamp) {
        oss << ofGetTimestampString("%H:%M:%S:%i") << " ";
    }
    oss << "[" << ofGetLogLevelName(level, true) << "] ";
    if (module != "") {
        oss << module << ": ";
    }
    oss << message << endl;
    
    // Add it to the buffer.
    _buffer.push_front(oss.str());
    
    // Adjust offset if necessary.
    if (_scrollOffset > 0) ++_scrollOffset;
    
    // Erase older messages.
    while (_buffer.size() > _maxBufferCount) {
        _buffer.pop_back();
    }
}

//--------------------------------------------------------------
void ofxScreenLoggerChannel::log(ofLogLevel level, const string & module, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    log(level, module, format, args);
    va_end(args);
}

//--------------------------------------------------------------
void ofxScreenLoggerChannel::log(ofLogLevel level, const string & module, const char* format, va_list args)
{
    // Compose the message.
    std::ostringstream oss;
    if (_bPrefixTimestamp) {
        oss << ofGetTimestampString("%H:%M:%S:%i") << " ";
    }
    oss << "[" << ofGetLogLevelName(level, true) << "] ";
    if (module != "") {
        oss << module << ": ";
    }
    oss << ofVAArgsToString(format, args) << endl;
    
    // Add it to the buffer.
    _buffer.push_front(oss.str());
    
    // Adjust offset if necessary.
    if (_scrollOffset > 0) ++_scrollOffset;
    
    // Erase older messages.
    while (_buffer.size() > _maxBufferCount) {
        _buffer.pop_back();
    }
}

//--------------------------------------------------------------
void ofxScreenLoggerChannel::clear()
{
    _buffer.clear();
}

//--------------------------------------------------------------
void ofxScreenLoggerChannel::draw() const
{
    ofPushStyle();
    {
        // Draw the background frame.
        ofSetColor(_backgroundColor);
        ofDrawRectangle(_drawBounds);
        
        // Draw the messages list.
        static const int kLineHeight = 12;
        static const int kTextPadding = 10;
        int currX = kTextPadding;
        int currY = kTextPadding * 2;
        ofSetColor(_textColor);
        
        int currOffset = 0;
        for (const auto& msg : _buffer) {
            // Scroll to the current location.
            if (currOffset < _scrollOffset) {
                ++currOffset;
                continue;
            }
            
            ofDrawBitmapString(msg, _drawBounds.x + currX, _drawBounds.y + currY);
            
            // Go to the next line.
            currY += kLineHeight;
            if (currY > _drawBounds.height - kTextPadding) {
                // Out of space, abort.
                break;
            }
        }
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxScreenLoggerChannel::setMaxBufferCount(int maxBufferCount)
{
    _maxBufferCount = maxBufferCount;
}

//--------------------------------------------------------------
int ofxScreenLoggerChannel::getMaxBufferCount() const
{
    return _maxBufferCount;
}

//--------------------------------------------------------------
void ofxScreenLoggerChannel::setDrawBounds(const ofRectangle& drawBounds)
{
    _drawBounds = drawBounds;
}

//--------------------------------------------------------------
const ofRectangle& ofxScreenLoggerChannel::getDrawBounds() const
{
    return _drawBounds;
}

//--------------------------------------------------------------
void ofxScreenLoggerChannel::setBackgroundColor(const ofColor& backgroundColor)
{
    _backgroundColor = backgroundColor;
}

//--------------------------------------------------------------
const ofColor& ofxScreenLoggerChannel::getBackgroundColor() const
{
    return _backgroundColor;
}

//--------------------------------------------------------------
void ofxScreenLoggerChannel::setTextColor(const ofColor& textColor)
{
    _textColor = textColor;
}

//--------------------------------------------------------------
const ofColor& ofxScreenLoggerChannel::getTextColor() const
{
    return _textColor;
}

//--------------------------------------------------------------
void ofxScreenLoggerChannel::setPrefixTimestamp(bool bPrefixTimestamp)
{
    _bPrefixTimestamp = bPrefixTimestamp;
}

//--------------------------------------------------------------
bool ofxScreenLoggerChannel::getPrefixTimestamp() const
{
    return _bPrefixTimestamp;
}

//--------------------------------------------------------------
void ofxScreenLoggerChannel::mouseDragged(ofMouseEventArgs& args)
{
    mouseMoved(args);
}

//--------------------------------------------------------------
void ofxScreenLoggerChannel::mouseMoved(ofMouseEventArgs& args)
{
    _bMouseInside = _drawBounds.inside(args.x, args.y);
}

//--------------------------------------------------------------
void ofxScreenLoggerChannel::mouseScrolled(ofMouseEventArgs& args)
{
    if (_bMouseInside) {
        _scrollOffset = MAX(0, MIN(_scrollOffset - round(args.y), _buffer.size() - 1));
    }
}
