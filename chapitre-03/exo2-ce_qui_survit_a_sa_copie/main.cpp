#include <iostream>
#include "include.h"


int main() {
    int n;
    if (!(std::cin >> n)){
         n = 0;}

    int nbGardes = 0; 
    int nbEphemeres = 0; 
    int nbInconnus = 0;

    for (int i = 0; i < n; ++i) {
        std::string champ;
        if (!(std::cin >> champ)) 
        break;

        if (contient(GARDES, 10, champ)) {
            std::cout << champ << " GARDER " << std::endl;
            ++nbGardes;
        } else if (contient(EPHEMERES, 4, champ)) {
            std::cout << champ << " HORS DESCRIPTEUR " << std::endl;
            ++nbEphemeres;
        } else {
            std::cout << champ << " INCONNU " << std::endl;
            ++nbInconnus;
        }
    }

    // affiche les resultats
    std::cout << "GARDES " << nbGardes << std::endl;
    std::cout << "EPHEMERES " << nbEphemeres << std::endl;
    std::cout << "INCONNUS " << nbInconnus << std::endl;
    return 0;
}