#pragma once
#include <iostream>

#include "printer.h"

class ConsolePrinter : public Printer
{
    public:
        ConsolePrinter (size_t);
        void print(std::shared_ptr<Bulk> data) override;
        void printThread(size_t& ) override;
    private:
};

// TODO : constructor for clas with streams vector 
ConsolePrinter::ConsolePrinter(size_t size = 1): Printer(size){

    std::shared_ptr<std::vector<std::ostream> > streams;
    streams->reserve(size);
    for (size_t i = 0; i<size; ++i){
        std::ofstream out1;
        streams->push_back(std::move(out1));
    }
    Printer::initWith(streams);
    // TODO : add call initwith
}

void ConsolePrinter::print(std::shared_ptr<Bulk> data) {
    Printer::print(data);
}

// TODO : add stream as parametr
void ConsolePrinter::printThread(size_t& threadNumber) {
    
    (void)(threadNumber);
    // TODO : 1. eof check: while not eof read bulk
    // TODO : 2. add thread id
    // TODO std::cout from vector threadNumber

    auto data = getBulk();
    std::string separator;
    std::cout << "bulk: ";
    for (auto &str : data->bulk){
        std::cout << separator << str << std::endl;
        separator = ",";
    }
    (void)time;
}