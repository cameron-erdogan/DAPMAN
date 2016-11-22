//
//  LeapUtil.hpp
//  DAPMAN
//
//  Created by Cameron Erdogan on 10/17/16.
//  Copyright © 2016 Cameron Erdogan. All rights reserved.
//

#ifndef LeapUtil_hpp
#define LeapUtil_hpp

#include <stdio.h>
#include <cstring>
#include "Leap.h"

using namespace Leap;

namespace LeapUtil {
    
    std::vector<Frame> takeSamples(const Controller& controller, int num_samples, float sample_rate);
        
    bool heatCheck(std::vector<Frame>& frames, float confidence);
    
    
    bool compareFrames(std::vector<Frame>& input_frames, std::vector<Frame>& saved_frames);
    
    bool compareFrame(Frame input_frame, Frame saved_frame);
    
    float distanceBetweenAngles(float a, float b);
    
    bool compareExtendedFingers(const Hand& a, const Hand& b);
    
    bool fileExists(std::string filename);
    
    void serializeFrames(std::vector<Frame>& frames, std::string filename);
    
    std::vector<Frame> deserializeFrames(std::string filename);
    
    void printFrameStuff(Frame& frame);
    
}


//DONE
//def take_samples(controller, num_samples):

//DONE
//def heat_check(frames):

//DONE
//def compare_frames(input_frames, saved_frames):

//DONE
//# this expects input in degrees, between -180 and 180
//def distance_between_angles(angle_a, angle_b):

//DONE
//# pass in hand objects
//# (broke this into a separate function because it's sorta gross
//def compare_extended_fingers(hand_a, hand_b):

//# make filename something like "frames.data"
//def serialize_frames(frames, filename):

//def deserialize_frames(filename):

//DONE
//def print_frame_stuff(frame):

#endif /* LeapUtil_hpp */
