#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include "graph.hpp"

/**
 * @brief ładuje dane do grafu zgodnie z daniem "przemytnicy"
 * 
 * @param fileName nazwa pliku z jakiego ładujemy dane
 * @return Graph<int, int> 
 */
Graph<int, int> przemytnicyLoadData(std::string fileName)
{
    Graph<int, int> g;
    std::string s;
    std::ifstream file(fileName);
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
    return g;
}

/**
 * @brief wykonuje zadanie "przemytnicy"
 * 
 * UWAGA nie wspiera grafów z pętlami nie będącymy częscią 0
 * 
 * @param g graf zdefiniowany zgodnie z treścią zadania
 * @return std::pair<int,std::vector<size_t>> {int najtańsza możliwa opcja, cykl}
 */
std::pair<int, std::vector<size_t>> przemytnicyLazy(Graph<int, int> g)
{
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
    // poniższa linijka upewnia nas że na pewno wszystkie cykle są poprawne inaczej nie przechodzi testu TEST_CASE("many_dead_ends")
    cycles.erase(
        std::remove_if(cycles.begin(), cycles.end(), [&](std::vector<size_t> v) {
            auto t = g.neighbours(v.back());
            return std::find(t.begin(), t.end(), 0) == t.end();
        }),
        cycles.end());
    std::vector<size_t> price(cycles.size(), 0);
    for (size_t i = 0; i < cycles.size(); i++)
    {
        for (size_t k = 0; k < cycles[i].size() - 1; k++)
        {
            price[i] += g.edgeLabel(cycles[i][k], cycles[i][k + 1]);
        }
        price[i] += g.edgeLabel(cycles[i].back(), 0);
        price[i] += (g.vertexData((*std::min_element(cycles[i].begin(), cycles[i].end(), [&](size_t a, size_t b) -> bool { return g.vertexData(a) < g.vertexData(b); })))) / 2;
    }
    price.push_back(g.vertexData(0) / 2);
    auto result = std::min_element(price.begin(), price.end());
    return {*result, *result != price.back() ? cycles[result - price.begin()] : std::vector<size_t>{}};
}

/**
 * @brief wykonuje zadanie "przemytnicy"
 * 
 * @param g graf zdefiniowany zgodnie z treścią zadania
 * @return std::pair<int,std::vector<size_t>> {int najtańsza możliwa opcja, cykl}
 */
std::pair<int, std::vector<size_t>> przemytnicy(Graph<int, int> g)
{
    class Path
    {
    private:
        Graph<int, int> *g;

    public:
        Path(Graph<int, int> *g_) : g(g_), path(1, 0), length(0), cheapest(5000) {}
        Path(Graph<int, int> *g_, size_t first) : g(g_), path(1, 0), length(0), cheapest(5000) { push_back(first); }
        ~Path() = default;
        std::vector<size_t> path;
        bool full = false;
        unsigned int length;
        unsigned int cheapest;
        void push_back(size_t item)
        {
            path.push_back(item);
            if ((g->vertexData(item) / 2) < cheapest)
                cheapest = g->vertexData(item) / 2;
            if (path.size() > 1)
                length += g->edgeLabel(path[path.size() - 2], path[path.size() - 1]);
        }
        size_t back() { return path.back(); }
        unsigned int allCost() { return length + cheapest; }
        std::vector<size_t> neighbours() { return g->neighbours(back()); }
        bool checkFull() { return full || back() == 0; }
    };
    std::vector<Path> cycles;
    for (auto &&i : g.neighbours(0))
        cycles.push_back(Path(&g, i));
    // if (cycles.empty())
    //     return; // !dodać wyjście
    bool everyPath = false;
    auto current = 0;
    while (true)
    {
        auto nei = cycles[current].neighbours();
        std::vector<size_t> toDelate;
        if (cycles[current].back() == 0) // jeżeli jedyny sąsiad to początek to pętla jest już skończona
            cycles[current].full = true;
        else
            switch (nei.size())
            {
            case 0:
                // tutaj nie ma sąsiadów więc na pewno nie jest częścią pętli
                toDelate.push_back(current);
                break;

            case 1:
                cycles[current].push_back(nei[0]);
                break;
            default:
                for (auto n : nei)
                {
                    cycles.push_back(Path(cycles[current]));
                    cycles.back().push_back(n);
                }
                toDelate.push_back(current);
                break;
            }
        for (auto it = toDelate.rbegin(); it != toDelate.rend(); it++)
            cycles.erase(cycles.begin() + *it);
        bool test = true;
        int next = current;
        for (size_t i = 0; i < cycles.size(); i++)
        {
            if (!cycles[i].full && cycles[i].allCost() < cycles[next].length)
            {
                next = i;
                test = false;
            }
        }
        if (next == current && cycles[current].checkFull())
            return {cycles[current].allCost(), cycles[current].path};
        else if (std::all_of(cycles.begin(),cycles.end(),[](Path &p) {return p.checkFull();}))
        {
            auto result = std::min_element(cycles.begin(), cycles.end(), [](Path p1, Path p2) { return p1.allCost() < p2.allCost(); });
            return {(*result).allCost(), (*result).path};
        }
        current = next;
    }
}