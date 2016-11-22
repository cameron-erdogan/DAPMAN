//
//  LeapUtil.cpp
//  DAPMAN
//
//  Created by Cameron Erdogan on 10/17/16.
//  Copyright © 2016 Cameron Erdogan. All rights reserved.
//

#include <fstream>
#include <sstream>
#include <unistd.h>
#include "LeapUtil.hpp"
#include "Printer.hpp"

using namespace std;
using namespace Leap;

namespace LeapUtil {
    
    vector<Frame> takeSamples(const Controller& controller, int num_samples, float sample_rate){
        
        vector<Frame> frames;

        typedef std::chrono::steady_clock clock;
        chrono::time_point<clock> start;
        start = clock::now();
        
        int capture_counter = 0;
        if(controller.isConnected() == true){
            while(capture_counter < num_samples){
                std::chrono::duration<double> elapsed = clock::now() - start;
                
                if(elapsed.count() > sample_rate) {
                    cout << "sampled frame " << endl;
                    frames.push_back(controller.frame());
                    
                    start = clock::now();
                    capture_counter++;
                }
            }
        }
        return frames;
    }
    
    bool heatCheck(std::vector<Frame>& frames, float confidence){
        bool still_confident = true;
        for (auto& frame: frames) {
            Hand hand = frame.hands().frontmost();
            if(hand.isValid() == false || hand.confidence() < confidence)
                still_confident = false;
        }
        
        return still_confident;
    }
    
    bool compareFrames(std::vector<Frame>& input_frames, std::vector<Frame>& saved_frames){
        bool match_so_far = true;
        stringstream debug_output;
        
        //check we have same number of frames
        if(input_frames.size() != saved_frames.size()){
            cout << "different number of frames!" << endl;
            return false;
        }
        
        for(std::size_t i = 0; i != input_frames.size(); i++){
            match_so_far = compareFrame(input_frames[i], saved_frames[i]);
            
            if(match_so_far == false)
                break;
        }
        
        if(match_so_far)
            debug_output << "sequences match!";
        else
            debug_output << "don't match!";

        //sort of a gross way to handle debugging
        cout << debug_output.str() << endl;
        
        return match_so_far;
    }
    
    bool compareFrame(Frame input_frame, Frame saved_frame){
        Hand input_hand = input_frame.hands().frontmost();
        Hand saved_hand = saved_frame.hands().frontmost();
        bool match_so_far = true;
        stringstream debug_output;
        
        //check both hands are valid
        if(input_hand.isValid() == false || saved_hand.isValid() == false){
            match_so_far = false;
            debug_output << "one of the hands is invalid\n";
        }else
            debug_output << "hands valid\n";
        
        //check both hands are either left or right
        if(input_hand.isLeft() != saved_hand.isLeft()){
            match_so_far = false;
            debug_output << "hands don't match\n";
        }else
            debug_output << "hands match\n";
        
        //compare rotation of hand
        Leap::Vector input_normal = input_hand.palmNormal();
        Leap::Vector saved_normal = saved_hand.palmNormal();
        float delta_roll = distanceBetweenAngles(input_normal.roll() * 180.0 / M_PI, saved_normal.roll() * 180.0 / M_PI);
            debug_output << "delta roll " << delta_roll << "\n";
        
        if(delta_roll > 30){
            match_so_far = false;
            debug_output << "one of the angles isn't valid\n";
        }else
            debug_output << "angles match\n";
        
        //compare extended fingers
        if(compareExtendedFingers(input_hand, saved_hand) == false){
            match_so_far = false;
            debug_output << "fingers don't match\n";
        }else
            debug_output << "fingers match\n";
        
         cout << debug_output.str() << endl;
        
        return match_so_far;
    }

    float distanceBetweenAngles(float a, float b){
        float diff = abs(a - b);
        float distance = diff > 180 ? 360 - diff : diff;
        return distance;
    }
    
    bool compareExtendedFingers(const Hand& a, const Hand& b){
        Leap::FingerList a_fingers = a.fingers().extended();
        Leap::FingerList b_fingers = b.fingers().extended();
        
        if(a_fingers.count() == b_fingers.count()){
            //i've empirically determined that .extended() returns fingers in sorted order
            //if it actually doesn't, this could cause problems
            for(int i = 0; i < a_fingers.count(); i++){
                if(a_fingers[i].type() != b_fingers[i].type())
                    return false;
            }
            return true;
        }else
            return false;
    }
    
    bool fileExists(std::string filename){
        ifstream f(filename.c_str());
        return f.good();
    }

    
    //serializeFrames and deserializeFrames have been taken almost verbatim from the Leap docs
    void serializeFrames(std::vector<Frame>& frames, std::string filename){
        
        //saves file in DAPMAN/bin/DAPMAN(Debug).app/Contents/Resources by default
//        char * dir = getcwd(NULL, 0); // Platform-dependent, see reference link below
//        printf("Current dir: %s", dir);
        
        //filename should be something like "frames.data"
        std::string outFilename = filename;
        std::fstream out(outFilename, std::ios_base::trunc | std::ios_base::out);
        if(out)
        {
            for(std::size_t i = 0; i < frames.size(); i++){
                Leap::Frame frameToSerialize = frames[i];
                std::string serialized = frameToSerialize.serialize();
                out << (long)serialized.length() << serialized;
            }
            out.flush();
            out.close();
            
            std::cout << "successfully saved files" << std::endl;
        }
        else if(errno) {
            std::cout << "Error: " << errno << std::endl;
            std::cout << "Couldn't open " << outFilename << " for writing." << std::endl;
        }
    }
    
    std::vector<Frame> deserializeFrames(std::string filename){
        
        std::vector<Leap::Frame> deserializedFrames;
        std::string inFilename = filename;
        std::ifstream in(inFilename, std::fstream::in);
        std::string contents;
        if (in)
        {
            in.seekg(0, std::ios::beg);
            long nextBlockSize = 0;
            in >> nextBlockSize;
            while (!in.eof())
            {
                contents.resize(nextBlockSize);
                in.read(&contents[0], nextBlockSize);
                Leap::Frame newFrame;
                newFrame.deserialize(contents);
                if(newFrame.isValid()) deserializedFrames.push_back(newFrame);
                in >> nextBlockSize;
            }
            in.close();
        }
        else if(errno){
            std::cout << "Error: " << errno << std::endl;
            std::cout << "Couldn't open " << inFilename << " for reading." << std::endl;
        }
        
        return deserializedFrames;
    }
    
    
    void printFrameStuff(Frame& frame){
        
        if(frame.hands().isEmpty() == false){
            Hand hand = frame.hands().frontmost();
            float roll = hand.palmNormal().roll() * M_PI/180.0;
            float pitch = hand.palmNormal().pitch() * M_PI/180.0;
            float yaw = hand.palmNormal().yaw() * M_PI/180.0;
            
            cout << "\tconfidence:\t " << hand.confidence() << endl;
            cout << "\tfingers ext:\t" << hand.fingers().extended().count() << endl;
            cout << "\troll: " << roll << "\tpitch: " << pitch << "\tyaw: " << yaw <<endl;
            
        }else{
            cout << "no hands!" << endl;
        }
    }
}

