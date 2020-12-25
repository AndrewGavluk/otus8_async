//#include "../libs/async.h" 
//#include "../libs/process.h"


int main(/*int argc, char** argv*/){

    /*if (argc < 2)
    {
        std::cerr << "Number of arguments < 2.\n";
        return 1;
    }
    interpreter inter1{std::atoi(argv[1])};*/
    //asy

    /*async interp{};

    uint64_t handler1{interp.connect()};
    uint64_t handler2{interp.connect()};

    (void)(handler1);
    (void)(handler2);
    
    const char *input1 = "cmd01\n cmd02\n cmd03\n cmd04\n {\n cmd11\n cmd12\n {\n cmd22\n }\n cmd31\n} cmd41\n cmd42\n"; 
    size_t size1 = 80;

    const char *input2 = "cmd01\n cmd02\n cmd03\n cmd04\n cmd05\n {\n cmd11\n cmd12\n cmd13\n{\n cmd22\n cmd23\n}\n cmd31\n} cmd41\n cmd42\n cmd43\n"; 
    size_t size2 = 106;

    interp.receive(handler1, input1, size1);
    interp.receive(handler2, input2, size2);
    
    interp.receive(handler1, input2, size2);
    interp.receive(handler2, input1, size1);*/

    return 0;
}
