#include "lib_interpret.h" 
/*
interpreter::interpreter(int size) : m_bulkSize{static_cast<size_t>(size)}{}

void interpreter::appendConsole(std::ostream& out)
{
    m_outputs.push_back(std::make_shared<ConsolePrinter>(out));
}



void interpreter::processStream(std::istream& iss)
{
    size_t level{0};
    std::string input;
    
    
    std::time_t time=0;
    std::string stime;
    while(std::getline(iss, input)){
        if ( input=="{" && level++ ) continue;
        if ( input=="}" && --level ) continue; 
        
        if (!time)  time = std::time(nullptr);

        if (input=="}" || input=="{" || m_block.size() >= m_bulkSize)
        {   
            stime=std::to_string(time);
            for (auto outs : m_outputs)
                outs->print( m_block, stime );
            m_block.clear();
            time=0;
        }
        else
            m_block.push_back(input);
        
    }
}*/