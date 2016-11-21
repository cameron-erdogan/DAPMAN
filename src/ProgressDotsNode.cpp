//
//  ProgressDotsNode.cpp
//  DAPMAN
//
//  Created by Cameron Erdogan on 11/2/16.
//
//

#include "ProgressDotsNode.hpp"

void ProgressDotsNode::customDraw(){
    ofSetColor(ofColor::red);
    ofFill();
    ofSetCircleResolution(25);
        
    for(std::size_t i = 0; i < _dot_positions.size(); i++){
        //start darwing outline only dots on the filled_dots-th dot
        if(i == _filled_dots)
            ofNoFill();
        
        ofDrawCircle(_dot_positions[i], _radius);
    }
}

void ProgressDotsNode::setup(int num_dots, float dot_radius, float width){
    _radius = dot_radius;
    
    //should calculate positions for dots here
    _dot_positions.clear();
    

    float leftPos = - width / 2.0;
    float spacing = width / (num_dots - 1);
    
    if(num_dots == 1){
        //special case for 1
        _dot_positions.push_back(ofVec2f::zero());
    }else{
        for(int i = 0; i < num_dots; i++){
            _dot_positions.push_back(ofVec2f(leftPos + spacing * i, 0));
        }
    }
    
    
    // o --- o --- o --- o
    // o ------ o ------ o
    // o --------------- o
    //          o
}

void ProgressDotsNode::fillDots(int filled_dots){
    _filled_dots = filled_dots;
}
