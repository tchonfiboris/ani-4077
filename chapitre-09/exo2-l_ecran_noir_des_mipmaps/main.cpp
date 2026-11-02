#include <algorithm>
#include <iostream>
#include <string>

// Nombre de niveaux de la chaîne complète : on divise chaque côté par deux
// (division entière, minimum 1) jusqu'au niveau 1 x 1 inclus.
int chaineComplete(long long L, long long H) {
    int niveaux = 1;
    while (L > 1 || H > 1) {
        L = std::max(1LL, L / 2);
        H = std::max(1LL, H / 2);
        ++niveaux;
    }
    return niveaux;
}

int main() {
    int N;
    std::cin >> N;

    int noires = 0;
    long long perdus = 0;

    for (int i = 0; i < N; ++i) {
        std::string nom, filtre, niveauxStr;
        long long L, H;
        std::cin >> nom >> L >> H >> filtre >> niveauxStr;

        int complete = chaineComplete(L, H);

        int envoyes;
        if (niveauxStr == "GENERE") {
            envoyes = complete;
        } else {
            envoyes = std::min(std::stoi(niveauxStr), complete);
        }

        if (filtre == "DEFAUT") {
            filtre = "GL_NEAREST_MIPMAP_LINEAR";
        }

        bool exigeMipmaps = (filtre.find("MIPMAP") != std::string::npos);

        if (exigeMipmaps) {
            if (envoyes < complete) {
                ++noires;
                std::cout << nom << " NOIRE MANQUE " << (complete - envoyes) << std::endl;
            } else {
                std::cout << nom << " COMPLETE" << std::endl;
            }
        } else {
            // Seul le niveau 0 est lu : les autres niveaux sont inutiles
            perdus += envoyes - 1;
            std::cout << nom << " COMPLETE" << std::endl;
        }
    }

    std::cout << "NOIRES " << noires << std::endl;
    std::cout << "NIVEAUX PERDUS " << perdus << std::endl;
    std::cout << "GL_GET_ERROR GL_NO_ERROR" << std::endl;

    return 0;
}