#include "printer.h"

Printer::Printer(size_t size ): m_qthreads{size}{  };

Printer::~Printer(){
    for (auto &i : m_threads)
        if (i.joinable())
                i.join();
}

void Printer::setEOF() { 
    m_queue.setEOF(); 
}

void Printer::print(std::shared_ptr<Bulk> data){
    m_queue.push(data);
}

void Printer::printThread(size_t a1){
    (void)(a1);
} 