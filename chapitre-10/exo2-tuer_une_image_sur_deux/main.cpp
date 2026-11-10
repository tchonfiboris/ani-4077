#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Segment {
    char c;
    long long debut, longueur;
    int z;
};

int main() {
    int W, S, F;
    std::cin >> W >> S >> F;

    std::vector<Segment> scene(S);
    for (auto& s : scene) std::cin >> s.c >> s.debut >> s.longueur >> s.z;

    std::string couleur(W, '.');
    std::vector<int> profondeur(W, 100);

    int vides = 0;

    std::string ligne;
    std::getline(std::cin, ligne);  // fin de la ligne précédente

    for (int k = 1; k <= F; ++k) {
        // On saute les lignes vides éventuelles.
        while (std::getline(std::cin, ligne)) {
            if (ligne.find_first_not_of(" \t\r") != std::string::npos) break;
        }

        std::istringstream iss(ligne);
        std::string mot;
        bool redim = false;
        std::string effacement = "RIEN";
        while (iss >> mot) {
            if (mot == "REDIM") redim = true;
            else effacement = mot;
        }

        // REDIM d'abord : les deux tampons redeviennent neufs.
        if (redim) {
            couleur.assign(W, '.');
            profondeur.assign(W, 100);
        }

        // Puis l'effacement : seulement ce que le mot nomme.
        if (effacement == "TOUT" || effacement == "COULEUR")
            couleur.assign(W, '.');
        if (effacement == "TOUT" || effacement == "PROFONDEUR")
            profondeur.assign(W, 100);

        // Puis le dessin, avec test de profondeur allumé.
        long long passes = 0;
        for (const auto& s : scene) {
            long long a = std::max(0LL, s.debut);
            long long b = std::min((long long)W, s.debut + s.longueur);
            for (long long p = a; p < b; ++p) {
                if (s.z < profondeur[p]) {
                    couleur[p] = s.c;
                    profondeur[p] = s.z;
                    ++passes;
                }
            }
        }

        if (passes == 0) ++vides;
        std::cout << "IMAGE " << k << " " << couleur << " PASSES " << passes << std::endl;
    }

    std::cout << "VIDES " << vides << std::endl;
    return 0;
}