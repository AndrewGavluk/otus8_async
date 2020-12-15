#include <memory>
#include <vector>
#include <map>
#include <list>
#include <string>

using line_t = std::vector<std::string>;
using shar_line_t = std::shared_ptr<line_t>;

class queueLists
{
    public:
        queueLists() = default;
        void push(shar_line_t& line);
        shar_line_t pop();
    
    private:
        std::list<shar_line_t> qList;

};

void queueLists::push(shar_line_t& line )
{
    qList.push_back(line);
}

shar_line_t queueLists::pop()
{
   auto iter = qList.begin();
   qList.pop_front();
   return *iter;
}