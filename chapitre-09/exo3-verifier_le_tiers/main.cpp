#include <algorithm>
#include <iostream>
#include <string>

int main() {
    int N;
    std::cin >> N;

    long long total = 0;
    long long sansMipmaps = 0;

    for (int i = 0; i < N; ++i) {
        std::string nom, mip;
        long long L, H;
        std::cin >> nom >> L >> H >> mip;

        long long base = L * H * 4;
        long long exact = base;
        long long estime = base;
        int niveaux = 1;

        if (mip == "OUI") {
            long long w = L, h = H;
            while (w > 1 || h > 1) {
                w = std::max(1LL, w / 2);
                h = std::max(1LL, h / 2);
                exact += w * h * 4;
                ++niveaux;
            }
            estime = base + base / 3;
        }

        long long ecart = estime - exact;

        std::cout << nom << " NIVEAUX " << niveaux
                  << " EXACT " << exact
                  << " ESTIME " << estime
                  << " ECART " << ecart << std::endl;

        total += exact;
        sansMipmaps += base;
    }

    std::cout << "TOTAL " << total << std::endl;
    std::cout << "SANS MIPMAPS " << sansMipmaps << std::endl;

    if (N == 0) {
        std::cout << "SURCOUT AUCUN" << std::endl;
    } else {
        long long surcout = (total - sansMipmaps) * 100 / sansMipmaps;
        std::cout << "SURCOUT " << surcout << " %" << std::endl;
    }

    return 0;
}