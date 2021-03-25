#pragma once

#include <optional>
#include <cstdint>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <stack>
#include <iostream>
#include <bitset>
#include <functional>
#include <set>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>

/**
 * @brief klasa reprezentująca graf skierowany oparty na MACIERZY SĄSIEDZTWA
 * 
 * @tparam V dane przechowywane przez wierzcholki
 * @tparam E dane przechowywane przez krawedzie (etykiety)
 */
template <typename V, typename E>
class Graph
{
public:
    // iterator po wierzchołkach (rosnąco po id wierzchołków)
    class VerticesIterator;
    // iterator po istniejących krawędziach
    class EdgesIterator;
    // iterator przeszukiwania przez DFS
    class DFSIterator;
    // iterator przeszukiwania przez BFS
    class BFSIterator;

public:
    Graph() : verticesAmount(0){};
    Graph(const Graph<V, E> &source) = default;
    Graph(Graph<V, E> &&source) = default;
    Graph &operator=(const Graph<V, E> &source) = default;
    Graph &operator=(Graph<V, E> &&source) = default;
    ~Graph(){};

    /**
     * @brief dodaje nowy wierzchołek
     * 
     * @param vertex_data dane wieszchołka 
     * @return VerticesIterator na nowo utworzony wierzchołek
     */
    VerticesIterator insertVertex(const V &vertex_data);

    /**
     * @brief dodaje nową krawędź między wierzchołkami
     * 
     * @param vertex1_id pierwsza krawędź 
     * @param vertex2_id druga krawędź
     * @param label wartość krawędzi 
     * @param replace jeżeli prawda powtarzająca się krawędź zostanie zastąpiona, jeżeli fałsz to nie 
     * @return std::pair<EdgesIterator, bool>  iterator na krawędź oraz czy krawędź została dodana 
     */
    std::pair<EdgesIterator, bool> insertEdge(std::size_t vertex1_id, std::size_t vertex2_id, const E &label = E(), bool replace = true);

    /**
     * @brief usuwa wierzchołek
     * 
     * @param vertex_id id wieszchołka 
     * @return VerticesIterator  na kolejny wierzchołek, lub to samo co "endVertices()" w przypadku usunięcia ostatniego wierzchołka, lub braku wierzchołka o podanym id
     */
    VerticesIterator removeVertex(std::size_t vertex_id);

    /**
     * @brief usuwa krawedź między dwoma wierzchołkami o podanych id
     * 
     * @param vertex1_id pierwsza krawędź 
     * @param vertex2_id druga krawędź 
     * @return EdgesIterator na kolejną krawędź, lub to samo co "endEdges()" w przypadku usunięcia ostatniej krawedzi, lub braku krawędzi między wierzchołkami o podanych id
     */
    EdgesIterator removeEdge(std::size_t vertex1_id, std::size_t vertex2_id);

    /**
     * @brief sprawdza czy istnieje krawędź między dwoma wierzchołkami
     * 
     * @param vertex1_id pierwsza krawęd
     * @param vertex2_id druga krawędź 
     * @return true jeżeli istnieje 
     * @return false jeżeli nie istnieje 
     */
    bool edgeExist(std::size_t vertex1_id, std::size_t vertex2_id) const
    {
        return vertex1_id < matrix.size() && vertex2_id < matrix.size() && matrix[vertex1_id][vertex2_id];
    };

    /**
     * @brief dodaje krawędzie z pliku csv
     * 
     * @param filename nazwa pliku z którego mają być załadowane krawędzie 
     * @param addNode jeżeli prawda od razu będą dodane wierzchołki !notworking
     * @param replace jeżeli prawda powtarzająca się krawędź zostanie zastąpiona, jeżeli fałsz to nie 
     * 
     */
    void addFromCSV(std::string filename, bool addNode = true, bool replace = true);

    /**
     * @brief zwraca plik w formacie dot opisujący graf
     * 
     * @param filename 
     */
    void exportToDot(std::string filename); //@TODO

    /**
     * @brief zwraca ilość wierzchołków w grafie 
     * 
     * @return std::size_t ilość wierzchołków w grafie 
     */
    std::size_t nrOfVertices() const { return valueList.size(); };

    /**
     * @brief zwraca ilość krawędzi w grafie 
     * 
     * @return std::size_t ilość krawędzi w grafie
     */
    std::size_t nrOfEdges() const { return verticesAmount; };

    /**
     * @brief drukuje macierz sąsiedztwa na konsoli (debug) 
     * 
     */
    void printNeighborhoodMatrix() const;

