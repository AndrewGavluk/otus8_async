#include <list>
#include <vector>
#include <memory>
#include <ctime>

#include "FilePrinter.h"
#include "ConsolePrinter.h"

class interpreter
{
    public:
        interpreter(size_t i);
        void push_back(std::shared_ptr<Printer> );
        void removeOutput(std::ostream&);
        void processStream();
        void insert(std::string strr);

    protected: 
        std::vector<std::string> m_block;
        
    private:  
        std::list< std::shared_ptr<Printer> > m_outputs; 
        std::istream iss;
        void print(std::time_t & ); 
        size_t m_bulkSize;
};
