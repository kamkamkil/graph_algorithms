#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_CONSOLE_WIDTH 300
#include "../lib/catch/catch.hpp"
#include "../src/graph.hpp"
#include <string>

TEST_CASE("basic_operation")
{
    Graph<int, std::string> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertVertex(6);
    g.insertEdge(1, 2, "a");
    g.insertEdge(2, 1, "b");
    g.insertEdge(3, 5, "qq");
}
TEST_CASE("VerticesIterator", "[iterator]")
{
    Graph<int, std::string> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    int result[] = {1, 2, 3, 4, 5};
    int n = 0;
    for (auto &&value : g)
    {
        REQUIRE(value == result[n]);
        n++;
    }
    g.removeVertex(4);
    n = 0;
    for (auto &&value : g)
    {
        REQUIRE(value == result[n]);
        n++;
    }
}
TEST_CASE("EdgesIterator", "[iterator]")
{
    Graph<int, std::string> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertEdge(1, 1, "1_1");
    g.insertEdge(1, 2, "1_2");
    g.insertEdge(3, 1, "3_1");
    g.insertEdge(0, 1, "0_1");
    g.insertEdge(0, 0, "0_0");
    g.insertEdge(4, 4, "4_4");
    std::string result[] = {"0_0", "0_1", "1_1", "1_2", "3_1", "4_4"};
    int n = 0;
    for (auto it = g.beginEdges(); it != g.endEdges(); it++)
    {
        REQUIRE(*it == result[n]);
        n++;
    }
}
TEST_CASE("BFSIterator", "[iterator]")
{
    Graph<std::string, int> g;
    g.insertVertex("zero");
    g.insertVertex("jeden");
    g.insertVertex("dwa");
    g.insertVertex("trzy");
    g.insertVertex("cztery");
    g.insertVertex("pięć");
    g.insertVertex("sześć");
    g.insertVertex("siedem");
    g.insertEdge(0, 1, 1);
    g.insertEdge(0, 3, 1);
    g.insertEdge(1, 4, 1);
    g.insertEdge(1, 2, 1);
    g.insertEdge(2, 1, 1);
    g.insertEdge(2, 7, 1);
    g.insertEdge(3, 4, 1);
    g.insertEdge(4, 3, 1);
    g.insertEdge(4, 5, 1);
    g.insertEdge(5, 6, 1);
    g.insertEdge(6, 7, 1);
    g.insertEdge(7, 2, 1);
    g.insertEdge(7, 6, 1);
    std::string result[] = {"zero", "jeden", "trzy", "dwa", "cztery", "siedem", "pięć", "sześć"};
    int n = 0;
    for (auto it = g.beginBFS(0); it != g.endBFS(); it++)
    {
        REQUIRE(result[n] == *it);
        n++;
    }
}
TEST_CASE("DFSIterator", "[iterator]")
{
    Graph<std::string, int> g;
    g.insertVertex("zero");
    g.insertVertex("jeden");
    g.insertVertex("dwa");
    g.insertVertex("trzy");
    g.insertVertex("cztery");
    g.insertVertex("piec");
    g.insertEdge(0, 1, 1);
    g.insertEdge(1, 4, 1);
    g.insertEdge(1, 2, 1);
    g.insertEdge(2, 5, 1);
    g.insertEdge(3, 0, 1);
    g.insertEdge(4, 3, 1);
    g.insertEdge(4, 5, 1);
    std::string result[] = {"zero", "jeden", "dwa", "piec", "cztery", "trzy"};
    int n = 0;
    for (auto it = g.beginDFS(0); it != g.endDFS(); it++)
    {
        REQUIRE(result[n] == *it);
        n++;
    }
} //"zero", "jeden", "dwa", "piec", "cztery", "trzy"
TEST_CASE("insertVertex", "[insert]")
{
    SECTION("int_vertex")
    {
        Graph<int, std::string> g;
        REQUIRE(*(g.insertVertex(1)) == 1);
        REQUIRE(*(g.insertVertex(1)) == 1);
        REQUIRE(*(g.insertVertex(2)) == 2);
        REQUIRE(*(g.insertVertex(3)) == 3);
        REQUIRE(g.nrOfVertices() == 4);
        REQUIRE(g.vertexData(0) == 1);
        REQUIRE(g.vertexData(1) == 1);
        REQUIRE(g.vertexData(2) == 2);
        REQUIRE(g.vertexData(3) == 3);
    }
    SECTION("string_vertex")
    {
        Graph<std::string, std::string> g;
        REQUIRE(*(g.insertVertex("jeden")) == "jeden");
        REQUIRE(*(g.insertVertex("jeden")) == "jeden");
        REQUIRE(*(g.insertVertex("dwa")) == "dwa");
        REQUIRE(*(g.insertVertex("trzy")) == "trzy");
        REQUIRE(g.nrOfVertices() == 4);
        REQUIRE(g.vertexData(0) == "jeden");
        REQUIRE(g.vertexData(1) == "jeden");
        REQUIRE(g.vertexData(2) == "dwa");
    }
}
TEST_CASE("insertEdge", "[insert]")
{
    Graph<int, std::string> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    REQUIRE(g.nrOfVertices() == 5);

    auto pair = g.insertEdge(1, 2, "jeden_dwa");
    REQUIRE(*(pair.first) == "jeden_dwa");
    REQUIRE_FALSE(pair.second);
    pair = g.insertEdge(3, 4, "trzy_cztery");
    REQUIRE(*pair.first == "trzy_cztery");
    REQUIRE_FALSE(pair.second);
    pair = g.insertEdge(2, 1, "dwa_jeden");
    REQUIRE(*pair.first == "dwa_jeden");
    REQUIRE_FALSE(pair.second);
    pair = g.insertEdge(1, 2, "jeden_dwa_zmieniony");
    REQUIRE(*pair.first == "jeden_dwa_zmieniony");
    REQUIRE(pair.second);
    pair = g.insertEdge(1, 2, "jeden_dwa_nowy", false);
    REQUIRE(*pair.first == "jeden_dwa_zmieniony");
    REQUIRE_FALSE(pair.second);
    pair = g.insertEdge(5, 5, "nie_powinno_sie_udac");
    REQUIRE(pair.first == g.endEdges());
    REQUIRE_FALSE(pair.second);
    REQUIRE(g.edgeExist(1, 2));
    REQUIRE(g.edgeExist(3, 4));
    REQUIRE_FALSE(g.edgeExist(4, 4));
    REQUIRE_FALSE(g.edgeExist(5, 5));
    REQUIRE(g.edgeLabel(3, 4) == "trzy_cztery");
    REQUIRE(g.edgeLabel(1, 2) == "jeden_dwa_zmieniony");
    REQUIRE(g.nrOfEdges() == 3);
}

