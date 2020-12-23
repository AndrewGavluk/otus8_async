#pragma once
#include <iostream>

#include "printer.h"

class ConsolePrinter : public Printer
{
    public:
        ConsolePrinter ();
        ~ConsolePrinter (){};
        void printThread(size_t ) override;
};

ConsolePrinter::ConsolePrinter() : Printer(1)
{
    m_threads.push_back(std::thread ( &ConsolePrinter::printThread, this, 0));
}

void ConsolePrinter::printThread(size_t threadNumber) {
    
    (void)(threadNumber);
    shar_line_t data;
    std::string separator;

    while(m_queue.pop(data))
        printInfo( data, separator, std::cout);
    
}