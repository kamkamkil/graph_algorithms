#include <iostream>
#include <fstream>
#include <vector>

#include "graph.hpp"
#include "graphAlgorithms.hpp"

// std::vector<std::string> split(const std::string &s, char delim)
// {
//     std::vector<std::string> result;
//     std::stringstream ss(s);
//     std::string item;

//     while (std::getline(ss, item, delim))
//     {
//         result.push_back(item);
//     }

//     return result;
// }

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout << "prosze podac odpowiednia ilocc argumentow" << std::endl;
        return -1;
    }
    Graph<int, int> g;
    std::string s;
    std::ifstream file(argv[1]);
    int n = 0;
    int amount;
    std::vector<int> price;
    while (std::getline(file, s))
    {
        if (n == 0)
        {
            amount = std::stoi(s);
            for (int i = 0; i < amount; i++)
            {
                g.insertVertex(i + 1);
            }
        }
        else if (n <= amount)
        {
            price.push_back(std::stoi(s));
        }
        else if (n == amount + 1)
        {
        }
        else
        {
            auto nr = split(s, ' ');
            g.insertEdge(std::stoi(nr[0]) - 1, std::stoi(nr[1]) - 1, std::stoi(nr[2]) - 1);
            std::cout << std::stoi(nr[0]) - 1 << "  " << std::stoi(nr[1]) - 1 << "    " << std::stoi(nr[2]) -1 << std::endl;
        }
        n++;
    }
    file.close();
    double c_length = 5000;

  
    return 0;
}
