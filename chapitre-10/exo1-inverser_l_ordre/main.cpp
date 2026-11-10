#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    int W, H, N;
    std::cin >> W >> H >> N;

    std::vector<std::string> color(H, std::string(W, '.'));
    std::vector<std::vector<int>> depth(H, std::vector<int>(W, 100));

    bool test = false;
    long long rejected = 0;
    std::string order;  // lettres dans l'ordre de leur premier RECT

    for (int i = 0; i < N; ++i) {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "TEST") {
            std::string mode;
            std::cin >> mode;
            test = (mode == "ON");
        } else if (cmd == "RECT") {
            char c;
            long long x, y, l, h;
            int z;
            std::cin >> c >> x >> y >> l >> h >> z;
            if (order.find(c) == std::string::npos) order += c;

            // On borne les boucles à la grille : ce qui sort est ignoré.
            long long x0 = std::max(0LL, x), x1 = std::min((long long)W, x + l);
            long long y0 = std::max(0LL, y), y1 = std::min((long long)H, y + h);

            for (long long py = y0; py < y1; ++py) {
                for (long long px = x0; px < x1; ++px) {
                    if (!test) {
                        color[py][px] = c;  // la profondeur ne change pas
                    } else if (z < depth[py][px]) {
                        color[py][px] = c;
                        depth[py][px] = z;
                    } else {
                        ++rejected;
                    }
                }
            }
        }
    }

    for (int r = 0; r < H; ++r) std::cout << color[r] << std::endl;

    if (order.empty()) {
        std::cout << "AUCUN" << std::endl;
    } else {
        for (char c : order) {
            long long n = 0;
            for (int r = 0; r < H; ++r)
                n += std::count(color[r].begin(), color[r].end(), c);
            std::cout << c << " " << n << std::endl;
        }
    }
    std::cout << "REJETES " << rejected << std::endl;
    return 0;
}