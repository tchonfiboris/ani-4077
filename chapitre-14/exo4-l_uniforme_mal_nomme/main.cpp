#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long cx = 0;
    long long cy = 0;
    long long z = 1;
    if (!(std::cin >> cx >> cy >> z)) {
        return 0;
    }

    int N = 0;
    if (!(std::cin >> N)) {
        N = 0;
    }

    long long justes = 0;
    long long oubliees = 0;
    long long abimees = 0;

    for (int i = 0; i < N; ++i) {
        std::string name;
        int c = 0;
        std::cin >> name >> c;

        std::vector<long long> vals(c > 0 ? static_cast<std::size_t>(c) : 0, 0);
        for (int j = 0; j < c; ++j) {
            std::cin >> vals[j];
        }

        std::string sens;
        std::cin >> sens;

        std::vector<long long> expected = vals;
        if (c == 2) {
            if (sens == "POSITION") {
                expected[0] = (vals[0] - cx) * z;
                expected[1] = (vals[1] - cy) * z;
            } else if (sens == "TAILLE") {
                expected[0] = vals[0] * z;
                expected[1] = vals[1] * z;
            }
        }

        std::vector<long long> rhi_vals = vals;
        bool applied_formula = false;
        if (c == 2) {
            if (name == "uDecalage") {
                rhi_vals[0] = (vals[0] - cx) * z;
                rhi_vals[1] = (vals[1] - cy) * z;
                applied_formula = true;
            } else if (name == "uEchelle") {
                rhi_vals[0] = vals[0] * z;
                rhi_vals[1] = vals[1] * z;
                applied_formula = true;
            }
        }

        bool is_exact = (rhi_vals == expected);
        std::string status;
        if (is_exact) {
            status = "JUSTE";
            ++justes;
        } else if (applied_formula) {
            status = "ABIMEE";
            ++abimees;
        } else {
            status = "OUBLIEE";
            ++oubliees;
        }

        std::cout << name;
        for (long long v : rhi_vals) {
            std::cout << ' ' << v;
        }
        std::cout << ' ' << status << '\n';
    }

    std::cout << "JUSTES " << justes << '\n';
    std::cout << "OUBLIEES " << oubliees << '\n';
    std::cout << "ABIMEES " << abimees << '\n';

    return 0;
}