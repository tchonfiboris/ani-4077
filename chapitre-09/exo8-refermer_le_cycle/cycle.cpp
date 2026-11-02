#include <cmath>
#include <cstdlib>
#include <iostream>

// Octet sRGB -> valeur linéaire
double versLineaire(int c) {
    double x = c / 255.0;
    if (x <= 0.04045) {
        return x / 12.92;
    }
    return std::pow((x + 0.055) / 1.055, 2.4);
}

int enOctet(double v) {
    return static_cast<int>(std::floor(v * 255.0 + 0.5));
}

int main() {
    int N;
    std::cin >> N;

    int identiques = 0;
    int ecartMax = 0;
    int octetMax = 0;
    bool premier = true;

    for (int i = 0; i < N; ++i) {
        int c;
        std::cin >> c;

        double l = versLineaire(c);

        // Cycle ouvert : la valeur linéaire part telle quelle à l'écran
        int d = enOctet(l);
        // Cycle refermé par l'approximation 1/2,2
        int g = enOctet(std::pow(l, 1.0 / 2.2));
        // Cycle refermé par la vraie courbe inverse
        double v;
        if (l <= 0.0031308) {
            v = l * 12.92;
        } else {
            v = 1.055 * std::pow(l, 1.0 / 2.4) - 0.055;
        }
        int e = enOctet(v);

        int x = g - c;
        if (g == c) {
            ++identiques;
        }
        // strict : on garde le premier octet qui atteint le maximum
        if (premier || std::abs(x) > ecartMax) {
            ecartMax = std::abs(x);
            octetMax = c;
            premier = false;
        }

        std::cout << c << " DECODE " << d << " GAMMA " << g
                  << " EXACT " << e << " ECART " << x << std::endl;
    }

    std::cout << "IDENTIQUES " << identiques << std::endl;
    std::cout << "ECART MAX " << ecartMax << " POUR " << octetMax << std::endl;

    return 0;
}
