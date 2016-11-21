//
//  CircleArcNode.cpp
//  DAPMAN
//
//  Created by Cameron Erdogan on 10/31/16.
//
//

#include "CircleArcNode.hpp"

void CircleArcNode::customDraw(){
    _circle_path.draw();
}

void CircleArcNode::setup(){
    _circle_path.setCircleResolution(360);
    _circle_path.setStrokeWidth(3);
    _circle_path.setFilled(false);
    _circle_path.setStrokeColor(ofColor::red);
}

void CircleArcNode::setCirclePercent(float percent){
    
    if(percent > 0 && percent <= 1){
        //setup path stuff here too
        _circle_path.clear();
        _circle_path.moveTo(0, -_radius);
        
        //calculate appropriate percent. 0 percent mark is at 12 o clock
        //percent is a value between 0 and 1
        /*
         percent / 1 = x / 360
         ---> 360 * percent = x
         */
        _circle_path.arc(0, 0, _radius, _radius, -90, 360*percent - 90);
    }else if (percent == 0){
        
        _circle_path.clear();
    }
   
}


void CircleArcNode::setRadius(float radius){
    _radius = radius;
}
