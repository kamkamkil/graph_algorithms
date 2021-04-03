#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_CONSOLE_WIDTH 300
#include "../lib/catch/catch.hpp"
#include "../src/graph.hpp"
#include "../src/graphAlgorithms.hpp"
#include <string>
#include <algorithm>

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
    g.insertEdge(0, 2, 3);
    g.insertEdge(1, 2, 1);
    g.insertEdge(1, 4, 10);
    g.insertEdge(2, 3, 3);
    g.insertEdge(3, 4, 3);

    auto result = dijkstra(g, 0, 4);
    std::vector rresult({0, 1, 2, 3, 4});
    REQUIRE(result.first == 8);
    for (size_t i = 0; i < result.second.size(); i++)
    {
        REQUIRE(result.second[i] == rresult[i]);
    }
}

TEST_CASE("Topological_sorting")
{
    SECTION("first_graph")
    {
        Graph<std::string, int> g;
        g.insertVertex("zero");
        g.insertVertex("jeden");
        g.insertVertex("dwa");
        g.insertVertex("trzy");
        g.insertVertex("cztery");
        g.insertEdge(0, 1, 1);
        g.insertEdge(0, 2, 3);
        g.insertEdge(1, 2, 1);
        g.insertEdge(1, 4, 10);
        g.insertEdge(2, 3, 3);
        g.insertEdge(3, 4, 3);
        auto sorted = topological_sorting(g);
        for (auto i = (++sorted.begin()); i != sorted.end(); i++)
        {
            for (auto iter = g.beginDFS(*i); iter != g.endDFS(); iter++)
            {
                REQUIRE_FALSE(std::find(sorted.begin(), i, iter.id()) == sorted.end());
            }
        }
    }
    SECTION("second_graph")
    {
        Graph<int, int> g;
        g.insertVertex(0);
        g.insertVertex(1);
        g.insertVertex(2);
        g.insertVertex(3);
        g.insertVertex(4);
        g.insertVertex(5);
        g.insertVertex(6);
        g.insertVertex(7);
        g.insertVertex(8);
        g.insertVertex(9);
        g.insertVertex(10);

        g.insertEdge(1, 0);
        g.insertEdge(0, 2);
        g.insertEdge(3, 2);
        g.insertEdge(2, 4);
        g.insertEdge(5, 4);
        g.insertEdge(4, 6);
        g.insertEdge(7, 6);
        g.insertEdge(8, 9);
        g.insertEdge(9, 10);
        g.insertEdge(10, 6);
        g.insertEdge(0, 8);
        g.insertEdge(3, 8);
        auto sorted = topological_sorting(g);
        for (auto i = (++sorted.begin()); i != sorted.end(); i++)
        {
            for (auto iter = g.beginDFS(*i); iter != g.endDFS(); iter++)
            {
                REQUIRE_FALSE(std::find(sorted.begin(), i, iter.id()) == sorted.end());
            }
        }
    }
}
TEST_CASE("transitive_Closure")
{
    SECTION("first_graph")
    {
        Graph<std::string, int> g;
        g.insertVertex("zero");
        g.insertVertex("jeden");
        g.insertVertex("dwa");
        g.insertVertex("trzy");
        g.insertVertex("cztery");
        g.insertEdge(0, 1, 1);
        g.insertEdge(0, 2, 3);
        g.insertEdge(1, 2, 1);
        g.insertEdge(1, 4, 10);
        g.insertEdge(2, 3, 3);
        g.insertEdge(3, 4, 3);
        auto tc = transitiveClosure(g);

        for (size_t i = 0; i < tc.size(); i++)
        {
            size_t temp = std::count(tc[i].begin(), tc[i].end(), true);
            for (auto dfs = g.beginDFS(i); dfs != g.endDFS(); dfs++)
            {
                CHECK(tc[i][dfs.id()]);
                if (tc[i][dfs.id()])
                    temp--;
            }
            CHECK(temp == 0);
        }
    }
    SECTION("bigger_graph")
    {
        Graph<int, int> g;
        g.insertVertex(0);
        g.insertVertex(1);
        g.insertVertex(2);
        g.insertVertex(3);
        g.insertVertex(4);
        g.insertVertex(5);
        g.insertVertex(6);
        g.insertVertex(7);
        g.insertVertex(8);
        g.insertVertex(9);
        g.insertVertex(10);

        g.insertEdge(0, 2);
        g.insertEdge(2, 3);
        g.insertEdge(4, 3);
        g.insertEdge(3, 5);
        g.insertEdge(3, 6);
        g.insertEdge(6, 2);
        g.insertEdge(2, 4);
        g.insertEdge(7, 5);
        g.insertEdge(8, 7);
        g.insertEdge(8, 4);
        g.insertEdge(9, 0);
        g.insertEdge(8, 9);
        g.insertEdge(6, 8);
        g.insertEdge(5, 10);
        g.insertEdge(11, 10);

        auto tc = transitiveClosure(g);

        for (size_t i = 0; i < tc.size(); i++)
        {
            size_t temp = std::count(tc[i].begin(), tc[i].end(), true);
            for (auto dfs = g.beginDFS(i); dfs != g.endDFS(); dfs++)
            {
                CHECK(tc[i][dfs.id()]);
                if (tc[i][dfs.id()])
                    temp--;
            }
            CHECK(temp == 0);
        }
    }
}

