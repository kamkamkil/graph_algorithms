#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "../lib/catch/catch.hpp"
#include "skarbonkaLib.cpp"

TEST_CASE("simple_example", "[benchmark]")
{
    Graph<int, int> g;
    g.insertVertex();
    g.insertVertex();
    g.insertVertex();
    g.insertVertex();
    g.insertEdge(0, 1);
    g.insertEdge(1, 0);
    g.insertEdge(2, 1);
    g.insertEdge(4, 4);
    REQUIRE(skarbonka(g) == 2);
    REQUIRE(skarbonkaNaive(g) == 2);
    BENCHMARK("naive_algorithm")
    {
        return skarbonkaNaive(g);
    };
    BENCHMARK("improved_algorithm")
    {
        return skarbonka(g);
    };
}
TEST_CASE("harder_benchark", "[benchmark]")
{
    Graph<int, int> g;
    for (size_t i = 0; i < 16; i++)
        g.insertVertex();
    g.insertEdge(0, 1);
    g.insertEdge(1, 2);
    g.insertEdge(2, 3);
    g.insertEdge(3, 4);
    g.insertEdge(4, 5);
    g.insertEdge(5, 6);
    g.insertEdge(6, 7);
    g.insertEdge(8, 7);
    g.insertEdge(9, 0);
    g.insertEdge(10, 1);
    g.insertEdge(11, 2);
    g.insertEdge(12, 3);
    g.insertEdge(13, 4);
    g.insertEdge(14, 5);
    g.insertEdge(15, 6);
    REQUIRE(skarbonka(g) == 8);
    REQUIRE(skarbonkaNaive(g) == 8);
    BENCHMARK("naive algorithm")
    {
        return skarbonkaNaive(g);
    };
    BENCHMARK("improved_algorithm")
    {
        return skarbonka(g);
    };
}