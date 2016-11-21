//
//  main.cpp
//  DAPMAN
//
//  Created by Cameron Erdogan on 10/13/16.
//  Copyright © 2016 Cameron Erdogan. All rights reserved.
//

#include <iostream>
#include <cstring>
#include "Leap.h"
#include "LeapUtil.hpp"

using namespace Leap;

//int main(int argc, const char * argv[]) {
//    // insert code here...
//    std::cout << "Hello, World!\n";
//    Controller controller;
//    
//    typedef std::chrono::steady_clock clock;
//    std::chrono::time_point<clock> start;
//    start = clock::now();
//
//    //wait for the controller to connect, normally takes a few seconds
//    std::chrono::duration<double> elapsed = clock::now() - start;
//    while(controller.isConnected() == false && elapsed.count() < 3){
//        elapsed = clock::now() - start;
//    }
//    
//    if(controller.isConnected() == true){
//        std::vector<Frame> frames = LeapUtil::takeSamples(controller, 4, 1.2);
//        for(std::size_t i = 0; i != frames.size(); i++){
//            std::cout << "frame " << i << std::endl;
//            LeapUtil::printFrameStuff(frames[i]);
//        }
//        
//        bool heat_check = LeapUtil::heatCheck(frames, 0.75);
//        std::cout << "heat check: " <<  heat_check << std::endl;
//        
//        LeapUtil::serializeFrames(frames, "frames.data");
//        std::vector<Frame> serializedFrames = LeapUtil::deserializeFrames("frames.data");
//        
//        LeapUtil::compareFrames(frames, serializedFrames);
//    }
//    else{
//        std::cout << "controller not connected" << std::endl;
//    }
//
//    return 0;
//}
