
#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <thread>

#include "queue.h"

//using shar_line_t = std::shared_ptr<Bulk>;

class Printer
{
    public:
        Printer(size_t);
        virtual ~Printer();
        void pushQueue(std::shared_ptr<Bulk> data);
        void pushQueueEOF();
        virtual void printThread(size_t) = 0;

    protected:
        template <typename T> 
        inline void printInfo(shar_line_t<Bulk>& ,std::string& , T& m_ofstream );
        std::vector<std::thread> m_threads;   
        queueLists<Bulk> m_queue;  
        size_t m_qthreads;      
};

template <typename T> 
void Printer::printInfo(shar_line_t<Bulk>& data,std::string& separator, T& m_ofstream ){
        
        if (! data->bulk.size()) 
            return;

        separator = "";
        m_ofstream << "bulk: ";
        for (auto &str : data->bulk){
            m_ofstream << separator << str << std::endl;
            separator = ","; 
        }
} 
