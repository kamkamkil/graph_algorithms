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

// Uwaga! Kod powinien być odporny na błędy i każda z metod jeżeli zachodzi niebezpieczeństwo wywołania z niepoprawnymi parametrami powinna zgłaszac odpowiednie wyjątki!

// klasa reprezentująca graf skierowany oparty na MACIERZY SĄSIEDZTWA
// V - dane przechowywane przez wierzcholki
// E - dane przechowywane przez krawedzie (etykiety)
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

    // dodaje nowy wierzchołek z danymi przyjętymi w argumencie (wierzchołek powinien posiadać kopie danych) i zwraca "VerticesIterator" na nowo utworzony wierzchołek
    VerticesIterator insertVertex(const V &vertex_data);
    // dodaje nową krawędź między wierzchołkami o id "vertex1_id" i "vertex2_id" i zwraca "EdgesIterator" na nowo dodaną krawędź, oraz informację o tym czy została dodana nowa krawędź, czy nie
    // jeśli krawędź między podanymi wierzchołkami już istnieje to działanie funkcji zależy od ostatniego argumentu
    // jeśli ostatni argument przyjmuje wartość "true" to krawędź zostaje zastąpiona, jeśli "false" to nie
    std::pair<EdgesIterator, bool> insertEdge(std::size_t vertex1_id, std::size_t vertex2_id, const E &label = E(), bool replace = true);
    // usuwa wierzchołek o podanym id i zwraca "VerticesIterator" na kolejny wierzchołek, lub to samo co "endVertices()" w przypadku usunięcia ostatniego wierzchołka, lub braku wierzchołka o podanym id
    VerticesIterator removeVertex(std::size_t vertex_id);
    // usuwa krawedź między dwoma wierzchołkami o podanych id i zwraca "EdgesIterator" na kolejną krawędź, lub to samo co "endEdges()" w przypadku usunięcia ostatniej krawedzi, lub braku krawędzi między wierzchołkami o podanych id
    EdgesIterator removeEdge(std::size_t vertex1_id, std::size_t vertex2_id);
    // zwraca true jeśli istnieje krawędź między wierzchołkami o podanych id, false w przeciwnym razie
    // O(1)
    bool edgeExist(std::size_t vertex1_id, std::size_t vertex2_id) const
    {
        return vertex1_id < matrix.size() && vertex2_id < matrix.size() && matrix[vertex1_id][vertex2_id];
    };
    // zwraca ilość wierzchołków w grafie
    // O(1)
    std::size_t nrOfVertices() const { return valueList.size(); };
    // zwraca ilość krawędzi w grafie
    // O(1)
    std::size_t nrOfEdges() const { return verticesAmount; };
    // drukuje macierz sąsiedztwa na konsoli (debug)
    void printNeighborhoodMatrix() const;
    // zwraca "VerticesIterator" do wierzchołka o podanym id, lub to samo co "endVertices()" w przypadku braku wierzchołka o podanym id
    VerticesIterator vertex(std::size_t vertex_id) { return vertex_id < valueList.size() ? VerticesIterator(vertex_id, &valueList) : endVertices(); };
    // zwraca referencję do danych wierzchołka o podanym id
    const V &vertexData(std::size_t vertex_id) const { return valueList[vertex_id]; };
    // zwraca referencję do danych wierzchołka o podanym id
    V &vertexData(std::size_t vertex_id) { return valueList[vertex_id]; };
    // zwraca "EdgesIterator" do krawędzi pomiędzy wierzchołkami o podanych id, lub to samo co "endEdges()" w przypadku braku krawędzi między wierzchołkami o podanych id
    EdgesIterator edge(std::size_t vertex1_id, std::size_t vertex2_id) { return matrix[vertex1_id][vertex2_id] ? EdgesIterator(vertex1_id, vertex2_id, &matrix) : end(); };
    // zwraca referencję do danych (etykiety) krawędzi pomiędzy wierzchołkami o podanych id
    const E &edgeLabel(std::size_t vertex1_id, std::size_t vertex2_id) const { return matrix[vertex1_id][vertex2_id].value(); };
    // zwraca referencję do danych (etykiety) krawędzi pomiędzy wierzchołkami o podanych id
    E &edgeLabel(std::size_t vertex1_id, std::size_t vertex2_id) { return matrix[vertex1_id][vertex2_id].value(); };
    VerticesIterator begin() { return beginVertices(); };
    VerticesIterator end() { return endVertices(); };
    // zwraca "VerticesIterator" na pierwszy wierzchołek (o najmniejszym id)
    VerticesIterator beginVertices() { return VerticesIterator(0, &valueList); };
    // zwraca "VerticesIterator" "za ostatni" wierzchołek
    VerticesIterator endVertices() { return VerticesIterator(valueList.size(), &valueList); };
    // zwraca "EdgesIterator" na pierwszą krawędź
    EdgesIterator beginEdges() { return EdgesIterator(this); };
    // zwraca "EdgesIterator" "za ostatnią" krawędź
    EdgesIterator endEdges() { return EdgesIterator(matrix.size(), 0, this); };
    //zwraca wszystkie wierzchołki do których można się dostać z danego wieszchołka
    std::vector<size_t> neighbours(size_t vertex) const;
    DFSIterator beginDFS(std::size_t vertex_id) { return DFSIterator(vertex_id, this); };
    // zwraca "DFSIterator" "za ostatni" wierzcholek
    DFSIterator endDFS() { return DFSIterator(); };
    // zwraca "BFSIterator" na wierzcholek o podanym id
    BFSIterator beginBFS(std::size_t vertex_id) { return BFSIterator(vertex_id, this); };
    // zwraca "BFSIterator" "za ostatni" wierzcholek
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