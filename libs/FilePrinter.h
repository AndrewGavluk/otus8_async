#include "printer.h"

class FilePrinter : public  Printer
{
    public:
        FilePrinter(size_t size);
        void print(std::shared_ptr<Bulk> data) override;
        void printThread(size_t threadNumber) override;

};

FilePrinter::FilePrinter(size_t size): Printer(size)
{
    std::shared_ptr<std::vector<std::ofstream> > streams;
    streams->reserve(static_cast<int>(size));
    for (size_t i = 0; i<size; ++i){
        std::ofstream out1;
        streams->push_back(std::move(out1));
    }
    Printer::initWith(streams);
}

void FilePrinter::print(std::shared_ptr<Bulk> data) {
    Printer::print(data);
}

void FilePrinter::printThread(size_t threadNumber){
    
    (void)(threadNumber);
    // TODO : 1. eof check: while not eof read bulk
    // TODO : 2. add thread id
    std::ofstream m_ofstream;
    // TODO m_ofstream from vector threadNumber

    auto data = getBulk();
    std::string separator;
    m_ofstream.open(data->time + ".log");
    m_ofstream << "bulk: ";
    for (auto &str : data->bulk){
        m_ofstream << separator << str << std::endl;
        separator = ",";
    }
    m_ofstream.close();

}