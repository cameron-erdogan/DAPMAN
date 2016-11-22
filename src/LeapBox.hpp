//
//  LeapBox.hpp
//  DAPMAN
//
//  Created by Cameron Erdogan on 10/27/16.
//
//

#ifndef LeapBox_hpp
#define LeapBox_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Leap.h"
#include "LeapUtil.hpp"
#include "CircleShadowNode.hpp"
#include "CircleArcNode.hpp"
#include "ProgressDotsNode.hpp"
#include "LeapBoxButtonNode.hpp"

class LeapBoxDelegate {
public:
    // pure virtual functions
    virtual void unlock() = 0;
    virtual void lock() = 0;
};

class LeapBox{
    
public:
    LeapBox();
    void setup();
    void draw();
    void update();
    void takeSamples(int num_samples, float sample_rate);

    LeapBoxDelegate* delegate;
    
    Leap::Controller controller;
    Leap::InteractionBox interaction_box;
    bool is_hand;

    ofNode root;
    ofVec3f box_size;
    
    float hand_radius;
    ofMaterial material;
    
    //stuff I'm drawing. These are all ofNodes
    CircleShadowNode hand_shadow;
    ofSpherePrimitive hand_sphere;
    CircleArcNode timer_circle;
    ProgressDotsNode progress_dots;
    ofVec3f status_pos;
    
    //buttons for unlocked state
    //would be nice to eventually encapsulate into a better organizational structure
    LeapBoxButtonNode reset_code_button;
    LeapBoxButtonNode finished_button;
    

private:
    enum AppState{looking_for_hand, attempting_to_unlock, wrong_code_cooldown, unlocked, set_new_code, cooldown};
    
    void connectToLeap();
    ofVec3f calculateInteractionBox(Leap::InteractionBox box, float max_side);
    void updateLeapPositions();
    void updateTimerAndSamples();
    void processSamples();
    
    //state cooldown stuff
    void setWrongCodeCooldown(float cooldown_time);
    void setCooldown(float cooldown_time, AppState next_state);
    void setCooldown(float cooldown_time, AppState next_state, string message);
    //what do I need a state enum for?
    
    /**
     - looking_for_hand
     - attempting to unlock
     - wrong_code_cooldown
     - unlocked
     **/
    AppState _state = looking_for_hand;
    AppState _post_cooldown_state = looking_for_hand;
    string _cooldown_message;
    
    //this is the saved code that should "unlock" dapman
    std::vector<Leap::Frame> _saved_frames;
    
    typedef std::chrono::steady_clock _clock;
     chrono::time_point<_clock> _start_time;
    
    bool _is_taking_samples = false;
    int _num_samples;
    float _sample_rate;  //in seconds/sample
    float _cooldown_time;
    std::vector<Leap::Frame> _samples;
   
   
    
};



#endif /* LeapBox_hpp */
