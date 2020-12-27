#pragma once
#include <atomic>
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

struct Bulk
{
    Bulk (std::vector<std::string>& _bulk, std::string& _time) :  bulk{_bulk}, time{_time} {}
    std::vector<std::string> bulk;
    std::string time;
};

template <typename T>
using shar_line_t = std::shared_ptr<T>;

template <typename T>
class queueLists
{
    public:
        queueLists() : m_EOF{true}{};
        void push(shar_line_t<T> line);
        bool pop(shar_line_t<T>);
        void pushEOF();
    private:
        std::deque<shar_line_t<T>> m_deque;
        std::mutex m_mutex; 
        std::condition_variable m_cv;
        std::atomic<bool> m_EOF; 
};

template <typename T>
void queueLists<T>::push(shar_line_t<T> line )
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_deque.push_back(line);
    m_cv.notify_one();
}

template <typename T>
bool queueLists<T>::pop(shar_line_t<T> line)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while (m_deque.size() == 0 && m_EOF)
			m_cv.wait(lock);
    if (m_deque.size())
    {
        line = std::move(m_deque.front());
        m_deque.pop_front();
        return true;
    }
    return false;
}

template <typename T>
void queueLists<T>::pushEOF()
{
    m_EOF = false;
    m_cv.notify_all();
}