    // 
    /**
     * @brief zwraca "VerticesIterator" do wierzchołka o podanym id, lub to samo co "endVertices()" w przypadku braku wierzchołka o podanym id 
     * 
     * @param vertex_id id wieszchołka 
     * @return VerticesIterator do wierzchołka o podanym id, lub to samo co "endVertices()"
     */
    VerticesIterator vertex(std::size_t vertex_id) { return vertex_id < valueList.size() ? VerticesIterator(vertex_id, &valueList) : endVertices(); };

    /**
     * @brief zwraca referencję do danych wierzchołka o podanym id
     * 
     * @param vertex_id id wieszchołka 
     * @return const V& referencja do danych 
     */
    const V &vertexData(std::size_t vertex_id) const { return valueList[vertex_id]; };

    /**
     * @brief zwraca referencję do danych wierzchołka o podanym id 
     * 
     * @param vertex_id id wieszchołka
     * @return V& referencja do danych
     */
    V &vertexData(std::size_t vertex_id) { return valueList[vertex_id]; };

    /**
     * @brief zwraca "EdgesIterator" do krawędzi pomiędzy wierzchołkami o podanych id, lub to samo co "endEdges()" w przypadku braku krawędzi między wierzchołkami o podanych id
     * 
     * @param vertex1_id id pierwszej krawędzi 
     * @param vertex2_id id drógiej krawędzi  
     * @return EdgesIterator do krawędzi pomiędzy wierzchołkami o podanych id, lub to samo co "endEdges()"
     */
    EdgesIterator edge(std::size_t vertex1_id, std::size_t vertex2_id) { return matrix[vertex1_id][vertex2_id] ? EdgesIterator(vertex1_id, vertex2_id, &matrix) : end(); };

     
    /**
     * @brief  zwraca referencję do danych (etykiety) krawędzi pomiędzy wierzchołkami o podanych id 
     * 
     * @param vertex1_id pierwszy wierzchołek
     * @param vertex2_id drógi wierzchołek
     * @return const E& referencja do danych 
     */
    const E &edgeLabel(std::size_t vertex1_id, std::size_t vertex2_id) const { return matrix[vertex1_id][vertex2_id].value(); };

    /**
     * @brief  zwraca referencję do danych (etykiety) krawędzi pomiędzy wierzchołkami o podanych id 
     * 
     * @param vertex1_id pierwszy wierzchołek
     * @param vertex2_id drógi wierzchołek
     * @return const E& referencja do danych 
     */
    E &edgeLabel(std::size_t vertex1_id, std::size_t vertex2_id) { return matrix[vertex1_id][vertex2_id].value(); };

    /**
     * @brief zwraca VerticesIterator na początek grafu (o najmniejszym id)
     * 
     * @return VerticesIterator na początek grafu (o najmniejszym id)
     */
    VerticesIterator begin() { return beginVertices(); };
    /**
     * @brief zwraca VerticesIterator za ostatnim wierzchołkiem grafu
     * 
     * @return VerticesIterator za ostatnim wierzchołkiem grafu
     */
    VerticesIterator end() { return endVertices(); };

    /**
     * @brief zwraca VerticesIterator na początek grafu (o najmniejszym id)
     * 
     * @return VerticesIterator na początek grafu (o najmniejszym id)
     */
    VerticesIterator beginVertices() { return VerticesIterator(0, &valueList); };

    /**
     * @brief zwraca VerticesIterator za ostatnim wierzchołkiem grafu
     * 
     * @return VerticesIterator za ostatnim wierzchołkiem grafu
     */
    VerticesIterator endVertices() { return VerticesIterator(valueList.size(), &valueList); };

    /**
     * @brief zwraca "EdgesIterator" na pierwszą krawędź 
     * 
     * @return EdgesIterator na pierwszą krawędź
     */
    EdgesIterator beginEdges() { return EdgesIterator(this); };

    /**
     * @brief zwraca "EdgesIterator" "za ostatnią" krawędź 
     * 
     * @return EdgesIterator "za ostatnią" krawędź
     */
    EdgesIterator endEdges() { return EdgesIterator(matrix.size(), 0, this); };

    /**
     * @brief zwraca wszystkie wierzchołki do których można się dostać z danego wieszchołka
     * 
     * @param vertex id wieszchołka którego szukamy sąsiadów 
     * @return std::vector<size_t> vector sąsiadów
     */
    std::vector<size_t> neighbours(size_t vertex) const;

    /**
     * @brief zwraca iterator DFS ma wierzchołek o podanym id 
     * 
     * @param vertex_id id wieszchołka 
     * @return DFSIterator na podanych wierzchołek
     */
    DFSIterator beginDFS(std::size_t vertex_id) { return DFSIterator(vertex_id, this); };

    /**
     * @brief zwraca "DFSIterator" "za ostatni" wierzcholek
     * 
     * @return DFSIterator "za ostatni" wierzcholek
     */
    DFSIterator endDFS() { return DFSIterator(); };

