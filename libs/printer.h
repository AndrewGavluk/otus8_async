
#pragma once
#include <functional>
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
        Printer(size_t);
        virtual ~Printer();
        void pushQueue(std::shared_ptr<Bulk> data);
        virtual void printThread(size_t) = 0;

    protected:
        template <typename T> 
        inline void printInfo(shar_line_t& ,std::string& , T& m_ofstream );
        std::vector<std::thread> m_threads;   
        queueLists m_queue;  
        size_t m_qthreads; 
        
};

Printer::Printer(size_t size ): m_qthreads{size}{ };

template <typename T> 
void Printer::printInfo(shar_line_t& data,std::string& separator, T& m_ofstream ){
        
        if (! data->bulk.size()) 
            return;
        separator = "";
        m_ofstream << "bulk: ";
        for (auto &str : data->bulk){
            m_ofstream << separator << str << std::endl;
            separator = ",";
        }
}

Printer::~Printer(){
    for (auto &i : m_threads)
        if (i.joinable())
                i.join();
}

void Printer::pushQueue(std::shared_ptr<Bulk> data)
{   m_queue.push(data); }
