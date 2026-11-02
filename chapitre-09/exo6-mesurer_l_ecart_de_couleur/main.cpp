#include <cmath>
#include <iostream>

// Décodage sRGB -> linéaire, puis arrondi au plus proche sur 0..255
int decode(int octet) {
    double x = octet / 255.0;
    double lineaire;
    if (x <= 0.04045) {
        lineaire = x / 12.92;
    } else {
        lineaire = std::pow((x + 0.055) / 1.055, 2.4);
    }
    return static_cast<int>(std::floor(lineaire * 255.0 + 0.5));
}

int main() {
    int N;
    std::cin >> N;

    long long somme[3] = {0, 0, 0};

    for (int i = 0; i < N; ++i) {
        int lu[3], ecrit[3], ecart[3];
        std::cin >> lu[0] >> lu[1] >> lu[2];

        for (int c = 0; c < 3; ++c) {
            ecrit[c] = decode(lu[c]);
            ecart[c] = ecrit[c] - lu[c];
            somme[c] += ecart[c];
        }

        std::cout << "LU " << lu[0] << " " << lu[1] << " " << lu[2]
                  << " ECRIT " << ecrit[0] << " " << ecrit[1] << " " << ecrit[2]
                  << " ECART " << ecart[0] << " " << ecart[1] << " " << ecart[2]
                  << std::endl;
    }

    std::cout << "ECART TOTAL " << somme[0] << " " << somme[1] << " " << somme[2] << std::endl;

    const char* noms[3] = {"ROUGE", "VERT", "BLEU"};
    int pire = 0;
    for (int c = 1; c < 3; ++c) {
        if (somme[c] < somme[pire]) {  // strict : égalité -> première composante
            pire = c;
        }
    }

    if (somme[pire] == 0) {
        std::cout << "PLUS TOUCHEE AUCUNE" << std::endl;
    } else {
        std::cout << "PLUS TOUCHEE " << noms[pire] << std::endl;
    }

    return 0;
}