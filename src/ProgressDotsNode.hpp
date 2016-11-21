//
//  ProgressDotsNode.hpp
//  DAPMAN
//
//  Created by Cameron Erdogan on 11/2/16.
//
//

#ifndef ProgressDotsNode_hpp
#define ProgressDotsNode_hpp

#include <stdio.h>
#include "ofMain.h"

class ProgressDotsNode : public ofNode{
    
public:
    void setup(int num_dots, float dot_radius, float width);
    void fillDots(int filled_dots);
    void customDraw();
    
private:
    std::vector<ofVec2f> _dot_positions;
    float _radius;
    int _filled_dots;
    
};


#endif /* ProgressDotsNode_hpp */
