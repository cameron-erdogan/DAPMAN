#include "ofApp.h"

using namespace Leap;
using namespace std;

/**
 Next step should be to handle the rendered interaction box as a node, 
 and include all of the tracked hand stuff inside that.
 Much cleaner to organize then my current mess of primitives.
 **/

//--------------------------------------------------------------
void ofApp::setup(){
    //normal OF setup stuff
    ofSetVerticalSync(true);
    ofBackground(20);
    ofSetSphereResolution(48);
    ofEnableDepthTest();
    ofSetSmoothLighting(true);
    
    leapBox.setup();
    leapBox.delegate = this;
    
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .85) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));

    lock();
}


void ofApp::unlock(){
    cout << "unlocking" << endl;
    tcpClient.setup("192.168.1.138", 12345);
    tcpClient.send("unlock");
    tcpClient.close();
}

void ofApp::lock(){
    cout << "locking" << endl;
    
    tcpClient.setup("192.168.1.138", 12345);
    tcpClient.send("lock");
    tcpClient.close();

}

//--------------------------------------------------------------
void ofApp::update(){
    //leap stuff
    
    leapBox.update();
    
    pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/3, 500);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //camera + lighting stuff
//    ofBackgroundGradient(ofColor::white, ofColor::whiteSmoke, OF_GRADIENT_CIRCULAR);
   
    leapBox.draw();
    
    ofEnableLighting();
    pointLight.enable();
    
//    if(tcpClient.isConnected())
//        ofDrawBitmapString("connected", 5, 15);
//    else
//        ofDrawBitmapString("not connected", 5, 15);
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
