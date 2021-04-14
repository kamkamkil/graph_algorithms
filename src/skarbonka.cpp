#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "skarbonkaLib.cpp"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout << "prosze podac odpowiednia ilosc argumentow" << std::endl;
        return -1;
    }

    std::ifstream file(argv[1]);
    auto g = skarbonkaLoad(argv[1]);
    std::cout << skarbonka(g) << std::endl;
    return 0;
}
