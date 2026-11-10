#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Cible {
    long long L = 0, H = 0;
};

struct Passe {
    std::string nom;
    long long charge;
    long long ecrit;
};

int main() {
    int T;
    std::cin >> T;

    std::map<std::string, Cible> cibles;
    for (int i = 0; i < T; ++i) {
        std::string nom;
        long long L, H;
        std::cin >> nom >> L >> H;
        cibles[nom] = {L, H};
    }

    int P;
    std::cin >> P;

    std::vector<Passe> passes;
    std::string liee = "FENETRE";  // au départ, la cible liée est FENETRE
    long long changements = 0;

    for (int i = 0; i < P; ++i) {
        std::string nom, mode;
        std::cin >> nom >> mode;

        // Des lignes qui se suivent sur la même cible forment une seule passe.
        // Une nouvelle passe commence quand la cible diffère de la cible liée.
        if (passes.empty() || nom != passes.back().nom) {
            if (nom != liee) ++changements;
            liee = nom;

            // 4 octets par pixel. Seule la première ligne de la passe décide
            // du chargement : GARDE relit toute la cible, EFFACE ne relit rien.
            long long octets = cibles[nom].L * cibles[nom].H * 4;
            Passe p;
            p.nom = nom;
            p.charge = (mode == "GARDE") ? octets : 0;
            p.ecrit = octets;  // chaque passe écrit toute sa cible en finissant
            passes.push_back(p);
        }
    }

    long long lus = 0, ecrits = 0;
    for (size_t k = 0; k < passes.size(); ++k) {
        std::cout << "PASSE " << k + 1 << " " << passes[k].nom
                  << " CHARGE " << passes[k].charge
                  << " ECRIT " << passes[k].ecrit << std::endl;
        lus += passes[k].charge;
        ecrits += passes[k].ecrit;
    }

    std::cout << "PASSES " << passes.size() << std::endl;
    std::cout << "CHANGEMENTS " << changements << std::endl;
    std::cout << "LUS " << lus << std::endl;
    std::cout << "ECRITS " << ecrits << std::endl;
    std::cout << "TOTAL " << lus + ecrits << std::endl;
    return 0;
}
