
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

class Printer
{
    public:
        Printer(size_t numThreads) : m_threads{numThreads} {};
        virtual ~Printer(){
             for (auto &i : m_threads)
                i.join();
        };
        virtual void print(std::shared_ptr<Bulk> data);
        virtual void printThread(size_t&) = 0;
    protected:
        shar_line_t getBulk();
        
        template <typename T>
        void initWith( std::shared_ptr<std::vector< T>>  );
    private:
        queueLists m_queue;
        std::vector<std::thread> m_threads;
    
};

template <typename T>
void Printer::initWith( std::shared_ptr<std::vector< T>>  ){
    size_t threadNumber{0};
    for (auto &i : m_threads)
        i = std::thread ( &Printer::printThread, this, ++threadNumber); 
}

shar_line_t Printer::getBulk(){
    return m_queue.pop();
}

void Printer::print(std::shared_ptr<Bulk> data)
{
    m_queue.push(data);
}
