#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct OffscreenTarget {
    std::string name;
    long long width = 0;
    long long height = 0;
    int id = 0;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int C = 0;
    if (!(std::cin >> C)) {
        return 0;
    }

    std::vector<OffscreenTarget> targets;
    targets.reserve(C > 0 ? static_cast<std::size_t>(C) : 0);
    std::unordered_map<std::string, int> target_index;
    target_index.reserve(static_cast<std::size_t>(C) * 2 + 1);

    for (int i = 0; i < C; ++i) {
        OffscreenTarget t;
        std::cin >> t.name >> t.width >> t.height;
        t.id = i + 1;
        target_index[t.name] = i;
        targets.push_back(t);
    }

    int P = 0;
    if (!(std::cin >> P)) {
        P = 0;
    }

    long long cache_target = 0;
    long long cache_prog = 0;
    long long cache_tex = 0;
    long long cache_vao = 0;

    long long total_draws = 0;
    long long total_requested = 0;
    long long total_emitted = 0;

    for (int k = 1; k <= P; ++k) {
        std::string dest;
        long long pass_w = 0;
        long long pass_h = 0;
        int ec = 0;
        int ep = 0;
        int D = 0;
        std::cin >> dest >> pass_w >> pass_h >> ec >> ep >> D;

        std::vector<std::pair<long long, long long>> draws;
        draws.reserve(D > 0 ? static_cast<std::size_t>(D) : 0);
        for (int d = 0; d < D; ++d) {
            long long prog = 0;
            long long tex = 0;
            std::cin >> prog >> tex;
            draws.emplace_back(prog, tex);
        }

        bool is_window = (dest == "FENETRE");
        auto it = target_index.find(dest);
        bool is_valid_target = is_window || (it != target_index.end());

        if (!is_valid_target) {
            std::cout << "PASSE " << k << ' ' << dest << " IGNOREE\n";
            continue;
        }

        long long vp_w = is_window ? pass_w : targets[it->second].width;
        long long vp_h = is_window ? pass_h : targets[it->second].height;

        std::cout << "PASSE " << k << ' ' << dest
                  << " VIEWPORT " << vp_w << ' ' << vp_h
                  << " EFFACE ";

        if (ec == 1 && ep == 1) {
            std::cout << "COULEUR PROFONDEUR\n";
        } else if (ec == 1) {
            std::cout << "COULEUR\n";
        } else if (ep == 1) {
            std::cout << "PROFONDEUR\n";
        } else {
            std::cout << "RIEN\n";
        }

        // Liaison de cible pour la passe
        ++total_requested;
        if (is_window) {
            if (cache_target != 0) {
                ++total_emitted;
                cache_target = 0;
            }
        } else {
            ++total_emitted;
            cache_target = targets[it->second].id;
        }

        // Dessins de la passe
        for (const auto& draw : draws) {
            ++total_draws;
            const long long prog = draw.first;
            const long long tex = draw.second;
            const long long vao = 1;

            total_requested += 3;

            if (cache_prog != prog) {
                ++total_emitted;
                cache_prog = prog;
            }
            if (cache_tex != tex) {
                ++total_emitted;
                cache_tex = tex;
            }
            if (cache_vao != vao) {
                ++total_emitted;
                cache_vao = vao;
            }
        }
    }

    std::cout << "DESSINS " << total_draws << '\n';
    std::cout << "DEMANDEES " << total_requested << '\n';
    std::cout << "EMISES " << total_emitted << '\n';

    return 0;
}