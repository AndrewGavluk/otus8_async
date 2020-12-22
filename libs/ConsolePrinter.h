#pragma once
#include <iostream>

#include "printer.h"

class ConsolePrinter : public Printer
{
    public:
        ConsolePrinter ();
        ~ConsolePrinter ();
        void print(std::shared_ptr<Bulk> data) override;
        void printThread(size_t ) override;
        void initWith(); 

    private:
};

ConsolePrinter::ConsolePrinter() : Printer(1)
{
    size_t threadNumber{0};
    for (size_t i = 0; i < m_qthreads; ++i)
    {
        size_t buf{++threadNumber};
        m_threads.push_back(std::thread ( &ConsolePrinter::printThread, this, std::ref(buf)));
    }
}

ConsolePrinter::~ConsolePrinter()
{
    for (auto &i : m_threads)
        if (i.joinable())
                i.join();

}

void ConsolePrinter::print(std::shared_ptr<Bulk> data) {
    Printer::print(data);
}

void ConsolePrinter::printThread(size_t threadNumber) {
    
    (void)(threadNumber);
    // TODO : 1. eof check: while not eof read bulk
    // TODO : 2. add thread id
    // TODO std::cout from vector threadNumber
    
    shar_line_t data;
    std::string separator;

    while(getBulk(data)){
        separator = "";
        std::cout << "bulk: ";
        for (auto &str : data->bulk){
            std::cout << separator << str << std::endl;
            separator = ",";
        }
    }
}