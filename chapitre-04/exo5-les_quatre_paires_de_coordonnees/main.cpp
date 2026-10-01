#include <iostream>
#include <cstdlib>
#include <algorithm>

// Pas sur un axe : le brut s'il est sous le seuil (inclus), le double sinon
static long long pas(long long brut, long long seuil) {
    return (std::llabs(brut) <= seuil) ? brut : 2 * brut;
}

int main() {

    long long largeur; 
    long long hauteur; 
    long long fx; 
    long long fy; 
    long long l; 
    long long h; 
    long long sx; 
    long long sy; 
    long long seuil;
    int n;

    if (!(std::cin >> largeur >> hauteur)) return 0;
    if (!(std::cin >> fx >> fy >> l >> h)) return 0;
    if (!(std::cin >> sx >> sy >> seuil)) return 0;
    if (!(std::cin >> n)) n = 0;

    long long sommeDx = 0; 
    long long sommeDy = 0; 
    long long sommeRx = 0; 
    long long sommeRy = 0;
    int bloques = 0;

    for (int i = 0; i < n; ++i) {

        long long rx;
        long long ry;

        if (!(std::cin >> rx >> ry)) 
        break;

        // Nouvelle position, bornée à l'écran, axe par axe
        long long nx = std::clamp(sx + pas(rx, seuil), 0LL, largeur - 1);
        long long ny = std::clamp(sy + pas(ry, seuil), 0LL, hauteur - 1);

        // Déplacement calculé après les bornes
        long long dx = nx - sx;
        long long dy = ny - sy;
        sx = nx;
        sy = ny;

        // Position dans la zone cliente, éventuellement négative
        long long x = sx - fx;
        long long y = sy - fy;
        bool dedans = (x >= 0 && x < l && y >= 0 && y < h);

        if ((rx != 0 && dx == 0) || (ry != 0 && dy == 0)) {
            ++bloques;}

        sommeDx += dx;
        sommeDy += dy;
        sommeRx += rx;
        sommeRy += ry;

        std::cout << sx << " " << sy << " " << x << " " << y << " "
                  << dx << " " << dy << " " << rx << " " << ry << " "
                  << (dedans ? "DEDANS" : "DEHORS") << std::endl;
    }

    std::cout << "SOMME DELTA " << sommeDx << " " << sommeDy << std::endl;
    std::cout << "SOMME RAW " << sommeRx << " " << sommeRy << std::endl;
    std::cout << "BLOQUES " << bloques << std::endl;

    return 0;
}
