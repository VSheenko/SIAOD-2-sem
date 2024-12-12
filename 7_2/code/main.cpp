#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>


std::pair<int, std::vector<int>> minimizeRisk(const std::vector<int>& risks, int K) {
    int N = (int)risks.size();

    std::vector<int> dp(N + 1, std::numeric_limits<int>::max());
    std::vector<int> prev(N + 1, -1);

    dp[1] = risks[0];

    for (int i = 1; i <= N; ++i) {
        for (int jump = 1; jump <= K; ++jump) {
            if (i + jump <= N) {
                int newRisk = dp[i] + risks[i + jump - 1];
                if (newRisk < dp[i + jump]) {
                    dp[i + jump] = newRisk;
                    prev[i + jump] = i;
                }
            }
        }
    }

    // Восстановление пути
    std::vector<int> path;
    for (int i = N; i != -1; i = prev[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());

    return {dp[N], path};
}

int main() {

    int k = 3;
    std::vector<int> risks = {5,2,8,6,3,7,2,4,6,1};

    auto [minRisk, path] = minimizeRisk(risks, k);

    std::cout << "Minimal risk: " << minRisk << std::endl;
    std::cout << "Optimal path: ";
    for (int pos : path) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;

    return 0;
}
