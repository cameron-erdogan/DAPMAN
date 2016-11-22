//
//  LeapBox.cpp
//  DAPMAN
//
//  Created by Cameron Erdogan on 10/27/16.
//
//

#include "LeapBox.hpp"

using namespace std;

LeapBox::LeapBox(){
}

void LeapBox::setup(){
    hand_radius = MIN(ofGetWidth(), ofGetHeight()) / 20.0;
    
    root.setPosition(ofGetWidth()/2.0, ofGetHeight()/2.0, 0);
    
    hand_sphere.setParent(root);
    hand_sphere.setRadius( hand_radius );
    
    timer_circle.setParent(hand_sphere);
    timer_circle.setup();
    timer_circle.setRadius(hand_radius * 1.2);
    
    hand_shadow.setRadius(hand_radius);
    hand_shadow.setParent(root);
    
    material.setShininess( 128 );
    material.setSpecularColor(ofColor(255, 255, 255, 255));
    
    connectToLeap();
    
    //buttons and stuff
    reset_code_button.setParent(root);
    reset_code_button.setup(ofVec3f(box_size.x/2.0, box_size.y, box_size.z));
    reset_code_button.setPosition(ofVec3f(-box_size.x/4.0, 0, 0));
    reset_code_button.setLabelText("Reset Code");
    
    finished_button.setParent(root);
    finished_button.setup(ofVec3f(box_size.x/2.0, box_size.y, box_size.z));
    finished_button.setPosition(ofVec3f(box_size.x/4.0, 0, 0));
    finished_button.setLabelText("Finish");
    
    progress_dots.setParent(root);
    progress_dots.setPosition(0, -box_size.y / 2.0, 0);
    //get the number of progress dots from the serialized code
    progress_dots.setup(4, 10, 300);
    progress_dots.fillDots(0);
    
    status_pos = ofVec3f(ofGetWidth() / 2.0 - 100, 20.0, 0);
    
    
//    if(LeapUtil::fileExists("custom_code.data") == true){
//        _saved_frames = LeapUtil::deserializeFrames("custom_code.data");
//    }else{
        _saved_frames = LeapUtil::deserializeFrames("code.data");
//    }
    
//    takeSamples(4, 1.2);
    ofBackgroundGradient(ofColor::white, ofColor::whiteSmoke, OF_GRADIENT_CIRCULAR);

    
}

void LeapBox::update(){
    updateLeapPositions();
    
    bool hand_in_finished_button = finished_button.checkHandInBounds(hand_sphere, true);
    bool hand_in_reset_button = reset_code_button.checkHandInBounds(hand_sphere, true);
    int extended_fingers = controller.frame().hands().frontmost().fingers().extended().count();
    
    switch(_state){
        case looking_for_hand:
            
            if(is_hand == true && _saved_frames.size() > 0){
                
                //should look for start gesture
                //for now this is just a closed fist
               
                if(extended_fingers == 0){
                    _state = attempting_to_unlock;
                    takeSamples(_saved_frames.size(), 1.2);
                }

            }
            break;
            
        case attempting_to_unlock:
            
            updateTimerAndSamples();
            
            break;
        case wrong_code_cooldown:
        {
            std::chrono::duration<double> elapsed = _clock::now() - _start_time;
            if(elapsed.count() > _cooldown_time){
                _state = looking_for_hand;
//                ofBackground(20);
            }
            
            break;
        }
            
        case unlocked:
            
            //listen for
            if(extended_fingers == 0){
                //check to see if the hand is in a button
                if(hand_in_reset_button == true){
//                    setCooldown(2, AppState::set_new_code, "prepare new code");
                    _state = AppState::set_new_code;
                    takeSamples(_saved_frames.size(), 1.2);
                    
                }else if(hand_in_finished_button == true){
                    //maybe should have a cool down here too
                    setCooldown(1, looking_for_hand);
                }
            }
            
            break;
            
        case set_new_code:
            
            updateTimerAndSamples();
            break;
        
        case cooldown:
            
            std::chrono::duration<double> elapsed = _clock::now() - _start_time;
            if(elapsed.count() > _cooldown_time){
                _state = _post_cooldown_state;
                
                if(_state == set_new_code || _state == looking_for_hand)
                    takeSamples(_saved_frames.size(), 1.2);
                //                ofBackground(20);
            }
            break;
            
    }
}

