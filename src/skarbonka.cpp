#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "graph.hpp"

int main(int argc, char const *argv[])
{
    // if (argc != 2)
    // {
    //     std::cout << "prosze podac odpowiednia ilosc argumentow" << std::endl;
    //     return -1;
    // }

    // std::ifstream file(argv[1]);
    // g = skarbonkaLoad(argv[1]);
    std::string s = "data.txt";
    auto g = skarbonkaLoad(s);
    std::cout << skarbonka(g) << std::endl;
    // std::cout << skarbonkaNaive(skarbonkaLoad(argv[1])) << std::endl;
    return 0;
}
