#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <memory>
#include <ctime>

#include "printer.h"

class interpreter
{
    public:
        interpreter(int i);
        void push_back(std::shared_ptr<Printer> );
        void removeOutput(std::ostream&);
        void processStream(std::istream&);

    protected: 
        std::vector<std::string> m_block;
        
    private:   
        void print(std::time_t & );
        std::list< std::shared_ptr<Printer> > m_outputs;
        size_t m_bulkSize;
};

interpreter::interpreter(int size) : m_bulkSize{static_cast<size_t>(size)}{}

void interpreter::push_back(std::shared_ptr<Printer> printer)
{
    m_outputs.push_back(printer);
}

void interpreter::print(std::time_t & time)
{
    std::string stime{std::to_string(time)};
    stime=std::to_string(time);
        for (auto outs : m_outputs){
            auto buf = std::make_shared<Bulk>(m_block, stime);
            outs->pushQueue(buf);
        }
        m_block.clear();
    time=0;
}

void interpreter::processStream(std::istream& iss)
{
    size_t level{0};
    std::string input;
    std::time_t time=0;

    while(std::getline(iss, input)){
        if ( input=="{" && level++ ) continue;
        if ( input=="}" && --level ) continue; 
        
        if (!time)  time = std::time(nullptr);

        if (input=="}" || input=="{")
            print(time);
        
        else{   // if string is not brackets print block, then push it to block, 
            m_block.push_back(input); 
            if(m_block.size() >= m_bulkSize && !level )
                print(time);  
        }  
    }
}