TEST_CASE("cycle")
{
    Graph<int, int> g;
    g.insertVertex(0);
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertVertex(6);
    g.insertVertex(7);
    g.insertVertex(8);
    g.insertVertex(9);
    SECTION("simple_loop")
    {
        g.insertEdge(0, 1);
        g.insertEdge(1, 2);
        g.insertEdge(2, 3);
        g.insertEdge(3, 4);
        g.insertEdge(4, 5);
        g.insertEdge(5, 6);
        g.insertEdge(6, 7);
        g.insertEdge(7, 8);
        g.insertEdge(8, 3);
        g.insertEdge(9, 0);
        std::cout << "1" << std::endl;
        graphCycle(g);
    }
    SECTION("line")
    {
        g.insertEdge(0, 1);
        g.insertEdge(1, 2);
        g.insertEdge(2, 3);
        g.insertEdge(3, 4);
        g.insertEdge(4, 5);
        g.insertEdge(5, 6);
        g.insertEdge(6, 7);
        g.insertEdge(7, 8);
        g.insertEdge(8, 9);
        std::cout << "2" << std::endl;
        graphCycle(g);
    }
    SECTION("tree")
    {
        g.insertEdge(0, 1);
        g.insertEdge(0, 2);
        g.insertEdge(0, 3);
        g.insertEdge(1, 4);
        g.insertEdge(1, 5);
        g.insertEdge(2, 6);
        g.insertEdge(2, 7);
        g.insertEdge(7, 8);
        g.insertEdge(7, 9);
        std::cout << "3" << std::endl;
        graphCycle(g);
    }
    SECTION("many_loop")
    {
        g.insertEdge(0, 1);
        g.insertEdge(1, 2);
        g.insertEdge(2, 3);
        g.insertEdge(2, 5);
        g.insertEdge(3, 4);
        g.insertEdge(4, 5);
        g.insertEdge(5, 6);
        g.insertEdge(6, 0);
        std::cout << "3" << std::endl;
        graphCycle(g);
    }
    SECTION("complicated_loop")
    {
        g.insertEdge(0, 1);
        g.insertEdge(1, 2);
        g.insertEdge(2, 3);
        g.insertEdge(3, 0);
        g.insertEdge(0, 4);
        g.insertEdge(0, 5);
        g.insertEdge(2, 7);
        g.insertEdge(1, 8);
        g.insertEdge(8, 9);
        std::cout << "4" << std::endl;
        graphCycle(g);
    }
}
