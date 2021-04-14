#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "../lib/catch/catch.hpp"
#include "../src/przemytnicylib.cpp"

TEST_CASE("benchmark_easy", "[benchmark]")
{
    Graph<int, int> g;
    g.insertVertex(200);
    g.insertVertex(100);
    g.insertVertex(40);
    g.insertVertex(2);
    g.insertEdge(0, 1, 10);
    g.insertEdge(0, 2, 5);
    g.insertEdge(1, 0, 25);
    g.insertEdge(2, 1, 10);
    g.insertEdge(2, 3, 5);
    g.insertEdge(3, 0, 50);
    BENCHMARK("naiveAlgorithm")
    {
        return przemytnicyLazy(g);
    };
    BENCHMARK("betterAlgorithm")
    {
        return przemytnicy(g);
    };
}
TEST_CASE("benchmark_hard", "[benchmark]")
{
    Graph<int, int> g;
    g.insertVertex(4000);
    g.insertVertex(2);
    g.insertVertex(2);
    g.insertVertex(2);
    g.insertVertex(2);
    g.insertVertex(2);
    g.insertVertex(2);
    g.insertVertex(2);
    g.insertEdge(0, 1, 1);
    g.insertEdge(1, 2, 1);
    g.insertEdge(2, 3, 1);
    g.insertEdge(3, 4, 1);
    g.insertEdge(4, 5, 1);
    g.insertEdge(5, 6, 1);
    g.insertEdge(6, 7, 1);
    g.insertEdge(7, 0, 1);

    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertEdge(0, 9, 100);
    g.insertEdge(0, 10, 100);
    g.insertEdge(0, 11, 100);
    g.insertEdge(11, 12, 100);
    g.insertEdge(11, 13, 100);
    g.insertEdge(11, 14, 100);
    g.insertEdge(11, 15, 100);
    g.insertEdge(11, 16, 100);
    g.insertEdge(16, 17, 100);
    g.insertEdge(17, 18, 100);
    g.insertEdge(18, 19, 100);
    g.insertEdge(19, 0, 100);
    g.insertEdge(11, 0, 100);
    g.insertEdge(0, 20, 100);
    g.insertEdge(0, 21, 100);
    g.insertEdge(0, 22, 100);
    g.insertEdge(15, 0, 100);
    g.insertEdge(0, 23, 100);
    REQUIRE(przemytnicy(g).second == std::vector<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 0});
    REQUIRE(przemytnicy(g).first == 9);
    REQUIRE(przemytnicyLazy(g).second == std::vector<size_t>{0, 1, 2, 3, 4, 5, 6, 7});
    REQUIRE(przemytnicyLazy(g).first == 9);
    BENCHMARK("naiveAlgorithm")
    {
        return przemytnicyLazy(g);
    };
    BENCHMARK("betterAlgorithm")
    {
        return przemytnicy(g);
    };
}