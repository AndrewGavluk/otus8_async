#include "../libs/printer.h"

#include <fstream>

class TestPrinter : public Printer
{
    public:
        TestPrinter(size_t size, std::string fname); 
        ~TestPrinter();
        void printThread(size_t threadNumber) override;
    private:
    std::string m_fname;
    std::ofstream m_ofstream;
       
};