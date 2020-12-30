#include "lib_interpret.h" 

interpreter::interpreter(size_t size) : m_bulkSize{size}  {}

interpreter::~interpreter(){
    if (m_thread.joinable())
        m_thread.join();
}

void interpreter::addPrinter(std::shared_ptr<Printer> printer)
{
    m_outputs.push_back(printer);
}

void interpreter::StartTread()
{
    m_thread = std::thread (&interpreter::processStream, std::ref(*this));
}

void interpreter::print(std::time_t & time)
{
    std::string stime{std::to_string(time)}; 
    auto bulkPrinter = [this, &stime](std::shared_ptr<Printer> outs){
         outs->print(std::make_shared<Bulk>(m_block, stime));};
    
    std::for_each(m_outputs.begin(), m_outputs.end(), bulkPrinter);
    m_block.clear();
    time=0;
}

void interpreter::processStream()
{
    size_t level{0};
    std::string input;
    std::time_t time=0;

    while(!m_sstrm.eof() && std::getline(m_sstrm, input)){
        if ( input=="{" && level++ ) continue;
        if ( input=="}" && --level ) continue;
        if (!time)  time = std::time(nullptr);

        if (input=="}" || input=="{")
            print(time);
        
        else{// if string is not brackets print block, then push it to block, 
            m_block.push_back(input); 
            if(m_block.size() >= m_bulkSize && !level )
                print(time);
        }  
    }
    for (auto& outs : m_outputs){
            outs->setEOF();
        }
}

void interpreter::putString(std::string buf)
{
    m_sstrm << buf;
}