    /**
     * @brief zwraca "BFSIterator" na wierzcholek o podanym id 
     * 
     * @param vertex_id id wierzchołka 
     * @return BFSIterator na wierzcholek o podanym id
     */
    BFSIterator beginBFS(std::size_t vertex_id) { return BFSIterator(vertex_id, this); };

    /**
     * @brief zwraca "BFSIterator" "za ostatni" wierzcholek 
     * 
     * @return BFSIterator "BFSIterator" "za ostatni" wierzcholek
     */
    BFSIterator endBFS() { return BFSIterator(); };

private:
    std::vector<std::vector<std::optional<E>>> matrix;
    std::vector<V> valueList;
    std::size_t verticesAmount;
};
//implementacja iteratorów
#include "graphIterator.hpp"

/*
implementacja funkcji 
*/
template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::insertVertex(const V &vertex_data)
{
    valueList.push_back(vertex_data);
    std::optional<E> op;
    std::vector<std::optional<E>> vec(matrix.size(), op);
    matrix.push_back(vec);
    for (auto &&i : matrix)
    {
        i.push_back(op);
    }
    VerticesIterator it(valueList.size() - 1, &valueList);
    return it;
}
template <typename V, typename E>
std::pair<typename Graph<V, E>::EdgesIterator, bool> Graph<V, E>::insertEdge(std::size_t vertex1_id, std::size_t vertex2_id, const E &label, bool replace)
{
    if (vertex1_id >= nrOfVertices() || vertex2_id >= nrOfVertices())
        return {endEdges(), false};
    if (matrix[vertex1_id][vertex2_id])
    {
        if (replace)
        {
            matrix[vertex1_id][vertex2_id] = label;
            return {EdgesIterator(vertex1_id, vertex2_id, this), true};

            verticesAmount++;
        }
        return {EdgesIterator(vertex1_id, vertex2_id, this), false};
    }
    else
    {
        matrix[vertex1_id][vertex2_id] = label;
        verticesAmount++;

        return {EdgesIterator(vertex1_id, vertex2_id, this), false}; // poprawić chyba na false
    }
    return {EdgesIterator(vertex1_id, vertex2_id, this), false};
}

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::removeVertex(std::size_t vertex_id)
{
    if (vertex_id >= valueList.size())
        return endVertices();
    for (size_t i = 0; i < valueList.size(); i++)
    {
        if (i == vertex_id)
        {
            if (matrix[i][i])
                verticesAmount--;
            continue;
        }
        if (matrix[vertex_id][i] && !matrix[i][vertex_id])
            verticesAmount--;
        if (!matrix[vertex_id][i] && matrix[i][vertex_id])
            verticesAmount--;
        if (matrix[vertex_id][i] && matrix[i][vertex_id])
            verticesAmount -= 2;
    }
    matrix.erase(matrix.begin() + vertex_id);
    for (auto &&column : matrix)
    {
        column.erase(column.begin() + vertex_id);
    }
    valueList.erase(valueList.begin() + vertex_id);
    return VerticesIterator(vertex_id, &valueList);
}

template <typename V, typename E>
void Graph<V, E>::printNeighborhoodMatrix() const
{
    for (auto &&verse : matrix)
    {
        for (auto &&value : verse)
        {
            if (value)
                std::cout << value.value() << ",  ";
            else
                std::cout << "X "
                          << ",  ";
        }
        std::cout << std::endl;
    }
}

template <typename V, typename E>
typename Graph<V, E>::EdgesIterator Graph<V, E>::removeEdge(std::size_t vertex1_id, std::size_t vertex2_id)
{
    if (matrix[vertex1_id][vertex2_id])
    {
        matrix[vertex1_id][vertex2_id].reset();
        verticesAmount--;
        return ++EdgesIterator(vertex1_id, vertex2_id, this);
    }
    else
        return endEdges();
}

std::vector<std::string> split(const std::string &s, char delim)
{ //@TODO move ?
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

template <typename V, typename E>
void Graph<V, E>::addFromCSV(std::string filename, bool addNode, bool replace)
{
    std::string s;
    std::ifstream file(filename);

    while (std::getline(file, s))
    {
        auto v = split(s, ',');
        insertEdge(std::stoi(v[0]), std::stoi(v[1]), std::stoi(v[2]), replace);
    }

    file.close();
}

template <typename V, typename E>
std::vector<size_t> Graph<V, E>::neighbours(size_t vertex) const
{
    std::vector<size_t> result;
    for (size_t i = 0; i < valueList.size(); i++)
    {
        if (matrix[vertex][i])
            result.push_back(i);
    }
    return result;
}
