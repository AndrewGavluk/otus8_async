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

