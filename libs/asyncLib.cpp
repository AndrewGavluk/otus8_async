#include"asyncLib.h"

async::async()  : m_counter{0}{}

uint64_t async::connect(){
   
    std::shared_ptr<interpreter> inter1 = std::make_shared<interpreter> (3);
    std::shared_ptr<Printer> Console = std::make_shared<ConsolePrinter>();
    std::shared_ptr<Printer> File1 = std::make_shared<FilePrinter>(2);
    
    inter1->push_back(Console);
    inter1->push_back(File1);
    m_inters.emplace(++m_counter, inter1);
    inter1->start();
    return m_counter;
}

void async::receive(uint64_t& num,  const char * data , size_t size){
    auto toInsert = m_inters.find(num);
    
    if (toInsert != m_inters.end()){
        toInsert->second->insert(std::make_shared<std::string> (data, size) );
    }
    else
        std::cerr << "Handle id you want recive in is not exist" << std::endl; 
}

void async::disconnect(uint64_t& num){
    auto toDel = m_inters.find(num);
    if (toDel != m_inters.end()){
        m_inters.erase(toDel);
    }
    else
        std::cerr << "Handle id you want del is not exist" << std::endl; 
    
}