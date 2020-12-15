#pragma once
#include <iostream>

#include "printer.h"

class ConsolePrinter : public Printer
{
    public:
        ConsolePrinter (std::ostream&);
        void print(std::vector<std::string>& bulk, std::string& time) override;
    private:
        std::ostream& out;
};

ConsolePrinter::ConsolePrinter(std::ostream& _out) : out{_out} {}

void ConsolePrinter::print(std::vector<std::string>& bulk, std::string& time) {
    
    std::string separator;
    std::cout << "bulk: ";
    for (auto &str : bulk){
        std::cout << separator << str << std::endl;
        separator = ",";
    }
    (void)time;
    std::cout << "to_console\n";

}