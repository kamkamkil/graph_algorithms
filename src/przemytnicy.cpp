#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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
    std::ifstream file(argv[1]);
    // std::ifstream file("data_p.txt"); //! DEBUG
    int n = 0;
    int amount;
    while (std::getline(file, s))
    {
        if (n == 0)
        {
            amount = std::stoi(s);

        }
        else if (n <= amount)
        {
            // price.push_back(std::stoi(s));
            g.insertVertex(std::stoi(s));
        }
        else if (n == amount + 1)
        {
        }
        else
        {
            auto nr = split(s, ' ');
            g.insertEdge(std::stoi(nr[0]) - 1, std::stoi(nr[1]) - 1, std::stoi(nr[2]));
        }
        n++;
    }
    file.close();
    double c_length = 5000;

    g.exportToDot("../../d.dot", true,true);
    std::vector<std::vector<size_t>> cycles;
    for (auto &&i : g.neighbours(0))
    {
        cycles.push_back({0, i});
    }

    while (true)
    {
        std::vector<int> toDelate;
        auto stop = cycles.size();
        bool allVisited = true;
        for (size_t i = 0; i < stop; i++)
        {
            auto nei = g.neighbours(cycles[i].back());
            switch (nei.size())
            {
            case 0:
                if (cycles[i].back() != 0)
                    toDelate.push_back(i);
                break;

            case 1:
                if (nei[0] != 0)
                {
                    allVisited = false;
                    cycles[i].push_back(nei[0]);
                }
                break;
            default:
                bool test = false;
                for (auto &&n : nei)
                {
                    if (n != 0)
                    {
                        auto copy = cycles[i];
                        copy.push_back(n);
                        cycles.push_back(copy);
                        test = true;
                    }
                }
                if (test)
                {
                    allVisited = false;
                    toDelate.push_back(i);
                }
                break;
            }
        }
        if (allVisited)
            break;
        for (auto it = toDelate.rbegin(); it != toDelate.rend(); it++)
            cycles.erase(cycles.begin() + *it);
    }
    std::vector<size_t> price(cycles.size(),0);
    for (size_t i = 0; i < cycles.size(); i++)
    {
        for (size_t k = 0; k < cycles[i].size() - 1; k++)
        {
            price[i] += g.edgeLabel(cycles[i][k],cycles[i][k+1]);
        }
        price[i] += g.edgeLabel(cycles[i].back(),0);
        price[i] += (g.vertexData((*std::min_element(cycles[i].begin(),cycles[i].end(),[&](size_t a,size_t b) -> bool {return g.vertexData(a) < g.vertexData(b); })))) / 2;
    }
    price.push_back(g.vertexData(0) / 2);
    std::cout << *std::min_element(price.begin(),price.end()) << std::endl;
    
    return 0;
}
