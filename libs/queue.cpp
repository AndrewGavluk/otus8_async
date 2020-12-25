#include "queue.h"

void queueLists::push(shar_line_t& line )
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_deque.push_back(line);
    m_cv.notify_one();
}

bool queueLists::pop(shar_line_t& line)
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

void queueLists::pushEOF()
{
    m_EOF = false;
    m_cv.notify_all();
}