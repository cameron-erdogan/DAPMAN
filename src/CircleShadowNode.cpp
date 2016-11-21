//
//  CircleShadowNode.cpp
//  DAPMAN
//
//  Created by Cameron Erdogan on 10/27/16.
//
//

#include "CircleShadowNode.hpp"

void CircleShadowNode::setRadius(float radius){
    _radius = radius;
}

void CircleShadowNode::customDraw(){
    ofPushMatrix();
    ofRotateX(90);
    ofDrawCircle(0, 0, _radius);
    ofPopMatrix();
}
