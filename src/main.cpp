#include "../libs/lib_interpret.h" 
#include "../libs/ConsolePrinter.h" 
#include "../libs/FilePrinter.h" 


int main(/*int argc, char** argv*/){

    /*if (argc < 2)
    {
        std::cerr << "Number of arguments < 2.\n";
        return 1;
    }
    interpreter inter1{std::atoi(argv[1])};*/
    interpreter inter1{3};

    std::shared_ptr<Printer> Console = std::make_shared<ConsolePrinter>(1);
    
    std::ofstream FileStream1;
    std::shared_ptr<Printer> File1 = std::make_shared<FilePrinter>(2);

    inter1.push_back(Console);
    inter1.push_back(File1);
    inter1.processStream(std::cin);

    return 0;
}
