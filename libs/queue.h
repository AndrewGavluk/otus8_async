#pragma once
#include <atomic>
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <string>

#include "printer.h"

struct Bulk;

using shar_line_t = std::shared_ptr<Bulk>;

class queueLists
{
    public:
        queueLists() : m_EOF{true}{};
        void push(shar_line_t& line);
        bool pop(shar_line_t&);
    private:
        std::deque<shar_line_t> m_deque;
        std::mutex m_mutex; 
        std::condition_variable m_cv;
        std::atomic<bool> m_EOF; // TODO: add eof functionality ???
};

void queueLists::push(shar_line_t& line )
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_deque.push_back(line);
    m_cv.notify_one();
}

bool queueLists::pop(shar_line_t& line)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while (m_deque.size() == 0)
			m_cv.wait(lock);
    if (m_deque.size())
    {
        line = std::move(m_deque.front());
        m_deque.pop_front();
        return true;
    }
    return false;
}