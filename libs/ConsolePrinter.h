#pragma once
#include <iostream>

#include "printer.h"

class ConsolePrinter : public Printer
{
    public:
        ConsolePrinter (size_t);
        void print(std::shared_ptr<Bulk> data) override;
        void printThread(size_t ) override;
    private:
};
ConsolePrinter::ConsolePrinter(size_t size = 1): Printer(size){

    std::shared_ptr<std::vector<std::ofstream> > streams;
    Printer::initWith(streams);

}

void ConsolePrinter::print(std::shared_ptr<Bulk> data) {
    Printer::print(data);
}

void ConsolePrinter::printThread(size_t threadNumber) {
    
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