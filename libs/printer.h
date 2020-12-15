
#pragma once
#include <string>

#include "lib_interpret.h"

struct Bulk
{
    Bulk (std::vector<std::string>& _bulk, std::string& _time) :  bulk{_bulk}, time{_time} {}
    std::vector<std::string> bulk;
    std::string time;
};

class Printer
{
    public:
        Printer(){};
        virtual ~Printer(){};
        virtual void print(std::shared_ptr<Bulk> data) = 0 ;
    
};