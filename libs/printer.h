
#pragma once
#include <string>

#include "lib_interpret.h"

class Printer
{
    public:
        Printer() = default;
        virtual ~Printer() = default;
        virtual void print(std::vector<std::string>& bulk, std::string& time) = 0 ;
    
};