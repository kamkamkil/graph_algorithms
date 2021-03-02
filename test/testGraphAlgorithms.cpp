#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_CONSOLE_WIDTH 300
#include "../lib/catch/catch.hpp"
#include "../src/graph.hpp"
#include "../src/graphAlgorithms.hpp"
#include <string>

TEST_CASE("DFS", "[Search_algorithm]")
{
    std::vector<std::string> result;
    std::vector<std::string> requireResult;
    Graph<std::string, int> g;
    g.insertVertex("zero");
    g.insertVertex("jeden");
    g.insertVertex("dwa");
    g.insertVertex("trzy");
    g.insertVertex("cztery");
    g.insertVertex("piec");
    SECTION("easy_grah")
    {
        g.insertEdge(0, 3, 1);
        g.insertEdge(3, 4, 1);
        g.insertEdge(4, 1, 1);
        g.insertEdge(4, 2, 1);
        g.insertEdge(4, 5, 1);
        DFS<std::string, int>(g, 0, [&](const std::string &v) -> void { result.push_back(v); });
        requireResult = {"zero", "trzy", "cztery", "jeden", "dwa", "piec"};
        REQUIRE(result == requireResult);
    }
    SECTION("multiple_road_from_begining")
    {
        g.insertEdge(0, 1, 1);
        g.insertEdge(0, 2, 1);
        g.insertEdge(0, 3, 1);
        g.insertEdge(0, 4, 1);
        g.insertEdge(4, 5, 1);
        DFS<std::string, int>(g, 0, [&](const std::string &v) -> void { result.push_back(v); });
        requireResult = {"zero", "cztery", "piec", "jeden", "dwa", "trzy"};
        REQUIRE(result == requireResult);
    }
    SECTION("big_loop")
    {
        g.insertEdge(0, 1, 1);
        g.insertEdge(1, 2, 1);
        g.insertEdge(2, 3, 1);
        g.insertEdge(3, 4, 1);
        g.insertEdge(4, 5, 1);
        g.insertEdge(5, 0, 1);
        DFS<std::string, int>(g, 0, [&](const std::string &v) -> void { result.push_back(v); });
        requireResult = {"zero", "jeden", "dwa", "trzy", "cztery", "piec"};
        REQUIRE(result == requireResult);
    }
    SECTION("small_loops")
    {
        g.insertEdge(0, 1, 1);
        g.insertEdge(1, 4, 1);
        g.insertEdge(1, 2, 1);
        g.insertEdge(2, 5, 1);
        g.insertEdge(3, 0, 1);
        g.insertEdge(4, 3, 1);
        g.insertEdge(4, 5, 1);
        DFS<std::string, int>(g, 0, [&](const std::string &v) -> void { result.push_back(v); });
        requireResult = {"zero", "jeden", "dwa", "piec", "cztery", "trzy"};
        REQUIRE(result == requireResult);
    }
    SECTION("not_all")
    {
        g.insertEdge(0, 1, 1);
        g.insertEdge(1, 4, 1);
        g.insertEdge(4, 3, 1);
        g.insertEdge(3, 4, 1);
        DFS<std::string, int>(g, 0, [&](const std::string &v) -> void { result.push_back(v); });
        requireResult = {"zero", "jeden", "cztery", "trzy"};
        REQUIRE(result == requireResult);
    }
    SECTION("empty_grapf")
    {
        DFS<std::string, int>(g, 0, [&](const std::string &v) -> void { result.push_back(v); });
        requireResult = {"zero"};
        REQUIRE(result == requireResult);
    }
}
TEST_CASE("BFS", "[Search_algorithm]")
{
    std::vector<std::string> result;
    std::vector<std::string> requireResult;
    Graph<std::string, int> g;
    g.insertVertex("zero");
    g.insertVertex("jeden");
    g.insertVertex("dwa");
    g.insertVertex("trzy");
    g.insertVertex("cztery");
    g.insertVertex("pięć");
    g.insertVertex("sześć");
    g.insertVertex("siedem");
    SECTION("simple_graph")
    {
        g.insertEdge(0, 1, 1);
        g.insertEdge(0, 3, 1);
        g.insertEdge(1, 2, 1);
        g.insertEdge(1, 7, 1);
        g.insertEdge(3, 4, 1);
        g.insertEdge(4, 5, 1);
        g.insertEdge(4, 6, 1);
        BFS<std::string, int>(g, 0, [&](const std::string &v) -> void { result.push_back(v); });
        requireResult = {"zero", "jeden", "trzy", "dwa", "siedem", "cztery", "pięć", "sześć"};
        REQUIRE(result == requireResult);
    }
    SECTION("star_like_graph")
    {
        g.insertEdge(0, 1, 1);
        g.insertEdge(0, 2, 1);
        g.insertEdge(0, 3, 1);
        g.insertEdge(0, 4, 1);
        g.insertEdge(0, 5, 1);
        g.insertEdge(0, 6, 1);
        g.insertEdge(0, 7, 1);
        BFS<std::string, int>(g, 0, [&](const std::string &v) -> void { result.push_back(v); });
        requireResult = {"zero", "jeden", "dwa", "trzy", "cztery", "pięć", "sześć", "siedem"};
        REQUIRE(result == requireResult);
    }
    SECTION("big_loop_graph")
    {
        g.insertEdge(0, 1, 1);
        g.insertEdge(1, 2, 1);
        g.insertEdge(2, 3, 1);
        g.insertEdge(3, 4, 1);
        g.insertEdge(4, 5, 1);
        g.insertEdge(5, 6, 1);
        g.insertEdge(6, 7, 1);
        g.insertEdge(7, 0, 1);
        BFS<std::string, int>(g, 0, [&](const std::string &v) -> void { result.push_back(v); });
        requireResult = {"zero", "jeden", "dwa", "trzy", "cztery", "pięć", "sześć", "siedem"};
        REQUIRE(result == requireResult);
    }
    SECTION("small_loops_graph")
    {
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
        BFS<std::string, int>(g, 0, [&](const std::string &v) -> void { result.push_back(v); });
        requireResult = {"zero", "jeden", "trzy", "dwa", "cztery", "siedem", "pięć", "sześć"};
        REQUIRE(result == requireResult);
    }
    SECTION("emppty_graph")
    {
        BFS<std::string, int>(g, 0, [&](const std::string &v) -> void { result.push_back(v); });
        requireResult = {"zero"};
        REQUIRE(result == requireResult);
    }
}
TEST_CASE("Dijkstras_algorithm")
{
    Graph<std::string, int> g;
    g.insertVertex("zero");
    g.insertVertex("jeden");
    g.insertVertex("dwa");
    g.insertVertex("trzy");
    g.insertVertex("cztery");
    g.insertEdge(0, 1, 1);
    g.insertEdge(0,2,3);
    g.insertEdge(1, 2, 1);
    g.insertEdge(1, 4, 10);
    g.insertEdge(2, 3, 3);
    g.insertEdge(3, 4, 3);

    auto result = dijkstra<std::string, int>(g, 0, 4);
    std::cout << result.first << std::endl;
    for (auto &&i : result.second)
    {
        std::cout << i << std::endl;
    }


}
