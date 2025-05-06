#ifndef GRAPH_H
#define GRAPH_H
#include <ctime>
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <set>

class NonDiGraph {
private:
    int vertices;
    std::vector<std::vector<int>> adjacencyMatrix;

public:
    NonDiGraph(int numVertices) : vertices(numVertices) {
        adjacencyMatrix.resize(vertices, std::vector<int>(vertices, 0));
    }

    bool hasEdge(int vertex1, int vertex2) const {
        return adjacencyMatrix[vertex1][vertex2] != 0 || adjacencyMatrix[vertex2][vertex1] != 0;
    }

    const std::vector<int>& getNeighbors(int vertex) const {
        return adjacencyMatrix[vertex];
    }

    bool isConnected() const {
        // Implementation for checking connectivity, you might have your own logic
        // This is a simple implementation assuming connectivity if there is an edge between any pair of vertices
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (i != j && hasEdge(i, j)) {
                    return true;
                }
            }
        }
        return false;
    }

    void setVertices(int numVertices) {
        vertices = numVertices;
        adjacencyMatrix.resize(vertices, std::vector<int>(vertices, 0));
    }
    void findMinimumSpanningTree() const {
        std::vector<bool> visited(vertices, false);
        std::vector<int> minWeight(vertices, INT_MAX);
        std::vector<int> parent(vertices, -1);

        minWeight[0] = 0;

        for (int i = 0; i < vertices - 1; ++i) {
            int minVertex = -1;
            for (int j = 0; j < vertices; ++j) {
                if (!visited[j] && (minVertex == -1 || minWeight[j] < minWeight[minVertex])) {
                    minVertex = j;
                }
            }

            visited[minVertex] = true;

            for (int k = 0; k < vertices; ++k) {
                if (adjacencyMatrix[minVertex][k] != 0 && !visited[k] && adjacencyMatrix[minVertex][k] < minWeight[k]) {
                    parent[k] = minVertex;
                    minWeight[k] = adjacencyMatrix[minVertex][k];
                }
            }
        }

        std::cout << "Minimum spanning tree:" << std::endl;
        for (int i = 1; i < vertices; ++i) {
            std::cout << "Edge " << parent[i] << " - " << i << "  Weight: " << minWeight[i] << std::endl;
        }
    }

    void findShortestPathWithMaxCapacity(int start, int end) const {
        std::vector<int> maxCapacity(vertices, INT_MIN);
        std::vector<bool> visited(vertices, false);

        maxCapacity[start] = INT_MAX;  // Начальная пропускная способность

        for (int i = 0; i < vertices - 1; ++i) {
            int maxVertex = findMaxCapacityVertex(maxCapacity, visited);
            visited[maxVertex] = true;

            for (int j = 0; j < vertices; ++j) {
                if (!visited[j] && adjacencyMatrix[maxVertex][j] != 0) {
                    int capacity = std::min(maxCapacity[maxVertex], adjacencyMatrix[maxVertex][j]);
                    if (capacity > maxCapacity[j]) {
                        maxCapacity[j] = capacity;
                    }
                }
            }
        }

        // Выводим наилучший путь с наибольшей пропускной способностью
        std::cout << "Shortest Path with Max Capacity from " << start << " to " << end << ": " << maxCapacity[end] << std::endl;
    }

    void addEdge(int from, int to, int weight) {
        if (from >= 0 && from < vertices && to >= 0 && to < vertices) {
            adjacencyMatrix[from][to] = weight;
            adjacencyMatrix[to][from] = weight;  // For a non-directed graph, add the reverse edge
        }
        else {
            //            std::cerr << "Error: Incorrect vertices!" << std::endl;
            ;
        }
    }

    int getVerticesCount() const {
        return vertices;
    }

    void printGraph() const {
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                std::cout << adjacencyMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Метод для случайной генерации рёбер неориентированного графа
    void generateRandomGraph(int numVertices, int numEdges, int maxWeight) {
        if (numEdges > numVertices * (numVertices - 1) / 2) {
            std::cerr << "Error: Too many edges for given number of vertices!" << std::endl;
            return;
        }

        srand(static_cast<unsigned int>(time(nullptr)));  // Seed the random number generator

        int count = 0;
        while (count < numEdges) {
            int vertex1 = rand() % numVertices;
            int vertex2 = rand() % numVertices;

            if (vertex1 != vertex2 && !hasEdge(vertex1, vertex2)) {
                int weight = rand() % maxWeight + 1;  // Weight from 1 to maxWeight
                addEdge(vertex1, vertex2, weight);
                count++;
            }
        }
    }

    void findConnectedComponents() const {
        std::vector<bool> visited(vertices, false);
        int component = 0;

        for (int i = 0; i < vertices; ++i) {
            if (!visited[i]) {
                std::cout << "Connected Component " << component << ": ";
                dfs(i, visited);
                std::cout << std::endl;
                component++;
            }
        }
    }

    void findPathsWithTotalCapacity(int start, int end, int requiredCapacity) const {
        std::vector<int> currentPath;
        std::vector<std::vector<int>> allPaths;
        std::vector<bool> visited(vertices, false);

        findPathsDFS(start, end, requiredCapacity, currentPath, allPaths, visited);

        // Вывод всех найденных путей
        std::cout << "Paths with Total Capacity from " << start << " to " << end << " (" << requiredCapacity << "):" << std::endl;
        for (const auto& path : allPaths) {
            std::cout << "Path: ";
            for (int vertex : path) {
                std::cout << vertex << " ";
            }
            std::cout << std::endl;
        }
    }

    int getEdgesCount() const {
        int count = 0;
        for (int i = 0; i < vertices; ++i) {
            for (int j = i + 1; j < vertices; ++j) {
                if (adjacencyMatrix[i][j] != 0 || adjacencyMatrix[j][i] != 0) {
                    ++count;
                }
            }
        }
        return count;
    }


private:


    int findMaxCapacityVertex(const std::vector<int>& maxCapacity, const std::vector<bool>& visited) const {
        int maxVertex = -1;
        int maxCapacityValue = INT_MIN;

        for (int i = 0; i < vertices; ++i) {
            if (!visited[i] && maxCapacity[i] > maxCapacityValue) {
                maxCapacityValue = maxCapacity[i];
                maxVertex = i;
            }
        }

        return maxVertex;
    }

    void dfs(int vertex, std::vector<bool>& visited) const {
        visited[vertex] = true;
        std::cout << vertex << " ";

        for (int i = 0; i < vertices; ++i) {
            if (adjacencyMatrix[vertex][i] != 0 && !visited[i]) {
                dfs(i, visited);
            }
        }
    }

    void findPathsDFS(int current, int end, int requiredCapacity, std::vector<int>& currentPath, std::vector<std::vector<int>>& allPaths, std::vector<bool>& visited) const {
        currentPath.push_back(current);

        if (current == end && calculatePathCapacity(currentPath) >= requiredCapacity) {
            allPaths.push_back(currentPath);
        }
        else {
            for (int i = 0; i < vertices; ++i) {
                if (adjacencyMatrix[current][i] != 0 && std::find(currentPath.begin(), currentPath.end(), i) == currentPath.end()) {
                    findPathsDFS(i, end, requiredCapacity, currentPath, allPaths, visited);
                }
            }
        }

        currentPath.pop_back();
    }

    int calculatePathCapacity(const std::vector<int>& path) const {
        int capacity = INT_MAX;
        for (size_t i = 0; i < path.size() - 1; ++i) {
            capacity = std::min(capacity, adjacencyMatrix[path[i]][path[i + 1]]);
        }
        return capacity;
    }
};
#endif //LAB4_GRAF_NONDIGRAPH_H