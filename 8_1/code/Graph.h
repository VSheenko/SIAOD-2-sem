#ifndef CODE_GRAPH_H
#define CODE_GRAPH_H

#include <vector>
#include <set>

class Graph {
private:
    int verticesCount;
    std::vector<std::vector<int>> adjMatrix;

    void cycleDfs(int start, int current, std::vector<bool>& visited, std::vector<int>& path, std::set<std::vector<int>>& uniqueCycles, int depth);
public:
    explicit Graph(int verticesCount);
    void addEdge(int start, int end, int distance);

    int getCountOfSimpleCycles();
    std::pair<std::vector<int>, int> shortestPath(int start, int end);
    void print();

    ~Graph() = default;
};


#endif //CODE_GRAPH_H
