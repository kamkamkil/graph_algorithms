#pragma once
#include "graph.hpp"
template <typename V, typename E>
class Graph<V, E>::VerticesIterator
{
public:
    VerticesIterator(std::vector<V> *valueList_) : idVal(0), valueList(valueList_){};
    VerticesIterator(size_t id_, std::vector<V> *valueList_) : idVal(id_), valueList(valueList_){};
    bool operator==(const VerticesIterator &vi2) const { return (idVal == vi2.idVal); };
    bool operator!=(const VerticesIterator &vi2) const { return idVal != vi2.idVal; };
    VerticesIterator &operator++()
    {
        idVal++;
        return *this;
    };
    VerticesIterator operator++(int)
    {
        VerticesIterator iterator = *this;
        ++*this;
        return iterator;
    };
    V &operator*() const { return valueList->at(idVal); };
    // V *operator->() const;
    // zwraca id aktualnego wierzchołka
    int id() const { return idVal; };
    operator bool() const { return idVal < valueList->size(); };

private:
    size_t idVal;
    std::vector<V> *valueList;
};

template <typename V, typename E>
class Graph<V, E>::EdgesIterator
{
public:
    EdgesIterator(Graph<V, E> *graph_) : v1id_val(0), v2id_val(0), graph(graph_)
    {
        if (!graph->edgeExist(v1id_val, v2id_val))
            ++*this;
    };
    EdgesIterator(size_t v1id_val_, size_t v2id_val_, Graph<V, E> *graph_) : v1id_val(v1id_val_), v2id_val(v2id_val_), graph(graph_){};
    bool operator==(const EdgesIterator &ei) const { return v1id_val == ei.v1id_val && v2id_val == ei.v2id_val; };
    bool operator!=(const EdgesIterator &ei) const { return v1id_val != ei.v1id_val || v2id_val != ei.v2id_val; };
    EdgesIterator &operator++();
    EdgesIterator operator++(int)
    {
        EdgesIterator iterator = *this;
        ++*this;
        return iterator;
    };
    E &operator*() const { return graph->edgeLabel(v1id_val, v2id_val); };
    E *operator->() const;
    // zwraca id wierzchołka startowego
    std::size_t v1id() const { return v1id_val; };
    // zwraca id wierzchołka koncowego
    std::size_t v2id() const { return v2id_val; };
    operator bool() const { return v1id_val < graph->nrOfVertices() && v2id_val < graph->nrOfVertices(); };

private:
    size_t v1id_val;
    size_t v2id_val;
    Graph<V, E> *graph;
};
template <typename V, typename E>
class Graph<V, E>::DFSIterator
{
public:
    DFSIterator(){};
    DFSIterator(size_t start_, Graph<V, E> *graph_);
    bool operator==(const DFSIterator &dfsi) const { return (stack.empty() && dfsi.stack.empty()) || (current == dfsi.current && start == dfsi.start && graph == dfsi.graph); };
    bool operator!=(const DFSIterator &dfsi) const { return !(*this == dfsi); }
    DFSIterator &operator++();
    DFSIterator operator++(int)
    {
        DFSIterator iterator = *this;
        ++*this;
        return iterator;
    };
    V &operator*() const { return graph->vertexData(current); };
    V *operator->() const { return graph->vertexData(current); };
    std::size_t id() const{ return current;}
    operator bool() const {return !stack.empty();};

private:
    bool test(size_t vertex);
    std::vector<bool> visited;
    size_t current;
    size_t start;
    std::stack<size_t> stack;
    Graph<V, E> *graph;
};
template <typename V, typename E>
class Graph<V, E>::BFSIterator
{
public:
    BFSIterator() : queue(){};
    BFSIterator(size_t start_, Graph<V, E> *graph_);
    bool operator==(const BFSIterator &dfsi) const { return (queue.empty() && dfsi.queue.empty()) || (current == dfsi.current && start == dfsi.start && graph == dfsi.graph); };
    bool operator!=(const BFSIterator &dfsi) const { return !(*this == dfsi); }
    BFSIterator &operator++();
    BFSIterator operator++(int)
    {
        BFSIterator iterator = *this;
        ++*this;
        return iterator;
    };
    ;
    V &operator*() const { return graph->vertexData(queue.front()); };
    V *operator->() const { return graph->vertexData(queue.front()); };
    std::size_t id() const{ return current;}
    operator bool() const {return !queue.empty();};

private:
    std::vector<bool> visited;
    size_t current;
    size_t start;
    std::queue<size_t> queue;
    Graph<V, E> *graph;
};

template <typename V, typename E>
typename Graph<V, E>::EdgesIterator &Graph<V, E>::EdgesIterator::operator++()
{
    do
    {
        if (v2id_val < graph->nrOfVertices() - 1)
            v2id_val++;
        else
        {
            v1id_val++;
            v2id_val = 0;
        }
        if (v1id_val >= graph->nrOfVertices())
            break;
    } while (!graph->edgeExist(v1id_val, v2id_val));
    return *this;
}

template <typename V, typename E>
Graph<V, E>::DFSIterator::DFSIterator(size_t start_, Graph<V, E> *graph_) : current(start_), start(start_), graph(graph_)
{
    visited.resize(graph->nrOfVertices(), false);
    visited[start] = true;
    stack.push(start);
    size_t current = graph->neighbours(start).back();
}
template <typename V, typename E>
typename Graph<V, E>::DFSIterator &Graph<V, E>::DFSIterator::operator++()
{
    stack.push(current);
    visited[current] = true;
    if (test(current))
    {
        for (auto &&ver : graph->neighbours(current))
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
    while (!stack.empty() && visited[current])
    {
        operator++();
    }
    return *this;
};
template <typename V, typename E>
bool Graph<V, E>::DFSIterator::test(size_t vertex)
{
    for (auto &&n : graph->neighbours(vertex))
    {
        if (!visited[n])
            return true;
    }
    return false;
};
template <typename V, typename E>
Graph<V, E>::BFSIterator::BFSIterator(size_t start_, Graph<V, E> *graph_) : current(start_), start(start_), graph(graph_)
{
    visited.resize(graph->nrOfVertices(), false);
    visited[start] = true;
    queue.push(start);
}
template <typename V, typename E>
typename Graph<V, E>::BFSIterator &Graph<V, E>::BFSIterator::operator++()
{
    current = queue.front();
    queue.pop();
    visited[current] = true;
    if (!graph->neighbours(current).empty())
    {
        for (auto &&node : graph->neighbours(current))
        {
            if (!visited[node])
            {
                queue.push(node);
                visited[node] = true;
            }
        }
    }
    return *this;
}