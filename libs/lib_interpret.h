#include <list>
#include <vector>
#include <memory>
#include <ctime>

#include "FilePrinter.h"
#include "ConsolePrinter.h"

class interpreter
{
    public:
        interpreter(size_t size);
        ~interpreter();
        void push_back(std::shared_ptr<Printer> );
        void processStream();
        void insert(std::shared_ptr<std::string> strr);
        void start();
    
    protected: 
        std::vector<std::string> m_block;
        
    private:  
        std::list< std::shared_ptr<Printer> > m_outputs; 
        void print(std::time_t & ); 
        queueLists<std::string> m_queue;
        size_t m_bulkSize;
        std::thread m_thread;   
};
