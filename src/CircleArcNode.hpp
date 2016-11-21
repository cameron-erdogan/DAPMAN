//
//  CircleArcNode.hpp
//  DAPMAN
//
//  Created by Cameron Erdogan on 10/31/16.
//
//

#ifndef CircleArcNode_hpp
#define CircleArcNode_hpp

#include <stdio.h>
#include "ofMain.h"

class CircleArcNode : public ofNode{
    
public:
    void setRadius(float radius);
    void customDraw();
    void setup();//initializes circlePath stuff. doesn't set radius
    void setCirclePercent(float percent); //please call setup and setRadius before this
    
private:
    float _radius;
    ofPath _circle_path;
};

#endif /* CircleArcNode_hpp */
