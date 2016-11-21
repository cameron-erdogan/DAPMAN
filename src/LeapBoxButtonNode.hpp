//
//  LeapBoxButtonNode.hpp
//  DAPMAN
//
//  Created by Cameron Erdogan on 11/11/16.
//
//

#ifndef LeapBoxButtonNode_hpp
#define LeapBoxButtonNode_hpp

#include <stdio.h>
#include "ofMain.h"

class LeapBoxButtonNode : public ofNode{
    
public:
    void setup(ofVec3f size);
    void customDraw();
    bool checkHandInBounds(ofNode& hand, bool highlight = false);
    void setLabelText(string label_text);
    
    
private:
    void updateHighlight(bool should_highlight);
    
    ofVec3f _position;
    ofVec3f _dimensions;
    ofBoxPrimitive _box;
    ofMaterial _material;
    string _label_text;
};

#endif /* LeapBoxButtonNode_hpp */
