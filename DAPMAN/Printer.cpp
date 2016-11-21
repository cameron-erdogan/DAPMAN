//
//  Printer.cpp
//  DAPMAN
//
//  Created by Cameron Erdogan on 10/17/16.
//  Copyright © 2016 Cameron Erdogan. All rights reserved.
//

#include <iostream>
#include "Printer.hpp"

namespace Printer {
    
    void debug_print(std::string print_string, int priority){
        if(debug_on == true){
            if(priority >= debug_threshold){
                std::cout << print_string << std::endl;
            }
        }
    }

}
