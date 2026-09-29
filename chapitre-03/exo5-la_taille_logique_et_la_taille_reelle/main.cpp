#include <iostream>
#include <string>

int main() {
    int n;
    if (!(std::cin >> n)){
         n = 0;}

    int aCorriger = 0;
    long long pire = 0;

    for (int i = 0; i < n; ++i) {

        std::string nom;
        long long largeur, hauteur, facteur;

        if (!(std::cin >> nom >> largeur >> hauteur >> facteur)) 
        break;

        // Le facteur s'applique à chaque dimension séparément (on multiplie avant de diviser)
        long long largeurReelle = largeur * facteur / 1000;
        long long hauteurReelle = hauteur * facteur / 1000;

        long long pixelsLogiques = largeur * hauteur;
        long long pixelsReels = largeurReelle * hauteurReelle;

        long long facteurSurface = (pixelsLogiques == 0) ? 0 : pixelsReels * 100 / pixelsLogiques;

        const char* verdict;
        if (facteur == 1000) {
            verdict = "IDENTIQUE";
        } else {
            verdict = (facteur > 1000) ? "ETIRE FLOU" : "REDUIT";
            ++aCorriger;
        }

        if (facteurSurface > pire) pire = facteurSurface;

        std::cout << nom << " " << largeurReelle << " " << hauteurReelle << " "
                  << pixelsLogiques << " " << pixelsReels << " "
                  << facteurSurface << " " << verdict << std::endl;
    }

    std::cout << "A CORRIGER " << aCorriger << std::endl;
    std::cout << "PIRE " << pire << std::endl;

    return 0;
}
