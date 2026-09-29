#include <iostream>
#include <string>

static long long rapport(long long largeur, long long hauteur) {
    if (hauteur == 0) return 0;
    return largeur * 1000 / hauteur;
}

int main() {

    long long bordure, barre, seuil;

    if (!(std::cin >> bordure >> barre >> seuil)) return 0;

    int n;
    if (!(std::cin >> n)) {
        n = 0;}

    int ovales = 0;
    long long pire = 0;

    for (int i = 0; i < n; ++i) {

        std::string nom;
        long long largeur, hauteur;

        if (!(std::cin >> nom >> largeur >> hauteur))
        break;

        long long largeurFenetre = largeur + 2 * bordure;
        long long hauteurFenetre = hauteur + 2 * bordure + barre;

        long long rapportClient = rapport(largeur, hauteur);
        long long rapportFenetre = rapport(largeurFenetre, hauteurFenetre);

        long long ecart = rapportClient - rapportFenetre;

        if (ecart < 0){
             ecart = -ecart;}

        bool invisible = (ecart <= seuil);

        if (!invisible) {
            ++ovales;}
        if (ecart > pire) {
            pire = ecart;}

        std::cout << nom << " " << largeurFenetre << " " << hauteurFenetre << " "
                  << rapportClient << " " << rapportFenetre << " " << ecart << " "
                  << (invisible ? "INVISIBLE" : "CERCLES OVALES") << std::endl;
    }

    std::cout << "OVALES " << ovales << std::endl;
    std::cout << "PIRE " << pire << std::endl;

    return 0;
}
