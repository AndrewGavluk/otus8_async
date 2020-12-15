
#pragma once
#include <string>

#include "lib_interpret.h"

class Printer
{
    public:
        Printer(){};
        virtual ~Printer(){};
        virtual void print(std::vector<std::string>& bulk, std::string& time) = 0 ;
    
};