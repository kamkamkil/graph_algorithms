#pragma once
#include <algorithm>
#include <set>
#include <stack>
#include "../src/graph.hpp"

/**
 * @brief używa funkcji na każdym z elementów w kolejności DFS zaczynając od wieszchołka vertex 
 * 
 * @param graph graf na na którym będzie wykonywana ta funkcja 
 * @param vertex wierzchołek startowy 
 * @param fun 
 */
template <typename V, typename E>
void DFS(const Graph<V, E> graph, size_t vertex, std::function<void(const V &)> fun)
{
    if (graph.neighbours(vertex).empty())
    {
        fun(graph.vertexData(vertex));
        return;
    }
    std::vector<bool> visited(graph.nrOfVertices());
    for (size_t i = 0; i < graph.nrOfVertices(); i++)
        visited[i] = false;
    visited[vertex] = true;
    std::stack<size_t> stack;
    stack.push(vertex);
    fun(graph.vertexData(vertex));
    size_t current = graph.neighbours(vertex).back();
    auto test = [&](size_t vertex_) -> bool {
        for (auto &&n : graph.neighbours(vertex_))
        {
            if (!visited[n])
                return true;
        }
        return false;
    };
    while (current != vertex || test(vertex)) //TODO ten kod bardzo mocno poczebuje refraktoringu
    {
        stack.push(current);
        if (!visited[current])
        {
            fun(graph.vertexData(current));
            visited[current] = true;
        }
        bool finish = true;
        for (auto &&value : visited)
        {
            if (!value)
            {
                finish = false;
                break;
            }
        }
        if (finish)
            return;
        if (test(current))
        {
            for (auto &&ver : graph.neighbours(current))
                if (!visited[ver])
                {
                    current = ver;
                    break;
                }
        }
        else
        {
            while (!stack.empty() && !test(current))
            {
                current = stack.top();
                stack.pop();
            }
        }
    };
}

/**
 * @brief używa funkcji na każdym z elementów w kolejności BFS zaczynając od wieszchołka vertex 
 * 
 * @param graph graf na na którym będzie wykonywana ta funkcja 
 * @param vertex wierzchołek startowy 
 * @param fun 
 */
template <typename V, typename E>
void BFS(const Graph<V, E> graph, size_t vertex, std::function<void(const V &)> fun) //const
{
    if (graph.neighbours(vertex).empty())
    {
        fun(graph.vertexData(vertex));
        return;
    }
    std::vector<bool> visited(graph.nrOfVertices());
    for (size_t i = 0; i < graph.nrOfVertices(); i++)
        visited[i] = false;
    visited[vertex] = true;
    std::queue<size_t> queue;
    size_t current;
    queue.push(vertex);
    while (!queue.empty())
    {
        current = queue.front();
        queue.pop();
        visited[current] = true;
        fun(graph.vertexData(current));
        if (!graph.neighbours(current).empty())
        {
            for (auto &&node : graph.neighbours(current))
            {
                if (!visited[node])
                {
                    queue.push(node);
                    visited[node] = true;
                }
            }
        }
    }
}

/**
 * @brief zwraca kiolejność przeszuiwania BFS
 *  
 * @param graph graf na jaki pracujemy 
 * @param vertex wierzchołek startowy
 * @return std::vector<size_t> kolejność przeszukiwania 
 */
template <typename V, typename E>
std::vector<size_t> BFS(const Graph<V, E> graph, size_t vertex) //const
{
    std::vector<size_t> result;
    if (graph.neighbours(vertex).empty())
    {
        result.push_back(vertex);
        return result;
    }
    std::vector<bool> visited(graph.nrOfVertices());
    for (size_t i = 0; i < graph.nrOfVertices(); i++)
        visited[i] = false;
    visited[vertex] = true;
    std::queue<size_t> queue;
    size_t current;
    queue.push(vertex);
    while (!queue.empty())
    {
        current = queue.front();
        queue.pop();
        visited[current] = true;
        result.push_back(current);
        if (!graph.neighbours(current).empty())
        {
            for (auto &&node : graph.neighbours(current))
            {
                if (!visited[node])
                {
                    queue.push(node);
                    visited[node] = true;
                }
            }
        }
    }
    return result;
}

/**
 * @brief zwraca najkrótszą trasę obliczaną algorytmem Dijkstry oraz jej długość 
 * 
 * @param graph graf na jakim pracujemy 
 * @param start_idx wierzchołek startowy
 * @param end_idx wierzchołek końcowy
 * @param getEdgeLength sposób obliczania długości krawędzi (domyślnie jest to po prostu krawędź)
 * @return std::pair<double, std::vector<std::size_t>> (długość trasy, ścieżka)
 */
