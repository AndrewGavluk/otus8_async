#pragma once
#include <atomic>
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <string>

#include "printer.h"

struct Bulk;

template <typename T>
class queueLists
{
    public:
        queueLists() : m_EOF{true}{};
        void push(std::shared_ptr<T> line);
        bool pop(std::shared_ptr<T>& );
    private:
        std::deque<std::shared_ptr<T>> m_deque;
        std::mutex m_mutex; 
        std::condition_variable m_cv;
        std::atomic<bool> m_EOF; // TODO: add eof functionality ???
};

template <typename T>
void queueLists<T>::push(std::shared_ptr<T> line )
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_deque.push_back(line);
    m_cv.notify_one();
}

template <typename T>
bool queueLists<T>::pop(std::shared_ptr<T>& line)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while (m_deque.size() == 0)
			m_cv.wait(lock);
            
    if (m_deque.size())
    {
        line = std::make_shared<T>(std::move(*m_deque.front().get()));
        m_deque.pop_front();
        return true;
    }
    return false;
}