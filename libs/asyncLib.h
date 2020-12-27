# pragma once
#include <cstdint>
#include <cstdio>
#include <map>
#include <memory>

#include "lib_interpret.h"


class assyncLib
{
    public:
        assyncLib();
        uint64_t conect(size_t&);
        void receive(uint64_t&,  const char *, size_t);
        void disconnect(uint64_t&);

    private:
        std::map<uint64_t, std::shared_ptr<interpreter> > m_inters;
        uint64_t m_counter;
};

assyncLib::assyncLib() : m_counter{0} {}

uint64_t assyncLib::conect(size_t& size)  {
    
    std::shared_ptr<interpreter> inter1 = std::make_shared<interpreter>(size);

    std::shared_ptr<Printer> Console = std::make_shared<ConsolePrinter>();
    std::shared_ptr<Printer> File1 = std::make_shared<FilePrinter>(2);

    inter1->push_back(Console);
    inter1->push_back(File1);
    
    inter1->processStream();
    m_inters.emplace(++m_counter, inter1);
    
    return m_counter;
}

void assyncLib::receive(uint64_t& id,  const char * buff, size_t size) {

    (void)(id);
    (void)(buff);
    (void)(size);

}

void assyncLib::disconnect(uint64_t& id) {
    (void)(id);

}