TEST_CASE("removeVertex", "[remove]")
{
    Graph<int, std::string> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertVertex(6);
    REQUIRE(g.nrOfVertices() == 6);
    for (size_t verse = 0; verse < 6; verse++)
    {
        for (size_t column = 0; column < 6; column++)
        {
            if (column * verse % 2 == 0)
                g.insertEdge(verse, column, std::to_string(verse * 10 + column));
        }
    }
    REQUIRE(g.nrOfEdges() == 27);
    SECTION("half_empty_vertex")
    {
        g.removeVertex(1);
        REQUIRE(g.nrOfEdges() == 21);
        REQUIRE(g.nrOfVertices() == 5);
    }
    SECTION("full_vertex")
    {
        g.removeVertex(2);
        REQUIRE(g.nrOfEdges() == 16);
        REQUIRE(g.nrOfVertices() == 5);
    }
}
TEST_CASE("removeEdge", "[remove]")
{
    Graph<int, std::string> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertVertex(6);
    REQUIRE(g.nrOfVertices() == 6);
    g.insertEdge(1, 2, "jeden_dwa");
    g.insertEdge(3, 1, "trzy_jeden");
    g.insertEdge(5, 0, "piec_zero");
    g.insertEdge(2, 2, "dwa_dwa");
    g.insertEdge(3, 2, "trzy_dwa");
    g.insertEdge(0, 0, "zero_zero");
    g.removeEdge(0, 0);
    REQUIRE_FALSE(g.edgeExist(0, 0));
    g.removeEdge(3, 2);
    g.removeEdge(1, 2);
    REQUIRE_FALSE(g.edgeExist(3, 2));
    REQUIRE_FALSE(g.edgeExist(1, 2));
}
TEST_CASE("allneighbours")
{
    Graph<int, std::string> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertVertex(6);
    for (size_t verse = 0; verse < 6; verse++)
    {
        for (size_t column = 0; column < 6; column++)
        {
            if (column * verse % 2 == 0)
                g.insertEdge(verse, column, std::to_string(verse * 10 + column));
        }
    }
    std::vector<size_t> temp = {0, 1, 2, 3, 4, 5};
    REQUIRE(g.neighbours(0) == temp);
    temp = {0, 2, 4};
    REQUIRE(g.neighbours(1) == temp);
}
