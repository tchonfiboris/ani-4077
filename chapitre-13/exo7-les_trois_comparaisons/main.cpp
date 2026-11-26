#include <iostream>
#include <string>
#include <vector>

struct Fragment {
    int px = 0;
    long long z = 0;
    long long color = 0;
};

struct PassResult {
    std::string name;
    bool has_test = false;
    std::vector<long long> colors;
    std::vector<long long> depths;
};

static bool pass_depth(const std::string& mode, long long z, long long s) {
    if (mode == "PLUSPROCHE") {
        return z < s;
    }
    if (mode == "PLUSPROCHEOUEGAL") {
        return z <= s;
    }
    if (mode == "PLUSLOIN") {
        return z > s;
    }
    if (mode == "TOUJOURS") {
        return true;
    }
    return false; // JAMAIS
}

static PassResult simulate_mode(const std::string& mode,
                               bool has_test,
                               int N,
                               long long Z0,
                               const std::vector<Fragment>& frags) {
    PassResult res;
    res.name = mode;
    res.has_test = has_test;
    res.colors.assign(static_cast<std::size_t>(N), 0);
    res.depths.assign(static_cast<std::size_t>(N), Z0);

    for (const Fragment& f : frags) {
        if (f.px < 0 || f.px >= N) {
            continue;
        }
        std::size_t idx = static_cast<std::size_t>(f.px);
        if (!has_test) {
            res.colors[idx] = f.color;
        } else {
            if (pass_depth(mode, f.z, res.depths[idx])) {
                res.colors[idx] = f.color;
                res.depths[idx] = f.z;
            }
        }
    }

    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N = 0;
    long long Z0 = 0;
    int F = 0;
    if (!(std::cin >> N >> Z0 >> F)) {
        return 0;
    }

    std::vector<Fragment> frags;
    frags.reserve(F > 0 ? static_cast<std::size_t>(F) : 0);
    for (int i = 0; i < F; ++i) {
        Fragment f;
        std::cin >> f.px >> f.z >> f.color;
        frags.push_back(f);
    }

    const std::vector<std::pair<std::string, bool>> modes = {
        {"SANSTEST", false},
        {"PLUSPROCHE", true},
        {"PLUSPROCHEOUEGAL", true},
        {"PLUSLOIN", true},
        {"TOUJOURS", true},
        {"JAMAIS", true}
    };

    std::vector<PassResult> results;
    results.reserve(modes.size());

    for (const auto& m : modes) {
        results.push_back(simulate_mode(m.first, m.second, N, Z0, frags));
    }

    for (const PassResult& r : results) {
        std::cout << r.name << " COULEURS";
        for (long long c : r.colors) {
            std::cout << ' ' << c;
        }
        std::cout << " PROFONDEURS";
        for (long long d : r.depths) {
            std::cout << ' ' << d;
        }
        std::cout << '\n';
    }

    const PassResult& sans_test = results[0];
    std::vector<std::string> same_colors;
    std::vector<std::string> same_both;

    for (std::size_t i = 1; i < results.size(); ++i) {
        if (results[i].colors == sans_test.colors) {
            same_colors.push_back(results[i].name);
            if (results[i].depths == sans_test.depths) {
                same_both.push_back(results[i].name);
            }
        }
    }

    std::cout << "MEMES COULEURS";
    if (same_colors.empty()) {
        std::cout << " AUCUNE\n";
    } else {
        for (const std::string& name : same_colors) {
            std::cout << ' ' << name;
        }
        std::cout << '\n';
    }

    std::cout << "MEMES TAMPONS";
    if (same_both.empty()) {
        std::cout << " AUCUNE\n";
    } else {
        for (const std::string& name : same_both) {
            std::cout << ' ' << name;
        }
        std::cout << '\n';
    }

    return 0;
}