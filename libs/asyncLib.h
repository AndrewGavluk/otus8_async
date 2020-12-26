#include<cstdint>
#include <map>

#include "lib_interpret.h"

class async{
    public:
        async();
        uint64_t connect();
        void receive(uint64_t&,  const char *, size_t);
        void disconnect(uint64_t&);

    private:
        std::map<uint64_t, std::shared_ptr<interpreter> > m_inters;
        uint64_t m_counter;
};