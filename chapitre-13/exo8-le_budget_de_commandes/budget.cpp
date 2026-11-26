#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int P = 0;
    if (!(std::cin >> P)) {
        return 0;
    }

    long long total_accepted = 0;
    long long total_refused = 0;

    for (int p = 0; p < P; ++p) {
        std::string pass_name;
        long long max_draws = 0;
        int D = 0;
        std::cin >> pass_name >> max_draws >> D;

        long long accepted = 0;
        long long refused = 0;
        std::vector<std::string> refused_names;

        for (int d = 0; d < D; ++d) {
            std::string obj_name;
            long long prog = 0;
            long long tex = 0;
            std::cin >> obj_name >> prog >> tex;

            bool unlimited = (max_draws == 0);
            bool within_budget = unlimited || (accepted < max_draws);

            if (within_budget) {
                ++accepted;
            } else {
                ++refused;
                refused_names.push_back(obj_name);
            }
        }

        total_accepted += accepted;
        total_refused += refused;

        std::cout << pass_name << " ACCEPTES " << accepted << " REFUSES " << refused << '\n';
        if (refused > 0) {
            std::cout << "REFUS " << pass_name;
            for (const std::string& name : refused_names) {
                std::cout << ' ' << name;
            }
            std::cout << '\n';
        }
    }

    std::cout << "TOTAL ACCEPTES " << total_accepted << " REFUSES " << total_refused << '\n';

    return 0;
}