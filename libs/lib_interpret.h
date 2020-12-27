#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <memory>
#include <ctime>
#include <sstream>   

#include "ConsolePrinter.h"
#include "FilePrinter.h"

class interpreter
{
    public:
        interpreter(size_t i);
        void push_back(std::shared_ptr<Printer> );
        void removeOutput(std::ostream&);
        void processStream();

    protected: 
        std::vector<std::string> m_block;
        
    private:   
        void print(std::time_t & );
        std::list< std::shared_ptr<Printer> > m_outputs;
        std::stringstream m_sstrm;
        size_t m_bulkSize;
};

interpreter::interpreter(size_t size) : m_bulkSize{size}{}

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
            outs->print(buf);
        }
        m_block.clear();
    time=0;
}

void interpreter::processStream()
{
    size_t level{0};
    std::string input;
    std::time_t time=0;

    while(!m_sstrm.eof() && std::getline(m_sstrm, input)){
        if ( input=="{" && level++ ) continue;
        if ( input=="}" && --level ) continue; 
        
        if (!time)  time = std::time(nullptr);

        if (input=="}" || input=="{")
            print(time);
        
        else{// if string is not brackets print block, then push it to block, 
            m_block.push_back(input); 
            if(m_block.size() >= m_bulkSize && !level )
                print(time);
        }  
    }
}