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

add_executable(przemytnicy src/przemytnicy.cpp)
target_link_libraries(przemytnicy graph)


add_test(testGraph testGraph)
add_test(testGraphAlgorithms testGraphAlgorithms)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
