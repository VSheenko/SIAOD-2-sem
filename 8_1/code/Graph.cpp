#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "Graph.h"

Graph::Graph(int verticesCount) {
    adjMatrix.resize(verticesCount, std::vector<int>(verticesCount, 0));
    this->verticesCount = verticesCount;
}

void Graph::addEdge(int start, int end, int distance) {
    if (start > 0 && start <= verticesCount && end > 0 && end <= verticesCount) {
        adjMatrix[start - 1][end - 1] = distance;
        adjMatrix[end - 1][start - 1] = distance;
    } else {
        throw std::invalid_argument("Invalid vertex index");
    }
}

void Graph::print() {
    for (int i = 0; i < verticesCount; i++) {
        for (int j = 0; j < verticesCount; j++) {
            std::cout << adjMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::cycleDfs(int start, int current, std::vector<bool>& visited, std::vector<int>& path, std::set<std::vector<int>>& uniqueCycles, int depth) {
    visited[current] = true;
    path.push_back(current);

    for (int next = 0; next < verticesCount; ++next) {
        if (adjMatrix[current][next] != 0) {
            if (!visited[next]) {
                cycleDfs(start, next, visited, path, uniqueCycles, depth + 1);
            } else if (next == start && depth >= 2) {
                // Найден простой цикл
                std::vector<int> cycle = path;
                cycle.push_back(start);
                uniqueCycles.insert(cycle);
            }
        }
    }

    visited[current] = false; // Снимаем посещение для поиска других циклов
    path.pop_back();
}

int Graph::getCountOfSimpleCycles() {
    std::set<std::vector<int>> uniqueCycles;
    std::vector<bool> visited(verticesCount, false);
    std::vector<int> path;

    for (int i = 0; i < verticesCount; ++i) {
        cycleDfs(i, i, visited, path, uniqueCycles, 0);
    }

    return uniqueCycles.size();
}

std::pair<std::vector<int>, int> Graph::shortestPath(int start, int end) {
    std::vector<int> distance(verticesCount, INT_MAX);
    std::vector<int> parent(verticesCount, -1);
    std::vector<bool> visited(verticesCount, false);

    distance[start - 1] = 0;

    for (int i = 0; i < verticesCount - 1; i++) {
        int minDistance = INT_MAX;
        int minVertex = -1;

        for (int j = 0; j < verticesCount; j++) {
            if (!visited[j] && distance[j] < minDistance) {
                minDistance = distance[j];
                minVertex = j;
            }
        }

        visited[minVertex] = true;

        for (int j = 0; j < verticesCount; j++) {
            if (!visited[j] && adjMatrix[minVertex][j] != 0 && distance[minVertex] + adjMatrix[minVertex][j] < distance[j]) {
                distance[j] = distance[minVertex] + adjMatrix[minVertex][j];
                parent[j] = minVertex;
            }
        }
    }

    std::vector<int> path;
    for (int v = end - 1; v != -1; v = parent[v]) {
        path.push_back(v + 1);
    }
    std::reverse(path.begin(), path.end());

    int pathLength = distance[end - 1];
    if (path.size() == 1 && path[0] != start) {
        return {{}, -1};
    }

    return {path, pathLength};
}
