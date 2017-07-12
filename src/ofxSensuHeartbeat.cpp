//
//  ofxSensuHeartbeat.cpp
//  GifAnimator
//
//  Created by aros on 7/10/17.
//
//

#include "ofxSensuHeartbeat.hpp"

void ofxSensuHeartbeat::setup(shared_ptr<ofxSensu> _sensu,
                                     string name,
                                     int ttl,
                                     string output,
                                     string remediation,
                                     int occurrences,
                                     int severity){
    halt   = false;
    period = chrono::seconds(ttl/2);;
    sensu  = _sensu;
    
    sensu->buildStillAliveMessage(name, ttl, output, remediation, occurrences, severity);
    
    start();
}


// Default setup, local logging only
void ofxSensuHeartbeat::setup(chrono::seconds _period){
    halt = false;
    sensu = NULL;
    period = _period;
    startTime = ofGetElapsedTimef();
    start();
}

ofxSensuHeartbeat::~ofxSensuHeartbeat() {
    stop();
    cv.notify_one();
    if (heart.joinable())
        heart.join();
}


// Begin Heartbeat loop
void ofxSensuHeartbeat::start() {
    heart = thread([this] {
        mutex m;
        unique_lock<mutex> l(m);
        while (!halt) {
            beat();
            cv.wait_for(l, period);
        }
    });
}


// Halt heart beat loop
void ofxSensuHeartbeat::stop() {
    halt = true;
}

// Perform these actions every period
void ofxSensuHeartbeat::beat() {
    
    float  minutesUp = (ofGetElapsedTimef() - startTime) / 60.f;
    string timestamp = ofGetTimestampString("%H:%M %b %e, %y").c_str();
    
    ofLogNotice("ofxSensuHeartbeat", "Up at %s (%0.f min)", timestamp.c_str(), minutesUp);
    
    if (sensu != NULL) {
        ofLogNotice("ofxSensuHeartbeat") << "Sending still alive";
        sensu->sendStillAlive();
    }
}