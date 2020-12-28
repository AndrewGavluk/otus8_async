#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <memory>
#include <ctime>
#include <sstream>   
#include <stdio.h> 

#include "ConsolePrinter.h"
#include "FilePrinter.h"

class interpreter
{
    public:
        interpreter(size_t i, bool);
        ~interpreter();
        void push_back(std::shared_ptr<Printer> );
        void processStream();
        void putString(std::string);
        void putEOF();
        void StartTread();

    protected: 
        std::vector<std::string> m_block;
    private:  
        bool getString(std::string&);
        void print(std::time_t & );
        std::list< std::shared_ptr<Printer> > m_outputs;
        std::stringstream m_sstrm;
        size_t m_bulkSize;
        std::thread m_thread;
        bool useThread;
};

interpreter::interpreter(size_t size, bool CreateThread) : m_bulkSize{size}, useThread{CreateThread}  {
       
}

interpreter::~interpreter(){
    
    if (m_thread.joinable())
        m_thread.join();
}

void interpreter::push_back(std::shared_ptr<Printer> printer)
{
    m_outputs.push_back(printer);
}

void interpreter::StartTread()
{
    m_thread = std::thread (&interpreter::processStream, this);
}
void interpreter::print(std::time_t & time)
{
    std::string stime{std::to_string(time)};
    stime=std::to_string(time);
        for (auto& outs : m_outputs){
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

    //while(!m_sstrm.eof() && std::getline(m_sstrm, input)){
    while(!std::cin.eof() && std::getline(std::cin, input)){
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
    putEOF();
}

void interpreter::putString(std::string buf)
{
    m_sstrm << buf;
}

void interpreter::putEOF()
{
    for (auto& outs : m_outputs){
            outs->setEOF();
        }
}


bool interpreter::getString(std::string& buf)
{
    return static_cast<bool>( std::getline(m_sstrm, buf));
}