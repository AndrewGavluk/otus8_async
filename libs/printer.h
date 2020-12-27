
#pragma once
#include <functional>
#include <thread>
#include <string>
#include <vector>
#include <iostream>

#include "queue.h"

struct Bulk
{
    Bulk (std::vector<std::string>& _bulk, std::string& _time) :  bulk{_bulk}, time{_time} {}
    Bulk (Bulk && other){
        std::swap(bulk, other.bulk);
        std::swap(time, other.time);
    }
    std::vector<std::string> bulk;
    std::string time;
};

class Printer
{
    public:
    Printer(size_t);
    virtual ~Printer();
    void print(std::shared_ptr<Bulk> data);
    virtual void printThread(size_t) = 0;

    protected:
        std::vector<std::thread> m_threads;   
        queueLists<Bulk> m_queue;  
        size_t m_qthreads; 
        
};

Printer::Printer(size_t size ): m_qthreads{size} {   
    /*size_t threadNumber{0};
    for (size_t i = 0; i < m_qthreads; ++i)
    {
        size_t buf{++threadNumber};
        m_threads.push_back(std::thread (pThread, this, std::ref(buf)));
    }*/
};


Printer::~Printer(){
    for (auto &i : m_threads)
        if (i.joinable())
                i.join();
}

void Printer::print(std::shared_ptr<Bulk> data)
{
    m_queue.push(data);
}

void Printer::printThread(size_t a1)
{
    (void)(a1);
} 