void LeapBox::draw(){
    //state specific stuff
    switch(_state){
        case looking_for_hand:
            ofDrawBitmapString("looking for hand", status_pos);
            ofBackgroundGradient(ofColor::white, ofColor::whiteSmoke, OF_GRADIENT_CIRCULAR);
            break;
            
        case attempting_to_unlock:
            ofDrawBitmapString("reading gestures", status_pos);
            ofBackgroundGradient(ofColor::white, ofColor::whiteSmoke, OF_GRADIENT_CIRCULAR);
            break;
            
        case wrong_code_cooldown:
            ofDrawBitmapString("wrong code!", status_pos);
            
            ofBackgroundGradient(ofColor::white, ofColor::paleVioletRed, OF_GRADIENT_CIRCULAR);
            break;
            
        case unlocked:
            ofDrawBitmapString("unlocked!", status_pos);
            ofBackgroundGradient(ofColor::white, ofColor::paleGreen, OF_GRADIENT_CIRCULAR);
            
            break;
        
        case set_new_code:
            ofDrawBitmapString("reading new code", status_pos);
            ofBackgroundGradient(ofColor::white, ofColor::blanchedAlmond, OF_GRADIENT_CIRCULAR);
            break;
        
        case cooldown:
            ofDrawBitmapString(_cooldown_message, status_pos);
            ofBackgroundGradient(ofColor::white, ofColor::whiteSmoke, OF_GRADIENT_CIRCULAR);
            break;
            
    }
    
    if(is_hand == true){
        //draw sphere
        material.begin();
        ofFill();
        hand_sphere.draw();
        material.end();
        
        //should draw an arc around the handsphere
        ofSetColor(255, 0, 0);
        ofNoFill();
        
        hand_shadow.draw();
        timer_circle.draw();
    }
    
    progress_dots.draw();
    
    ofSetColor(255, 0, 0);
    ofNoFill();
    //fudge the size a bit so the circle doesn't overlap bounds?
    ofDrawBox(root.getPosition(), box_size.x, box_size.y, box_size.z);
    

    
    //draw transparent stuff
    //according to openframeworks documentation you have to draw all the opaque stuff before you
    //draw any transparent stuff. Not 100% sure why this is.
    if(_state == unlocked){
        reset_code_button.draw();
        finished_button.draw();

    }

}

//more like "prepare to take samples"
void LeapBox::takeSamples(int num_samples, float sample_rate){
    
//    if(_state != attempting_to_unlock){
//        _state = attempting_to_unlock;
        _start_time = _clock::now();
        _samples.clear();
        _num_samples = num_samples;
        _sample_rate = sample_rate;
        
//    }
}

//specifically for wrong code cooldown
//we change the background color specifically for wrong code state
void LeapBox::setWrongCodeCooldown(float cooldown_time){
   
    progress_dots.fillDots(0);
    _state = wrong_code_cooldown;
    _start_time = _clock::now();
    _cooldown_time = cooldown_time;
    
}

//for generic cooldowns
void LeapBox::setCooldown(float cooldown_time, AppState next_state){
    _state = cooldown;
    _start_time = _clock::now();
    _cooldown_time = cooldown_time;
    _post_cooldown_state = next_state;
    _cooldown_message = "";
}

void LeapBox::setCooldown(float cooldown_time, AppState next_state, string message){
    _state = cooldown;
    _start_time = _clock::now();
    _cooldown_time = cooldown_time;
    _post_cooldown_state = next_state;
    _cooldown_message = message;
}

void LeapBox::updateTimerAndSamples(){

    if(_state == attempting_to_unlock || _state == set_new_code){
        std::chrono::duration<double> elapsed = _clock::now() - _start_time;
        
        if(elapsed.count() > _sample_rate){
            _samples.push_back(controller.frame());
            progress_dots.fillDots(_samples.size());
            cout << "take sample " << _samples.size() << endl;
            _start_time = _clock::now();
            
        }else{
            timer_circle.setCirclePercent(elapsed.count() / _sample_rate);
        }
        
        if(_samples.size() >= _num_samples){

            timer_circle.setCirclePercent(0);
            //means we're done
            //in an ideal world, I process samples on a different thread than the UI
            processSamples();
        }
    }
}

