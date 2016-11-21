//
//  LeapBoxButtonNode.cpp
//  DAPMAN
//
//  Created by Cameron Erdogan on 11/11/16.
//
//

#include "LeapBoxButtonNode.hpp"

void LeapBoxButtonNode::setup(ofVec3f size){
    
//    _box.setParent(*this);
    _box.set(size.x, size.y, size.z);
    _box.setPosition(ofVec3f::zero());
    
    
    ofFloatColor color = ofFloatColor::mediumAquaMarine;
    color.a = 0.1f;
    _material.setDiffuseColor(color);
    
}

void LeapBoxButtonNode::customDraw(){
    //draw box
    _material.begin();
    ofFill();
    _box.draw();
    _material.end();
    
    
    ofDrawBitmapString(_label_text, ofVec3f(-30, 0, 0));
}

bool LeapBoxButtonNode::checkHandInBounds(ofNode& hand, bool highlight){
    //need to compare the global position of hand to the global bounds of _box
    bool in_bounds = false;
    
    //check x
    //box.globalPosition is actually just 0, 0, 0. not what i would've expected
    ofVec3f box_center = getGlobalPosition();
    ofVec3f box_extr = _box.getSize() / 2.0;
    
    ofVec3f hand_pos = hand.getGlobalPosition();
    
    bool x_in_bounds = (hand_pos.x > box_center.x - box_extr.x && hand_pos.x < box_center.x + box_extr.x);
    bool y_in_bounds = (hand_pos.y > box_center.y - box_extr.y && hand_pos.y < box_center.y + box_extr.y);
    bool z_in_bounds = (hand_pos.z > box_center.z - box_extr.z && hand_pos.z < box_center.z + box_extr.z);
    
    bool hand_in_bounds = x_in_bounds && y_in_bounds && z_in_bounds;
    
    if(highlight == true)
        updateHighlight(hand_in_bounds);
    
    return hand_in_bounds;
}

void LeapBoxButtonNode::updateHighlight(bool should_highlight){
    
    ofFloatColor color = ofFloatColor::mediumAquaMarine;
    
    if(should_highlight){
        color.a = 0.25f;
        _material.setDiffuseColor(color);
    }
    else{
        color.a = 0.1f;
        _material.setDiffuseColor(color);
    }
}

void LeapBoxButtonNode::setLabelText(string label_text){
    _label_text = label_text;
}

