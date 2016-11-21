//
//  Printer.hpp
//  DAPMAN
//
//  Created by Cameron Erdogan on 10/17/16.
//  Copyright © 2016 Cameron Erdogan. All rights reserved.
//

#ifndef Printer_hpp
#define Printer_hpp

#include <string>

namespace Printer {
    static bool debug_on = true;
    static int debug_threshold = 3;
    void debug_print(std::string print_string, int priority = 3);
}

#endif /* Printer_hpp */
