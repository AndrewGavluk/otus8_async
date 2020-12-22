
#pragma once
#include <string>
#include <thread>

#include "lib_interpret.h"
#include "queue.h"

struct Bulk
{
    Bulk (std::vector<std::string>& _bulk, std::string& _time) :  bulk{_bulk}, time{_time} {}
    std::vector<std::string> bulk;
    std::string time;
};


using shar_line_t = std::shared_ptr<Bulk>;

class Printer
{
    public:
        Printer(size_t numThreads) :  m_qthreads{numThreads} {
            };
        virtual ~Printer(){

        };
        virtual void print(std::shared_ptr<Bulk> data);
        virtual void printThread(size_t) = 0;

    protected:
        mutable std::mutex m_mutex;
        bool getBulk(shar_line_t&);
        std::vector<std::thread> m_threads;  
        size_t m_qthreads;
    
    private:    
        queueLists m_queue;
};

/*
TODO: add parent method
template <typename T>
void Printer::initWith( std::shared_ptr<std::vector<T>> ){
    size_t threadNumber{0};
    for (auto &i : m_threads)
        i = std::thread ( &Printer::printThread, this, ++threadNumber); 
}*/

bool Printer::getBulk(shar_line_t& Bulk){
    return m_queue.pop(Bulk);
}

void Printer::print(std::shared_ptr<Bulk> data)
{
    m_queue.push(data);
}
