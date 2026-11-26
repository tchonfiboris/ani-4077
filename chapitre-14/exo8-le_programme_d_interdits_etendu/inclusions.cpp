#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int F = 0;
    if (!(std::cin >> F)) {
        return 0;
    }

    std::unordered_map<std::string, std::vector<std::string>> adj;
    adj.reserve(static_cast<std::size_t>(F) * 2 + 1);

    for (int i = 0; i < F; ++i) {
        std::string kw, name;
        int K = 0;
        std::cin >> kw >> name >> K;

        std::vector<std::string> incs;
        incs.reserve(K > 0 ? static_cast<std::size_t>(K) : 0);
        for (int j = 0; j < K; ++j) {
            std::string inc;
            std::cin >> inc;
            incs.push_back(inc);
        }
        adj[name] = std::move(incs);
    }

    std::string rule_kw, target_file;
    int n = 0;
    std::cin >> rule_kw >> target_file >> n;

    std::vector<std::string> forbidden(n > 0 ? static_cast<std::size_t>(n) : 0);
    for (int i = 0; i < n; ++i) {
        std::cin >> forbidden[static_cast<std::size_t>(i)];
    }

    std::unordered_set<std::string> direct_set;
    auto direct_it = adj.find(target_file);
    if (direct_it != adj.end()) {
        for (const std::string& inc : direct_it->second) {
            direct_set.insert(inc);
        }
    }

    std::unordered_map<std::string, std::string> parent;
    std::unordered_set<std::string> visited;
    std::queue<std::string> q;

    visited.insert(target_file);
    q.push(target_file);

    while (!q.empty()) {
        std::string u = q.front();
        q.pop();

        auto it = adj.find(u);
        if (it == adj.end()) {
            continue;
        }

        for (const std::string& v : it->second) {
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                parent[v] = u;
                q.push(v);
            }
        }
    }

    long long direct_count = 0;
    long long hidden_count = 0;

    for (const std::string& h : forbidden) {
        if (direct_set.find(h) != direct_set.end()) {
            std::cout << "DIRECT " << h << '\n';
            ++direct_count;
        } else if (visited.find(h) != visited.end()) {
            std::vector<std::string> chain;
            std::string cur = h;
            while (cur != target_file) {
                chain.push_back(cur);
                cur = parent[cur];
            }
            std::reverse(chain.begin(), chain.end());

            std::cout << "CACHEE " << h << " PAR ";
            for (std::size_t idx = 0; idx < chain.size(); ++idx) {
                if (idx > 0) {
                    std::cout << " > ";
                }
                std::cout << chain[idx];
            }
            std::cout << '\n';
            ++hidden_count;
        }
    }

    std::cout << "DIRECTES " << direct_count << '\n';
    std::cout << "CACHEES " << hidden_count << '\n';
    std::cout << "VERDICT " << ((direct_count + hidden_count) > 0 ? "REFUSE\n" : "PROPRE\n");

    return 0;
}