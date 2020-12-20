#pragma once
#include <iostream>

#include "printer.h"

class ConsolePrinter : public Printer
{
    public:
        ConsolePrinter (size_t);
        void print(std::shared_ptr<Bulk> data) override;
        void printThread(size_t ) override;

        template <typename T>
        void initWith( std::shared_ptr<std::vector< T>>  ); 

    private:
};

template <typename T>
void ConsolePrinter::initWith( std::shared_ptr<std::vector<T>> ){
    size_t threadNumber{0};
    for (size_t i = 0; i < m_qthreads; ++i)
    {
        size_t buf{++threadNumber};
        m_threads.push_back(std::thread ( &ConsolePrinter::printThread, this, std::ref(buf)));
    }

    for (auto &i : m_threads)
        if (i.joinable())
                i.join();
}

ConsolePrinter::ConsolePrinter(size_t size = 1): Printer(size){

    std::shared_ptr<std::vector<std::ofstream> > streams;
    initWith(streams);

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
    bool result = getBulk(data);
    (void)(result);

    // TODO : check te result and process bulks while not eof
    
    /*std::string separator;
    std::cout << "bulk: ";
    for (auto &str : data->bulk){
        std::cout << separator << str << std::endl;
        separator = ",";
    }
    (void)time;*/
}