#include <iostream>
#include <string>

int main() {

    int n;

    if (!(std::cin >> n)) {
        n = 0;}

    int nbValides = 0;
    int nbDefaut = 0;

    for (int i = 0; i < n; ++i) {

        std::string nom;
        std::string plateforme;
        int h1, h2, largeur, hauteur;

        if (!(std::cin >> nom >> plateforme >> h1 >> h2 >> largeur >> hauteur))
        break;

        bool valide;
        bool parDefaut = false;

        if (plateforme == "WINDOWS") {
            valide = (h1 == 1) && largeur > 0 && hauteur > 0;
        } else if (plateforme == "WAYLAND") {
            // la hauteur n'entre pas dans ce test
            valide = (h1 == 1) && (h2 == 1) && largeur > 0;
        } else if (plateforme == "ANDROID") {
            valide = (h1 == 1) && largeur > 0;
        } else if (plateforme == "MACOS") {
            valide = (h1 == 1) && (h2 == 1) && largeur > 0 && hauteur > 0;
        } else {
            // plateforme inconnue : on ne regarde pas les poignées
            valide = largeur > 0 && hauteur > 0;
            parDefaut = true;
        }

        if (!valide) {
            std::cout << nom << " INVALIDE" << std::endl;
        } else if (parDefaut) {
            std::cout << nom << " VALIDE PAR DEFAUT" << std::endl;
            ++nbValides;
            ++nbDefaut;
        } else {
            std::cout << nom << " VALIDE" << std::endl;
            ++nbValides;
        }
    }

    std::cout << "VALIDES " << nbValides << "" << std::endl;
    std::cout << "PAR DEFAUT " << nbDefaut << "" << std::endl;

    return 0;
}
