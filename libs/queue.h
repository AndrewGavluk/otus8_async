#pragma once
#include <memory>
#include <vector>
#include <map>
#include <mutex>
#include <list>
#include <string>

#include "printer.h"

struct Bulk;

using shar_line_t = std::shared_ptr<Bulk>;

class queueLists
{
    public:
        queueLists() = default;
        void push(shar_line_t line);
        shar_line_t pop();
    private:
        std::list<shar_line_t> qList;
        mutable std::mutex m_mutex;  // TODO: check the nesessary of mutex
};

void queueLists::push(shar_line_t line )
{
    std::lock_guard<std::mutex> lock(m_mutex);
    qList.push_back(line);
}

shar_line_t queueLists::pop()
{
   std::lock_guard<std::mutex> lock(m_mutex);
   auto iter = qList.begin();
   qList.pop_front();
   return *iter;
}