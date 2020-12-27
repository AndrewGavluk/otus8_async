#include "lib_interpret.h"

interpreter::interpreter(size_t size) : m_bulkSize{size} {
 
}

interpreter::~interpreter()
{
    if (m_thread.joinable())
        m_thread.join();
}

void interpreter::push_back(std::shared_ptr<Printer> printer)
{
    m_outputs.push_back(printer);
}

void interpreter::print(std::time_t & time)
{
    std::string stime{std::to_string(time)};
    stime=std::to_string(time);
        for (auto outs : m_outputs){
            auto buf = std::make_shared<Bulk>(m_block, stime);
            outs->pushQueue(buf);
        }
        m_block.clear();
    time=0;
}

void interpreter::start()   {   
    m_thread = std::thread {&interpreter::processStream, this };    
}

void interpreter::insert(std::shared_ptr<std::string> strr)
{
    m_queue.push(strr);
}

void interpreter::processStream()
{
    size_t level{0};
    std::shared_ptr<std::string> sharinput;
    std::string input;
    std::time_t time=0;

    while(m_queue.pop(sharinput)){
        input = *sharinput.get();
        if ( input=="{" && level++ ) continue;
        if ( input=="}" && --level ) continue; 
        if (!time)  time = std::time(nullptr);

        if (input=="}" || input=="{")
            print(time);
        
        else{   // if string is not brackets print block, then push it to block, 
            m_block.push_back(input); 
            if(m_block.size() >= m_bulkSize && !level )
                print(time);  
        }  
    }
}