#define CATCH_CONFIG_MAIN
// #define CATCH_CONFIG_CONSOLE_WIDTH 300
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
    REQUIRE(przemytnicy(g).first == 60);
}
TEST_CASE("gold_is_the_cheapest")
{
    Graph<int, int> g;
    g.insertVertex(2);
    g.insertVertex(100);
    g.insertVertex(40);
    g.insertVertex(2);
    g.insertEdge(0, 1, 10);
    g.insertEdge(0, 2, 5);
    g.insertEdge(1, 0, 25);
    g.insertEdge(2, 1, 10);
    g.insertEdge(2, 3, 5);
    g.insertEdge(3, 0, 50);
    REQUIRE(przemytnicy(g).first == 1);
    REQUIRE(przemytnicy(g).second == std::vector<size_t>{});
}

TEST_CASE("alternative_paths")
{
    Graph<int, int> g;

    g.insertVertex(1000);
    g.insertVertex(60);
    g.insertVertex(40);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(200);
    g.insertVertex(10);
    g.insertEdge(0, 1, 20);
    g.insertEdge(0, 2, 30);
    g.insertEdge(1, 3, 30);
    g.insertEdge(2, 3, 20);
    g.insertEdge(3, 4, 20);
    g.insertEdge(3, 5, 5);
    g.insertEdge(4, 6, 100);
    g.insertEdge(5, 6, 200);
    g.insertEdge(6, 0, 25);
    // g.exportToDot("../../dot.d",true,true);
    REQUIRE(przemytnicy(g).second == std::vector<size_t>{0, 1, 3, 4, 6});
    REQUIRE(przemytnicy(g).first == 200);
}

TEST_CASE("many_dead_ends")
{
    Graph<int, int> g;
    g.insertVertex(2000);
    g.insertVertex(60);
    g.insertVertex(40);
    g.insertVertex(100);
    g.insertVertex(100);
    g.insertVertex(200);
    g.insertVertex(10);
    g.insertVertex(20);
    g.insertVertex(30);
    g.insertVertex(40);
    g.insertVertex(50);
    g.insertEdge(0,1 ,10 );
    g.insertEdge(0,2 ,20 );
    g.insertEdge(0,3 ,30 );
    g.insertEdge(1,4 ,40 );
    g.insertEdge(1,5 ,100 );
    g.insertEdge(5,6 ,100 );
    g.insertEdge(6,7 ,100 );
    g.insertEdge(6,8 ,100 );
    g.insertEdge(2,9 ,100 );
    g.insertEdge(9,10 ,40 );
    g.insertEdge(10,0 ,40 );
    g.exportToDot("../../dot.dot");
    REQUIRE(przemytnicy(g).second == std::vector<size_t>{ 0, 2, 9, 10 });
    REQUIRE(przemytnicy(g).first == 220);
}

TEST_CASE("Same_path_cost_diffrent_node_cost")
{
    Graph<int, int> g;
    g.insertVertex(2000);
    g.insertVertex(50);
    g.insertVertex(100);
    g.insertEdge(0,1 ,10 );
    g.insertEdge(0,2 ,10 );
    g.insertEdge(1,0 ,10 );
    g.insertEdge(2,0 ,10 );
    REQUIRE(przemytnicy(g).second == std::vector<size_t>{ 0,1 });
    REQUIRE(przemytnicy(g).first == 45);
}
