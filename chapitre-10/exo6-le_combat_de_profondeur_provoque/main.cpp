#include <iostream>

int main() {
    int b, N;
    std::cin >> b >> N;

    // M = 2^b - 1
    long long M = (1LL << b) - 1;

    int erreurs = 0;

    for (int k = 1; k <= N; ++k) {
        long long z1, z2;
        std::cin >> z1 >> z2;

        // Arrondi à l'entier le plus proche, moitié vers le haut, en entiers.
        long long d1 = (2 * (z1 + 1000000) * M + 2000000) / 4000000;
        long long d2 = (2 * (z2 + 1000000) * M + 2000000) / 4000000;

        // La première surface est déjà là : la seconde passe si d2 < d1, strictement.
        int gagnant = (d2 < d1) ? 2 : 1;

        // Le bon gagnant est la surface au plus petit z ; égalité de z : toujours OK.
        bool ok;
        if (z1 == z2) ok = true;
        else ok = (gagnant == (z1 < z2 ? 1 : 2));

        if (!ok) ++erreurs;

        std::cout << "PAIRE " << k << " " << d1 << " " << d2
                  << " GAGNANT " << gagnant << " " << (ok ? "OK" : "ERREUR") << std::endl;
    }

    // Plus petit écart entier qui donne toujours deux entiers différents : 2000000 / M, vers le haut.
    long long separation = (2000000 + M - 1) / M;

    std::cout << "ERREURS " << erreurs << std::endl;
    std::cout << "SEPARATION SURE " << separation << std::endl;
    return 0;
}