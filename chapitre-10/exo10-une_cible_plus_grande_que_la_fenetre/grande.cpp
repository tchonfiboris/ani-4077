#include <algorithm>
#include <iostream>

int main() {
    long long W, H, L, M, C, D, F;
    std::cin >> W >> H >> L >> M >> C >> D >> F;

    long long n = L * M;  // pixels de la cible
    long long m = W * H;  // pixels de la zone d'affichage

    std::cout << "CIBLE PIXELS " << n << std::endl;
    std::cout << "FENETRE PIXELS " << m << std::endl;
    // Division entière ; on évite la division par zéro si la zone est vide.
    std::cout << "RAPPORT " << (m > 0 ? n * 100 / m : 0) << std::endl;

    long long couleur = n * C;
    long long profondeur = n * D;
    std::cout << "MEMOIRE COULEUR " << couleur << std::endl;
    std::cout << "MEMOIRE PROFONDEUR " << profondeur << std::endl;
    std::cout << "MEMOIRE TOTALE " << couleur + profondeur << std::endl;
    std::cout << "FRAGMENTS PAR SECONDE " << n * F << std::endl;

    // Lecture bilinéaire, sans mipmaps : 4 texels lus par pixel de la zone.
    long long lus = 4 * m;
    std::cout << "TEXELS LUS " << lus << std::endl;
    std::cout << "TEXELS IGNORES " << std::max(0LL, n - lus) << std::endl;

    if (n > m) std::cout << "SENS REDUCTION" << std::endl;
    else if (n < m) std::cout << "SENS AGRANDISSEMENT" << std::endl;
    else std::cout << "SENS EGAL" << std::endl;
    return 0;
}
