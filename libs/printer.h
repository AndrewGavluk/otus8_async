
#pragma once
#include <functional>
#include <thread>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>

#include "queue.h"

struct Bulk
{
    Bulk () = default;

    Bulk (std::vector<std::string>& _bulk, std::string& _time) :  bulk{_bulk}, time{_time} {}
    
    Bulk(const Bulk& Copy) : time {Copy.time}
    {
        bulk.reserve(Copy.bulk.size());
        std::copy(Copy.bulk.begin(), Copy.bulk.end(), back_inserter(bulk));
    }

    Bulk (Bulk && other){
        std::swap(bulk, other.bulk);
        std::swap(time, other.time);
    }

    Bulk& operator =(const Bulk& Copy)
    {
        time = Copy.time;
        bulk.reserve(Copy.bulk.size());
        std::copy(Copy.bulk.begin(), Copy.bulk.end(), back_inserter(bulk));

        return *this;
    }


    std::vector<std::string> bulk;
    std::string time;
};

class Printer
{
    public:
        Printer(size_t);
        virtual ~Printer();
        void print(Bulk data);
        virtual void printThread(size_t) = 0;
        void setEOF();

    protected:
        std::vector<std::thread> m_threads;   
        queueLists<Bulk> m_queue;  
        size_t m_qthreads;  
};
