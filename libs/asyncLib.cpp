#include "asyncLib.h"

assyncLib::assyncLib() : m_counter{0} {}

uint64_t assyncLib::connect(size_t& size)  {
    
    std::shared_ptr<interpreter> inter1 = std::make_shared<interpreter>(size);

    std::shared_ptr<Printer> Console = std::make_shared<ConsolePrinter>();
    std::shared_ptr<Printer> File1 = std::make_shared<FilePrinter>(2);

    inter1->push_back(Console);
    inter1->push_back(File1);
    inter1->StartTread();
    m_inters.emplace(++m_counter, inter1);
    
    return m_counter;
}

void assyncLib::receive(uint64_t& id,  const char * buff, size_t size) {
    auto toInsert = m_inters.find(id);
    if (toInsert != m_inters.end())
        toInsert->second->putString(std::string(buff, size));
}

void assyncLib::disconnect(uint64_t& id) {
    auto toDel = m_inters.find(id);
    if (toDel != m_inters.end()){
        m_inters.erase(toDel); 
    }
}
