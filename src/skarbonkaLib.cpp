#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "graph.hpp"
Graph<int, int> skarbonkaLoad(std::string filename)
{
    std::ifstream file(filename);
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

static void visit(Graph<int, int> &g, std::vector<bool> &visited, size_t start)
{
    visited[start] = true;
    auto nei = g.neighbours(start);
    if (!nei.empty())
        while (!visited[nei[0]])
        {
            visited[nei[0]] = true;
            nei = g.neighbours(nei[0]);
            if (nei.empty())
                break;
        }
}

int skarbonka(Graph<int, int> &g)
{
    int result = 0;
    std::vector<bool> visited(g.nrOfVertices(), false);
    for (size_t i = 0; i < g.nrOfVertices(); i++)
        if (g.predecessor(i).empty())
        {
            visit(g, visited, i);
            result++;
        }
    while (std::none_of(visited.begin(), visited.end(), [](bool b) { return b; }))
    {
        auto node = std::find(visited.begin(), visited.end(), false);
        visit(g, visited, node - visited.begin());
        result++;
    }
    return result;
}

int skarbonkaNaive(Graph<int, int> &g)
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
