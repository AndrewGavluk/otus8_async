#include "printer.h"

class FilePrinter : public  Printer
{
    public:
        FilePrinter(size_t size);
        ~FilePrinter();
        void print(std::shared_ptr<Bulk> data) override;
        void printThread(size_t threadNumber) override;
};

FilePrinter::FilePrinter(size_t size): Printer(size)
{
    size_t threadNumber{0};
    for (size_t i = 0; i < m_qthreads; ++i)
    {
        size_t buf{++threadNumber};
        std::thread iThread ( &FilePrinter::printThread, this, std::ref(buf)); 
        m_threads.push_back(std::move(iThread));
    }
}


FilePrinter::~FilePrinter()
{
    for (auto &i : m_threads)
        if (i.joinable())
                i.join();
}


void FilePrinter::print(std::shared_ptr<Bulk> data) {
    Printer::print(data);
}

void FilePrinter::printThread(size_t threadNumber){
    
    (void)(threadNumber);
    std::ofstream m_ofstream;
    shar_line_t data;
    std::string separator;

    while(getBulk(data)){
        m_ofstream.open(data->time + ".log");
        m_ofstream << "bulk: ";
        separator = "";
        std::cout << "bulk: ";
        for (auto &str : data->bulk){
            m_ofstream << separator << str << std::endl;
            separator = ",";
        }
        m_ofstream.close();
    }
}