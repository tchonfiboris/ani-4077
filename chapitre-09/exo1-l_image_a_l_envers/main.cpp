#include <iostream>
#include <string>
#include <vector>

// Division entière avec arrondi vers le bas (valide pour les nombres négatifs)
long long floorDiv (long long a, long long b) {
    long long q = a / b;
    if ((a % b != 0) && ((a < 0) != (b < 0))) {
        --q;
    }
    return q;
}

// Reste toujours positif ou nul
long long posMod(long long a, long long b) {
    long long r = a % b;
    if (r < 0) r += b;
    return r;
}

int main() {
    long long L, H, Q;
    int C, N;
    std::string mode;
    std::cin >> L >> H >> C >> N >> mode >> Q;

    std::vector<std::string> fichier(H);
    for (long long i = 0; i < H; ++i) {
        std::cin >> fichier[i];
    }

    // Lignes dans l'ordre où OpenGL les reçoit : la première reçue est la ligne 0
    std::vector<std::string> gl(H);
    for (long long i = 0; i < H; ++i) {
        gl[i] = (C == 1) ? fichier[H - 1 - i] : fichier[i];
    }

    bool repeat = (mode == "GL_REPEAT");

    for (long long k = 0; k < Q; ++k) {
        long long u, v;
        std::cin >> u >> v;

        long long vv = (N == 1) ? 1000 - v : v;

        long long col = floorDiv(u * L, 1000);
        long long row = floorDiv(vv * H, 1000);

        if (repeat) {
            col = posMod(col, L);
            row = posMod(row, H);
        } else {
            if (col < 0) col = 0;
            if (col > L - 1) col = L - 1;
            if (row < 0) row = 0;
            if (row > H - 1) row = H - 1;
        }

        std::cout << u << " " << v << " " << gl[row][col] << std::endl;
    }

    int corrections = C + N;
    std::cout << "CORRECTIONS " << corrections << std::endl;
    std::cout << (corrections == 1 ? "IMAGE DROITE" : "IMAGE RETOURNEE") << std::endl;

    return 0;
}