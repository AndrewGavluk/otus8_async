#pragma once

#include <list>
#include <ctime>
#include <sstream>   
#include <stdio.h> 

#include "ConsolePrinter.h"
#include "FilePrinter.h"

class interpreter
{
    public:
        interpreter(size_t i);
        ~interpreter();
        void push_back(std::shared_ptr<Printer> );
        void processStream();
        void putString(std::string);
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
