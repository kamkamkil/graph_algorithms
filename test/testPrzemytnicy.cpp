#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_CONSOLE_WIDTH 300
#include "../lib/catch/catch.hpp"
#include "../src/przemytnicylib.cpp"

TEST_CASE("example_from_exercise")
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
    REQUIRE(przemytnicy(g) == 60);
}