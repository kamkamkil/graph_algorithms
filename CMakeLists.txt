cmake_minimum_required(VERSION 3.0.0)
project(graphalg VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
include(CTest)
enable_testing()

add_library(graph INTERFACE)
target_include_directories(graph INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include/graph>
)

add_executable(testGraph test/testGraph.cpp)
target_link_libraries(testGraph graph)

add_executable(testGraphAlgorithms test/testGraphAlgorithms.cpp) 
target_link_libraries(testGraphAlgorithms graph)

add_library(przemytnicylib src/przemytnicylib.cpp)
target_link_libraries(przemytnicylib graph)

add_executable(przemytnicy src/przemytnicy.cpp)
target_link_libraries(przemytnicy przemytnicylib)

add_executable(testprzemytnicy test/testPrzemytnicy.cpp)
target_link_libraries(testprzemytnicy przemytnicylib)

add_executable(benchmarkPrzemytnicy test/benchmarkPrzemytnicy.cpp)
target_link_libraries(benchmarkPrzemytnicy przemytnicylib)

add_library(skarbonkaLib src/skarbonkaLib.cpp)
target_link_libraries(skarbonkaLib graph)

add_executable(skarbonka src/skarbonka.cpp)
target_link_libraries(skarbonka skarbonkaLib)

add_executable(testSkarbonka test/testSkarbonka.cpp)
target_link_libraries(testSkarbonka skarbonkaLib)

add_executable(benchmarkSkarbonka test/benchmarkSkarbonka.cpp)
target_link_libraries(benchmarkSkarbonka skarbonkaLib)

add_test(testGraph testGraph)
set_tests_properties(testGraph PROPERTIES LABELS standard)

add_test(testGraphAlgorithms testGraphAlgorithms)
set_tests_properties(testGraphAlgorithms PROPERTIES LABELS standard)

add_test(testprzemytnicy testprzemytnicy)
set_tests_properties(testprzemytnicy PROPERTIES LABELS standard)

add_test(testSkarbonka testSkarbonka)
set_tests_properties(testSkarbonka PROPERTIES LABELS standard)


add_test(benchmarkPrzemytnicy benchmarkPrzemytnicy)
set_tests_properties(benchmarkPrzemytnicy PROPERTIES LABELS benchmark)

add_test(benchmarkSkarbonka benchmarkSkarbonka)
set_tests_properties(benchmarkSkarbonka PROPERTIES LABELS benchmark)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
