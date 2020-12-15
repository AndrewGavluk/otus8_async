#include "printer.h"

class FilePrinter : public  Printer
{
    public:
        FilePrinter(std::ofstream& fstr) : m_ofstream{fstr} {};
        void print(std::shared_ptr<Bulk> data) override;
    private:
        std::string m_filename;
        std::ofstream& m_ofstream;

};

void FilePrinter::print(std::shared_ptr<Bulk>  data){
    std::string separator;
    
    m_ofstream.open(data->time + ".log");
    m_ofstream << "bulk: ";
    for (auto &str : data->bulk){
        m_ofstream << separator << str << std::endl;
        separator = ",";
    }
    m_ofstream.close();

}