#include <iostream>
#include <vector>

void greedyColoring(const std::vector<std::vector<int>>& graph, int V) {
    std::vector<int> result(V, -1);
    result[0] = 0;

    std::vector<bool> available(V, false);

    for (int u = 1; u < V; ++u) {
        for (int i : graph[u]) {
            if (result[i] != -1) {
                available[result[i]] = true;
            }
        }

        int cr;
        for (cr = 0; cr < V; ++cr) {
            if (!available[cr]) {
                break;
            }
        }

        result[u] = cr;

        for (int i : graph[u]) {
            if (result[i] != -1) {
                available[result[i]] = false;
            }
        }
    }

    for (int u = 0; u < V; ++u) {
        std::cout << "Vertex " << u + 1 << " ---> Color " << result[u] << std::endl;
    }
}

int main() {
    int V = 8;
    std::vector<std::vector<int>> graph(V);

    graph[0] = {1, 2};
    graph[1] = {0, 2, 4, 7};
    graph[2] = {0, 1, 3};
    graph[3] = {2, 5};
    graph[4] = {1, 5, 6};
    graph[5] = {3, 5, 6};
    graph[6] = {4, 5, 7};
    graph[7] = {1, 6};

    greedyColoring(graph, V);

    return 0;
}