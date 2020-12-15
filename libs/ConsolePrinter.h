#pragma once
#include <iostream>

#include "printer.h"

class ConsolePrinter : public Printer
{
    public:
        ConsolePrinter (std::ostream&);
        void print(std::shared_ptr<Bulk> data) override;
    private:
        std::ostream& out;
};

ConsolePrinter::ConsolePrinter(std::ostream& _out) : out{_out} {}

void ConsolePrinter::print(std::shared_ptr<Bulk> data) {
    
    std::string separator;
    std::cout << "bulk: ";
    for (auto &str : data->bulk){
        std::cout << separator << str << std::endl;
        separator = ",";
    }
    (void)time;
    std::cout << "to_console\n";

}