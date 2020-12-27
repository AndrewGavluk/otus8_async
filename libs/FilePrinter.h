#pragma once

#include <fstream>
#include "printer.h"

class FilePrinter : public  Printer
{
    public:
        FilePrinter(size_t size);
        ~FilePrinter(){};
        void printThread(size_t threadNumber) override;
    private:
        std::ofstream m_ofstream;
};

FilePrinter::FilePrinter(size_t size): Printer(size)
{
    for (size_t i = 0; i < m_qthreads; ++i)
        m_threads.push_back(std::thread ( &FilePrinter::printThread, this, i ));
}

void FilePrinter::printThread(size_t threadNumber){
    
    
    std::shared_ptr<Bulk> data;
    std::string separator;

    while(m_queue.pop(data)){
        m_ofstream.open(data->time + "_threadN" + std::to_string(threadNumber) + ".log");
        
        separator = "";
        m_ofstream << "bulk: ";
        for (auto &str : data->bulk){
            m_ofstream << separator << str << std::endl;
            separator = ",";
        }

        m_ofstream.close();
    }
}