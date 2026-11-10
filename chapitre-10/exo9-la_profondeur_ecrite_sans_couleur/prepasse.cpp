#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Objet {
    char c;
    long long x, y, l, h;
    int z;
};

int main() {
    int W, H, N;
    long long F, P, S;
    std::cin >> W >> H >> N >> F >> P >> S;

    std::vector<Objet> objets(N);
    for (auto& o : objets) std::cin >> o.c >> o.x >> o.y >> o.l >> o.h >> o.z;

    // Les pixels couverts par un objet, une fois coupés à la grille
    // (ce qui sort de la grille est ignoré).
    auto bornes = [&](const Objet& o, long long& x0, long long& x1, long long& y0, long long& y1) {
        x0 = std::max(0LL, o.x);
        x1 = std::min((long long)W, o.x + o.l);
        y0 = std::max(0LL, o.y);
        y1 = std::min((long long)H, o.y + o.h);
    };

    // --- Sans pré-passe : une passe en GL_LESS, profondeur neuve à 100. ---
    std::vector<int> prof0(W * H, 100);
    long long a = 0;  // fragments qui passent
    for (const auto& o : objets) {
        long long x0, x1, y0, y1;
        bornes(o, x0, x1, y0, y1);
        for (long long py = y0; py < y1; ++py)
            for (long long px = x0; px < x1; ++px) {
                int& d = prof0[py * W + px];
                if (o.z < d) {
                    ++a;
                    d = o.z;
                }
            }
    }
    long long x = N * S + a * F;

    // --- Passe 1 : GL_LESS, la couleur est masquée, seule la profondeur s'écrit. ---
    std::vector<int> prof1(W * H, 100);
    long long b = 0;  // fragments testés pendant la passe 1
    for (const auto& o : objets) {
        long long x0, x1, y0, y1;
        bornes(o, x0, x1, y0, y1);
        for (long long py = y0; py < y1; ++py)
            for (long long px = x0; px < x1; ++px) {
                ++b;
                int& d = prof1[py * W + px];
                if (o.z < d) d = o.z;
            }
    }

    // --- Passe 2 : tout est redessiné en GL_LEQUAL, la profondeur ne change plus. ---
    long long c = 0;  // fragments qui passent en GL_LEQUAL : le nuanceur travaille
    long long dless = 0;  // ceux qui passeraient en GL_LESS
    for (const auto& o : objets) {
        long long x0, x1, y0, y1;
        bornes(o, x0, x1, y0, y1);
        for (long long py = y0; py < y1; ++py)
            for (long long px = x0; px < x1; ++px) {
                int d = prof1[py * W + px];
                if (o.z <= d) ++c;
                if (o.z < d) ++dless;
            }
    }

    long long y = 2 * N * S + b * P + c * F;

    std::cout << "SANS NUANCEUR " << a << " COUT " << x << std::endl;
    std::cout << "AVEC PROFONDEUR " << b << " NUANCEUR " << c << " COUT " << y << std::endl;
    std::cout << "PASSE 2 EN LESS NUANCEUR " << dless << std::endl;
    std::cout << "GAGNE " << x - y << std::endl;
    std::cout << (y < x ? "VERDICT PREPASSE" : "VERDICT UNE PASSE") << std::endl;
    return 0;
}
