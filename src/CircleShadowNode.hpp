//
//  CircleShadowNode.hpp
//  DAPMAN
//
//  Created by Cameron Erdogan on 10/27/16.
//
//

#ifndef CircleShadowNode_hpp
#define CircleShadowNode_hpp

#include <stdio.h>
#include "ofMain.h"

class CircleShadowNode : public ofNode{
    
public:
    void setRadius(float radius);
    void customDraw();
    
private:
    float _radius;
};

#endif /* CircleShadowNode_hpp */
