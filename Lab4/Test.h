#ifndef TEST_H
#define TEST_H
#include "graph.h"
#include <iostream>
#include <cassert>

template <typename T>
bool test_non_directed_graph_default_constructor() {
    NonDiGraph graph(5);
    assert(graph.getVerticesCount() == 5);
    assert(graph.getEdgesCount() == 0);

    std::cout << "Test passed: test_non_directed_graph_default_constructor\n";
    return true;
}

template <typename T>
bool test_non_directed_graph_add_edge() {
    NonDiGraph graph(3);
    graph.addEdge(0, 1, 2);
    graph.addEdge(1, 2, 3);
    assert(graph.getEdgesCount() == 2);

    std::cout << "Test passed: test_non_directed_graph_add_edge\n";
    return true;
}

template <typename T>
bool test_non_directed_graph_find_connected_components() {
    NonDiGraph graph(5);
    graph.addEdge(0, 1, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 4, 1);

    graph.findConnectedComponents();

    // Add your assertions based on the expected connected components

    std::cout << "Test passed: test_non_directed_graph_find_connected_components\n";
    return true;
}

template <typename T>
bool test_non_directed_graph_find_path_with_total_capacity() {
    NonDiGraph graph(4);
    graph.addEdge(0, 1, 2);
    graph.addEdge(1, 3, 4);
    graph.addEdge(0, 2, 1);

    graph.findPathsWithTotalCapacity(0, 3, 5);

    // Add your assertions based on the expected paths

    std::cout << "Test passed: test_non_directed_graph_find_path_with_total_capacity\n";
    return true;
}

void test_non_directed_graph() {
    int total_tests = 4;
    int passed_tests = test_non_directed_graph_default_constructor<int>() +
        test_non_directed_graph_add_edge<int>() +
        test_non_directed_graph_find_connected_components<int>() +
        test_non_directed_graph_find_path_with_total_capacity<int>();

    int failed_tests = total_tests - passed_tests;
    std::cout << "_____________________________________________________________\n";
    std::cout << "Total NonDiGraph tests: " << total_tests << ", Passed: " << passed_tests << ", Failed: " << failed_tests << std::endl;
    std::cout << "_____________________________________________________________\n";
}
#endif 
