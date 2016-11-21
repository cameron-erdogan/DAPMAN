#pragma once

#include "ofMain.h"
#include "Leap.h"
#include "LeapUtil.hpp"
#include "LeapBox.hpp"
#include "ofxNetwork.h"

class ofApp : public ofBaseApp, LeapBoxDelegate{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //LeapBoxDelegate stuff
    void lock();
    void unlock();
    
    //leap motion stuff
    LeapBox leapBox;
    ofLight pointLight;
    
    //need to create client object to talk to door's server
    //client object should handle connecting & reconnecting
    //& sending messages
    ofxTCPClient tcpClient;
    int connectTime;
    int deltaTime;
};
