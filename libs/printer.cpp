#include "printer.h"

Printer::Printer(size_t size ): m_qthreads{size}{ };

Printer::~Printer(){
    for (auto &i : m_threads)
        if (i.joinable())
            i.join();
}

void Printer::pushQueue(std::shared_ptr<Bulk> data){   
    m_queue.push(data); 
}

void Printer::pushQueueEOF(){
    m_queue.pushEOF();
}
