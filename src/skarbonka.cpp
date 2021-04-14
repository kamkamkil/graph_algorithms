#include <iostream>
#include <fstream>
#include "graph.hpp"

int main(int argc, char const *argv[])
{
    // if (argc != 2)
    // {
    //     std::cout << "prosze podac odpowiednia ilosc argumentow" << std::endl;
    //     return -1;
    // }

    Graph<int, int> g;
    std::string s;
    // std::ifstream file(argv[1]);
    std::ifstream file("data.txt");
    int n = 0;
    int amount;
    while (std::getline(file, s))
    {
        if (n == 0)
        {
            amount = std::stoi(s);
            for (unsigned int i = 0; i < (unsigned int)std::stoi(s); i++)
            {
                g.insertVertex(i);
            }
        }
        else
        {
            auto nr = split(s, ' ');
            if( n - 1 != std::stoi(nr[0]) - 1)
                g.insertEdge( n - 1,std::stoi(nr[0]) - 1);
        }
        n++;
    }
    file.close();
    g.exportToDot("../../temp.dot");
    
    return 0;
}
