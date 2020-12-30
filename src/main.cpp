#include <stdlib.h>     //for using the function sleep

#include "../libs/asyncLib.h"

int main(){
    assyncLib interp{};
    size_t size {3};
    uint64_t handler1{interp.connect(size)};
    uint64_t handler2{interp.connect(size)};
    
    const char *input1 = "cmd01 \ncmd02 \ncmd03 \ncmd04 \n{\ncmd11 \ncmd12 \n{\ncmd22 \n}\ncmd31 \n}\ncmd41 \ncmd42 \ncmd43 \n"; 
    size_t size1 = 86;
    const char *input2 = "cmd51 \ncmd52 \ncmd53 \ncmd54 \ncmd55 \n{\ncmd61 \ncmd62 \ncmd63 \n{\ncmd71 \ncmd72 \n}\ncmd81 \n}\ncmd91 \ncmd92 \ncmd93 \n"; 
    size_t size2 = 107;
    
    //size_t ping = 500;

    //std::this_thread::sleep_for (std::chrono::milliseconds(ping));
    interp.receive(handler1, input1, size1);
    //std::this_thread::sleep_for (std::chrono::milliseconds(ping));
    interp.receive(handler2, input2, size2);
    
    //std::this_thread::sleep_for (std::chrono::milliseconds(ping));
    interp.receive(handler1, input2, size2);
    //std::this_thread::sleep_for (std::chrono::milliseconds(ping));
    interp.receive(handler2, input1, size1);

    interp.disconnect(handler1);
    interp.disconnect(handler2);
    return 0;
}
