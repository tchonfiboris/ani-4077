#include <iostream>

int main() {

    long long seuil;
    int memoire; 
    int n;

    if (!(std::cin >> seuil >> memoire >> n)){
         return 0;}

    bool precedent = (memoire == 1);  // le seul booléen de mémoire
    int montants = 0, descendants = 0, pressees = 0;
    int suite = 0, plusLong = 0;

    for (int i = 0; i < n; ++i) {
        long long v;
        if (!(std::cin >> v)) 
        break;

        bool pressee = (v >= seuil);  // égalité comprise

        const char* front;
        if (pressee && !precedent) {
            front = "MONTE";
            ++montants;
        } else if (!pressee && precedent) {
            front = "DESCEND";
            ++descendants;
        } else {
            front = "AUCUN";
        }

        if (pressee) {
            ++pressees;
            ++suite;
            if (suite > plusLong) plusLong = suite;
        } else {
            suite = 0;
        }

        std::cout << i << " " << v << " "
                  << (pressee ? "PRESSEE" : "RELACHEE") << " " << front << std::endl;

        precedent = pressee;  // mise à jour après l'image
    }

    std::cout << "MONTANTS " << montants << std::endl;
    std::cout << "DESCENDANTS " << descendants << std::endl;
    std::cout << "PRESSEES " << pressees << std::endl;
    std::cout << "PLUS LONG " << plusLong << std::endl;

    return 0;
}
