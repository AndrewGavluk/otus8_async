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

using shar_line_t = std::shared_ptr<Bulk>;

class queueLists
{
    public:
        queueLists() : m_EOF{true}{};
        void push(shar_line_t& line);
        bool pop(shar_line_t&);
        void pushEOF();
    private:
        std::deque<shar_line_t> m_deque;
        std::mutex m_mutex; 
        std::condition_variable m_cv;
        std::atomic<bool> m_EOF; 
};