template <typename V, typename E>
std::pair<double, std::vector<std::size_t>> dijkstra(
    Graph<V, E> &graph, std::size_t start_idx, std::size_t end_idx, std::function<double(const E &)> getEdgeLength = [](const E &edge) -> E { return edge; })
{
    std::set<std::pair<double, size_t>> unvisited;
    for (size_t i = 0; i < graph.nrOfVertices(); i++)
        if (i != start_idx)
            unvisited.insert({std::numeric_limits<double>::max(), i});
        else
            unvisited.insert({0, i});
    std::vector<size_t> predecesor(graph.nrOfVertices());

    auto current_node = unvisited.find({0, start_idx});
    while ((*current_node).second != end_idx)
    {
        auto neighbours = graph.neighbours((*current_node).second);
        auto it = std::remove_if(neighbours.begin(), neighbours.end(), [&](size_t n) -> bool { return std::none_of(unvisited.begin(), unvisited.end(), [&](const std::pair<double, size_t> a) -> bool { return a.second == n; }); });
        neighbours.erase(it, neighbours.end());
        for (auto &&neighbour : neighbours)
        {
            auto temp = std::find_if(unvisited.begin(), unvisited.end(), [&](const std::pair<double, size_t> a) -> bool { return a.second == neighbour; }); //TODO zmiana nazwy
            if (getEdgeLength(graph.edgeLabel((*current_node).second, neighbour)) + (*current_node).first < (*temp).first)
            {
                unvisited.erase(temp);
                unvisited.insert({graph.edgeLabel((*current_node).second, neighbour) + (*current_node).first, neighbour});
                predecesor[neighbour] = (*current_node).second;
            }
        }
        unvisited.erase(current_node);
        if (unvisited.empty())
            throw "no path exeption";
        current_node = std::min_element(unvisited.begin(), unvisited.end());
    }
    size_t node = end_idx;
    std::vector<size_t> result;
    while (node != start_idx)
    {
        result.push_back(node);
        node = predecesor[node];
    }
    double result_distance = 0;
    result.push_back(start_idx);
    std::reverse(result.begin(), result.end());
    for (size_t i = 1; i < result.size(); i++)
    {
        result_distance += getEdgeLength(graph.edgeLabel(result[i - 1], result[i]));
    }
    return {result_distance, result};
}
/**
 * @brief zwraca najkrótszą trasę obliczaną algorytmem A* oraz jej długość 
 * 
 * @param graph graf na jakim pracujemy 
 * @param start_idx wierzchołek startowy
 * @param end_idx wierzchołek końcowy
 * @param heuristics heurystyka służąca do przybliżenia odległości w tym algorytmie 
 * @param getEdgeLength sposób obliczania długości krawędzi (domyślnie jest to po prostu krawędź)
 * @return std::pair<double, std::vector<std::size_t>> (długość trasy, ścieżka)
 */
template <typename V, typename E>
std::pair<double, std::vector<std::size_t>> astar(
    Graph<V, E> &graph, std::size_t start_idx, std::size_t end_idx, std::function<double(const Graph<V, E> &, std::size_t actual_vertex_id, std::size_t end_vertex_id)> heuristics, std::function<double(const E &)> getEdgeLength = [](const E &edge) -> E { return edge; })
{
    std::vector<std::pair<double, double>> open(graph.nrOfVertices(), {std::numeric_limits<double>::max(), std::numeric_limits<double>::max()});
    std::vector<bool> visited(graph.nrOfVertices(), false);
    std::vector<size_t> predecessor(graph.nrOfVertices());
    open[start_idx] = {0, heuristics(graph, start_idx, end_idx)};
    size_t current_node = start_idx;
    while (current_node != end_idx)
    {
        auto neighbors = graph.neighbours(current_node);
        for (auto &&i : neighbors)
        {
            if (!visited[i])
            {
                if ((open[i].first + open[i].second) > open[current_node].first + getEdgeLength(graph.edgeLabel(i, current_node)) + heuristics(graph, i, end_idx))
                {
                    open[i] = {open[current_node].first + getEdgeLength(graph.edgeLabel(i, current_node)), heuristics(graph, i, end_idx)};
                    predecessor[i] = current_node;
                }
            }
        }
        visited[current_node] = true;
        for (size_t i = 0; i < visited.size(); i++)
            if (!visited[i])
            {
                current_node = i;
                break;
            }
        int n = 0;
        for (n = 0; n < open.size(); n++)
            if (!visited[n] && open[n].first + open[n].second < open[current_node].first + open[current_node].second)
                current_node = n;
    }
    size_t node = end_idx;
    std::vector<size_t> result;
    while (node != start_idx)
    {
        result.push_back(node);
        node = predecessor[node];
    }
    result.push_back(start_idx);
    std::reverse(result.begin(), result.end());
    double result_distance = 0;
    for (size_t i = 1; i < result.size(); i++)
    {
        result_distance += getEdgeLength(graph.edgeLabel(result[i - 1], result[i]));
    }
    return {result_distance, result};
}

/**
 * @brief zwraca nr wierzchołków posortowanych topologicznie, zakładamy że graf nie ma cykli oraz jest spójny
 * 
 * @param graph graf w jakim sortujemy wierzchołki
 * @return std::stack<size_t> posortowane wierzchołki, podane nr 
 */
template <typename V, typename E>
std::vector<size_t> topological_sorting(Graph<V, E> &graph)
{
    std::vector<bool> visited(graph.nrOfVertices(), false);
    std::vector<size_t> result;
    size_t current = 0;
    while (std::any_of(visited.begin(), visited.end(), [](int i) { return i == false; }))
    {
        std::stack<size_t> work_s; 
        // szukamy wieszchołka startowego
        for (size_t i = 0; i < visited.size(); i++)
        {
            if (!visited[i])
            {
                current = i;
                break;
            }
        }
        work_s.push(current);

        while (!work_s.empty())
        {
            current = work_s.top();
            auto nei = graph.neighbours(current);
            // sprawdzamy czy ma sąsiadów
            if (!nei.empty())
            {
                bool test = true;
                for (auto n : nei)
                {
                    if (!visited[n])
                    {
                        test = false;
                        work_s.push(n);
                    }
                }
                if (test) // sąsiedzi byli odwiedzeni jak dobrze rozumiem to jak jeden sąsiad był odwiedzony to wszyscy byli
                {
                    visited[current] = true;
                    result.push_back(current);
                    work_s.pop();
                }
            }
            else // wierzchołek nie ma sąsiadów
            {
                visited[current] = true;
                result.push_back(current);
                work_s.pop();
            }
        }
    }
    return result;
}
