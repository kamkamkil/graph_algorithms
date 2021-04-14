#define CATCH_CONFIG_MAIN
// #define CATCH_CONFIG_CONSOLE_WIDTH 300
#include "../lib/catch/catch.hpp"
#include "skarbonkaLib.cpp"

TEST_CASE("example_from_exercise")
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
}

TEST_CASE("every_verticle_to_themself")
{
    Graph<int, int> g;
    g.insertVertex();
    g.insertVertex();
    g.insertVertex();
    g.insertVertex();
    g.insertVertex();
    REQUIRE(skarbonka(g) == 5);
}

TEST_CASE("only_pair")
{
    Graph<int, int> g;
    g.insertVertex();
    g.insertVertex();
    g.insertVertex();
    g.insertVertex();
    g.insertVertex();
    g.insertVertex();
    g.insertEdge(0, 1);
    g.insertEdge(1, 0);
    g.insertEdge(2, 3);
    g.insertEdge(3, 2);
    g.insertEdge(4, 5);
    g.insertEdge(5, 4);
    g.exportToDot("../../temp.dot");
    REQUIRE(skarbonka(g) == 3);
}

TEST_CASE("one_loop")
{
    Graph<int, int> g;
    g.insertVertex();
    g.insertVertex();
    g.insertVertex();
    g.insertVertex();
    g.insertVertex();
    g.insertVertex();
    g.insertEdge(0, 1);
    g.insertEdge(1, 2);
    g.insertEdge(2, 3);
    g.insertEdge(3, 4);
    g.insertEdge(4, 5);
    g.insertEdge(5, 0);
    REQUIRE(skarbonka(g) == 1);

}