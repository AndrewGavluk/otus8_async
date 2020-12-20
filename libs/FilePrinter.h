#include "printer.h"

class FilePrinter : public  Printer
{
    public:
        FilePrinter(size_t size);
        void print(std::shared_ptr<Bulk> data) override;
        void printThread(size_t threadNumber) override;

        template <typename T>
        void initWith( std::shared_ptr<std::vector< T>>  ); 


};

FilePrinter::FilePrinter(size_t size): Printer(size)
{
    std::shared_ptr<std::vector<std::ofstream> > streams;
    streams->reserve(static_cast<int>(size));
    for (size_t i = 0; i<size; ++i){
        std::ofstream out1;
        streams->push_back(std::move(out1));
    }
    initWith(streams);
}

template <typename T>
void FilePrinter::initWith( std::shared_ptr<std::vector< T>>  )
{
    size_t threadNumber{0};
    for (size_t i = 0; i < m_qthreads; ++i)
    {
        size_t buf{++threadNumber};
        std::thread iThread ( &FilePrinter::printThread, this, std::ref(buf)); 
        m_threads.push_back(std::move(iThread));
    }

    for (auto &i : m_threads)
        if (i.joinable())
                i.join();
         
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
    // TODO : check te result and process bulks while not eof
    shar_line_t data;
    bool result = getBulk(data);
    (void)(result);

    std::string separator;
    m_ofstream.open(data->time + ".log");
    m_ofstream << "bulk: ";
    for (auto &str : data->bulk){
        m_ofstream << separator << str << std::endl;
        separator = ",";
    }
    m_ofstream.close();

}