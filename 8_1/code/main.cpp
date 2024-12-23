#include <iostream>
#include "Graph.h"

int main() {
    int vertices, edges;
    std::cout << "Enter the number of vertices and edges: ";
    std::cin >> vertices >> edges;

    Graph graph(vertices);

    for (int i = 0; i < edges; i++) {
        int start, end, distance;
        std::cout << "Enter the start, end and distance of the edge: ";
        std::cin >> start >> end >> distance;
        graph.addEdge(start, end, distance);
    }

    graph.print();

    // Задача 1: Количество простых циклов
    int simpleCycles = graph.getCountOfSimpleCycles();
    std::cout << "Number of simple cycles in the graph: " << simpleCycles << std::endl;

    // Задача 2: Кратчайший путь между двумя вершинами
    int start, end;
    std::cout << "Enter start and end vertices to find shortest path: ";
    std::cin >> start >> end;

    auto [path, distance] = graph.shortestPath(start, end);
    if (path.empty()) {
        std::cout << "Path not found." << std::endl;
    } else {
        std::cout << "Shortest path: ";
        for (int v : path) {
            std::cout << v << " ";
        }
        std::cout << "with distance: " << distance << std::endl;
    }

    system("pause");
    return 0;
}
