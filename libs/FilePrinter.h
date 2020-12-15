#include "printer.h"

class FilePrinter : virtual public  Printer
{
    public:
        FilePrinter(std::ofstream& fstr) : m_ofstream{fstr} {};
        void print(std::vector<std::string>& bulk, std::string& time) override;
    private:
        std::string m_filename;
        std::ofstream& m_ofstream;

};

void FilePrinter::print(std::vector<std::string>& bulk, std::string& time){
    std::string separator;
    
    m_ofstream.open(time + ".log");
    m_ofstream << "bulk: ";
    for (auto &str : bulk){
        m_ofstream << separator << str << std::endl;
        separator = ",";
    }
    m_ofstream.close();

}