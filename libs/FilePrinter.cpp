#include "FilePrinter.h"

FilePrinter::FilePrinter(size_t size): Printer(size)
{
    for (size_t i = 0; i < m_qthreads; ++i)
        m_threads.push_back(std::thread ( &FilePrinter::printThread, this, i ));
}

void FilePrinter::printThread(size_t threadNumber){
    
    std::ofstream m_ofstream;
    shar_line_t<Bulk> data;
    std::string separator;

    while(m_queue.pop(data)){
        m_ofstream.open(data->time + "_threadN" + std::to_string(threadNumber) + ".log");
        printInfo( data, separator, m_ofstream);
        m_ofstream.close();
    }
}