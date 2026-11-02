#include <algorithm>
#include <iostream>
#include <vector>

// Division entière avec arrondi vers le bas (valide pour les nombres négatifs)
long long floorDiv(long long a, long long b) {
    long long q = a / b;
    if ((a % b != 0) && ((a < 0) != (b < 0))) {
        --q;
    }
    return q;
}

long long borne(long long i, long long dernier) {
    return std::max(0LL, std::min(i, dernier));
}

int main() {
    long long L, H, Q;
    std::cin >> L >> H >> Q;

    // tex[j][i] : la première ligne lue est la ligne du bas (j = 0)
    std::vector<std::vector<long long>> tex(H, std::vector<long long>(L));
    for (long long j = 0; j < H; ++j) {
        for (long long i = 0; i < L; ++i) {
            std::cin >> tex[j][i];
        }
    }

    long long surs = 0, frontieres = 0;

    for (long long k = 0; k < Q; ++k) {
        long long u, v;
        std::cin >> u >> v;

        // Au plus proche
        long long i = borne(floorDiv(u * L, 1000), L - 1);
        long long j = borne(floorDiv(v * H, 1000), H - 1);
        long long a = tex[j][i];

        // Linéaire, en entiers : X = x en deux-millièmes de texel
        long long X = 2 * u * L - 1000;
        long long Y = 2 * v * H - 1000;
        long long i0 = floorDiv(X, 2000);
        long long j0 = floorDiv(Y, 2000);
        long long fx = X - i0 * 2000;  // dans [0, 2000)
        long long fy = Y - j0 * 2000;

        long long ia = borne(i0, L - 1), ib = borne(i0 + 1, L - 1);
        long long ja = borne(j0, H - 1), jb = borne(j0 + 1, H - 1);

        long long somme =
              (2000 - fx) * (2000 - fy) * tex[ja][ia]
            + fx * (2000 - fy) * tex[ja][ib]
            + (2000 - fx) * fy * tex[jb][ia]
            + fx * fy * tex[jb][ib];

        const long long D = 4000000;  // dénominateur des poids
        // Arrondi au plus proche, moitié exacte vers le haut
        long long b = floorDiv(2 * somme + D, 2 * D);

        bool sur = (a == b);
        if (sur) ++surs; else ++frontieres;

        std::cout << u << " " << v << " PROCHE " << a << " LINEAIRE " << b
                  << (sur ? " SUR" : " FRONTIERE") << std::endl;
    }

    std::cout << "SURS " << surs << std::endl;
    std::cout << "FRONTIERES " << frontieres << std::endl;

    return 0;
}