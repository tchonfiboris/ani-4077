#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

struct FileNode {
    std::string name;
    int g = 0;
    int door = 0;
    std::vector<std::string> includes;
    std::vector<int> adj;
};

static bool has_h_suffix(const std::string& name, std::string& stem) {
    if (name.size() >= 2 && name.compare(name.size() - 2, 2, ".h") == 0) {
        stem.assign(name.begin(), name.end() - 2);
        return true;
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int F = 0;
    if (!(std::cin >> F)) {
        return 0;
    }

    std::vector<FileNode> files(F);
    std::unordered_map<std::string, int> index_of;
    index_of.reserve(static_cast<std::size_t>(F) * 2);

    for (int i = 0; i < F; ++i) {
        int k = 0;
        std::cin >> files[i].name >> files[i].g >> files[i].door >> k;
        files[i].includes.resize(k);
        for (int j = 0; j < k; ++j) {
            std::cin >> files[i].includes[j];
        }
        index_of[files[i].name] = i;
    }

    for (int i = 0; i < F; ++i) {
        for (const std::string& inc : files[i].includes) {
            auto it = index_of.find(inc);
            if (it != index_of.end()) {
                files[i].adj.push_back(it->second);
            }
        }

        std::string stem;
        if (has_h_suffix(files[i].name, stem)) {
            auto cpp_it = index_of.find(stem + ".cpp");
            if (cpp_it != index_of.end()) {
                files[i].adj.push_back(cpp_it->second);
            }
        }
    }

    int leaks = 0;
    int free_count = 0;

    for (int start = 0; start < F; ++start) {
        if (files[start].door == 1) {
            std::cout << files[start].name << " PORTE\n";
            continue;
        }
        if (files[start].g > 0) {
            std::cout << files[start].name << " PARLE " << files[start].g << '\n';
            continue;
        }

        std::vector<bool> visited(F, false);
        std::queue<int> q;
        visited[start] = true;
        q.push(start);

        int dist = 0;
        int best_target = -1;

        while (!q.empty() && best_target == -1) {
            ++dist;
            const std::size_t level_size = q.size();

            for (std::size_t s = 0; s < level_size; ++s) {
                int u = q.front();
                q.pop();

                for (int v : files[u].adj) {
                    if (visited[v] || files[v].door == 1) {
                        continue;
                    }
                    visited[v] = true;

                    if (files[v].g > 0) {
                        if (best_target == -1 || v < best_target) {
                            best_target = v;
                        }
                    } else {
                        q.push(v);
                    }
                }
            }
        }

        if (best_target != -1) {
            std::cout << files[start].name << " FUITE " << dist << ' ' << files[best_target].name << '\n';
            ++leaks;
        } else {
            std::cout << files[start].name << " LIBRE\n";
            ++free_count;
        }
    }

    std::cout << "FUITES " << leaks << '\n';
    std::cout << "LIBRES " << free_count << '\n';

    return 0;
}