void LeapBox::updateLeapPositions(){
    if(controller.isConnected() == true && controller.frame().isValid() == true){
        
        Frame frame = controller.frame();
        interaction_box = frame.interactionBox();
        ///want to use the x (left to right) and z (forward and back) axes for drawing floor
        float min_dimension = MIN(ofGetWidth(), ofGetHeight());
        box_size = calculateInteractionBox(interaction_box, min_dimension * 0.6);
        
        Hand h = frame.hands().frontmost();
        if(h.isValid() == true){
            is_hand = true;
            
            Leap::Vector last_normalized_hand = interaction_box.normalizePoint(h.palmPosition());
            ofVec3f normalized_hand = ofVec3f(last_normalized_hand.x, 1.0 - last_normalized_hand.y, last_normalized_hand.z) - ofVec3f(0.5, 0.5, 0.5);
            
            //convert normalized hand position to box size
            ofVec3f sphere_pos = normalized_hand * box_size;
            
            hand_sphere.setPosition(sphere_pos);
            hand_shadow.setPosition(sphere_pos.x, box_size.y / 2.0, sphere_pos.z);
        }
        else{
            is_hand = false;
        }
    }
    
}

//makes use of the frame samples in _samples
//this is currently a useless function, but should verify the input samples match the serialized samples
void LeapBox::processSamples(){
    //print and serialize
    for(std::size_t i = 0; i != _samples.size(); i++) {
        LeapUtil::printFrameStuff(_samples[i]);
    }
//    LeapUtil::serializeFrames(_samples, "code.data");
    progress_dots.fillDots(0);

    if(_state == attempting_to_unlock){
        bool codes_match = LeapUtil::compareFrames(_samples, _saved_frames);
        if(codes_match == true){
            _state = unlocked;
            
            if(delegate)
                delegate -> unlock();
        }else{
            setWrongCodeCooldown(3);
        }
    }else if(_state == set_new_code){
        bool heat_check = LeapUtil::heatCheck(_samples, 0.7f);
        
        if(heat_check == true){
            LeapUtil::serializeFrames(_samples, "custom_code.data");
            _saved_frames = _samples;
            
            setCooldown(1.0, unlocked, "new code successfully created");
        }else{
            setCooldown(1.5, set_new_code, "uncertain reading, try again");
        }
    }
    
    
//    vector<Frame> saved_frames = LeapUtil::deserializeFrames("code.data");
//    for(std::size_t i = 0; i != saved_frames.size(); i++) {
//        LeapUtil::printFrameStuff(saved_frames[i]);
//    }
}

void LeapBox::connectToLeap(){
    
    typedef std::chrono::steady_clock clock;
    std::chrono::time_point<clock> start;
    start = clock::now();
    
    //wait for the controller to connect and for first valid frame, normally takes a few seconds
    std::chrono::duration<double> elapsed = clock::now() - start;
    while((controller.isConnected() == false || controller.frame().isValid() == false) && elapsed.count() < 4){
        elapsed = clock::now() - start;
    }
    
    if(controller.isConnected() == true && controller.frame().isValid()){
        cout << "controller connected!" << endl;
        Frame frame = controller.frame();
        interaction_box = controller.frame().interactionBox();
        
        float minDimension = MIN(ofGetWidth(), ofGetHeight());
        box_size = calculateInteractionBox(interaction_box, minDimension * 0.6);
        
    }
    else{
        cout << "controller not connected" << endl;
    }
}

ofVec3f LeapBox::calculateInteractionBox(Leap::InteractionBox box, float max_side){
    //find out which dimension is the greatest
    //use this as normalizer for other dimensions
    float max = MAX(box.width(), MAX(box.height(), box.depth()));
    
    float norm_w = box.width()/max;
    float norm_h = box.height()/max;
    float norm_d = box.depth()/max;
    
    //now return an ofVector scaled by what we want our max dimension to be
    return ofVec3f(norm_w * max_side, norm_h * max_side, norm_d * max_side);
}

