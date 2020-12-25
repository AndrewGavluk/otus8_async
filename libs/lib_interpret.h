#include <list>
#include <vector>
#include <memory>
#include <ctime>

#include "FilePrinter.h"
#include "ConsolePrinter.h"

class interpreter
{
    public:
        interpreter(int i);
        void push_back(std::shared_ptr<Printer> );
        void removeOutput(std::ostream&);
        void processStream(std::istream&);

    protected: 
        std::vector<std::string> m_block;
        
    private:   
        void print(std::time_t & );
        std::list< std::shared_ptr<Printer> > m_outputs;
        size_t m_bulkSize;
};
