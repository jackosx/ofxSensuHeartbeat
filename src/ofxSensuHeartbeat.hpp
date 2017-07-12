//
//  ofxSensuHeartbeat.hpp
//  GifAnimator
//
//  Created by aros on 7/10/17.
//
//

#ifndef ofxSensuHeartbeat_hpp
#define ofxSensuHeartbeat_hpp

#include "ofMain.h"
#include "ofxSensu.h"

class ofxSensuHeartbeat {
public:
    
    // Full-featured setup
    void setup(shared_ptr<ofxSensu> _sensu,
               string name,
               int ttl,
               string output,
               string remediation,
               int occurrences,
               int severity);
    
    // By default just log a still-up message locally
    void setup(chrono::seconds period = chrono::seconds(60));
    
    ~ofxSensuHeartbeat();
    
private:
    float startTime;
    
    atomic<bool> halt;
    condition_variable cv;
    chrono::seconds period;
    
    thread heart;
    shared_ptr<ofxSensu> sensu;
    
    void beat();
    
    void start();
    void stop();
    
};

#endif /* ofxSensuHeartbeat_hpp */
