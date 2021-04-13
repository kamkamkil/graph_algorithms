#include <iostream>
#include "przemytnicylib.cpp"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout << "prosze podac odpowiednia ilosc argumentow" << std::endl;
        return -1;
    }
    std::cout << przemytnicy(przemytnicyLoadData(argv[1])) << std::endl;

    return 0;
}
