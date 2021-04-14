#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "graph.hpp"

Graph<int, int> skarbonkaLoad(std::string filename)
{
    std::ifstream file("data.txt");
    Graph<int, int> g;
    std::string s;
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
            if (n - 1 != std::stoi(nr[0]) - 1)
                g.insertEdge(n - 1, std::stoi(nr[0]) - 1);
        }
        n++;
    }
    file.close();
    return g;
}

int skarbonkaNaive(Graph<int, int> g)
{
    int result = 0;
    std::vector<bool> visited(g.nrOfVertices(), false);
    for (size_t i = 0; i < g.nrOfVertices(); i++)
    {
        if (g.predecessor(i).empty())
        {
            for (auto it = g.beginDFS(i); it != g.endDFS(); it++)
                visited[it.id()] = true;
            result++;
        }
    }
    while (std::none_of(visited.begin(), visited.end(), [](bool b) { return b; }))
    {
        auto node = std::find(visited.begin(), visited.end(), false);
        for (auto it = g.beginDFS(node - visited.begin()); it != g.endDFS(); it++)
            visited[it.id()] = true;
        result++;
    }
    return result;
}

int main(int argc, char const *argv[])
{
    // if (argc != 2)
    // {
    //     std::cout << "prosze podac odpowiednia ilosc argumentow" << std::endl;
    //     return -1;
    // }

    // std::ifstream file(argv[1]);
    // g = skarbonkaLoad(argv[1]);
    std::cout << skarbonkaNaive(skarbonkaLoad("data.txt")) << std::endl;
    return 0;
}
