
#include "TestPrinter.h"

TestPrinter::TestPrinter(size_t size, std::string fname) :Printer{size}, m_fname{fname} {
    m_ofstream.open(m_fname, std::ofstream::trunc);
    m_ofstream.close();
    for (size_t i = 0; i < m_qthreads; ++i)
        m_threads.push_back(std::thread ( &TestPrinter::printThread, this, i ));
}

TestPrinter::~TestPrinter(){
    for (auto &i : m_threads)
        if (i.joinable())
                i.join();
}

void TestPrinter::printThread(size_t threadNumber)
{
    std::shared_ptr<Bulk> data;
    std::string separator;
    size_t counter{0};
    while(m_queue.pop(data)){
        m_ofstream.open(m_fname, std::ofstream::out | std::ofstream::app);
        separator = "";
        m_ofstream << "bulk: ";
        for (auto &str : data->bulk){
            m_ofstream << separator << str << std::endl;
            separator = ",";
        }
        m_ofstream.close();
    }

}