#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    int E, N;
    std::cin >> E >> N;

    std::vector<std::string> noms(E);
    std::map<std::string, int> indice;
    for (int i = 0; i < E; ++i) {
        std::cin >> noms[i];
        indice[noms[i]] = i;
    }

    int unite = 0;                     // unité courante
    std::vector<long long> unites(16, 0);  // texture attachée à chaque unité
    std::vector<int> valeur(E, 0);     // unité lue par chaque échantillonneur

    int dessin = 0, justes = 0, faux = 0, ignores = 0;

    for (int c = 0; c < N; ++c) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "ACTIVE") {
            std::cin >> unite;
        } else if (cmd == "BIND") {
            long long t;
            std::cin >> t;
            unites[unite] = t;         // attaché à l'unité COURANTE
        } else if (cmd == "UNIFORM1I") {
            std::string nom;
            int u;
            std::cin >> nom >> u;
            auto it = indice.find(nom);
            if (it != indice.end()) {
                valeur[it->second] = u;
            }
        } else if (cmd == "UNIFORM1F") {
            std::string nom;
            int u;
            std::cin >> nom >> u;
            ++ignores;                 // sans effet
        } else if (cmd == "DESSINE") {
            ++dessin;
            std::string erreurs;
            for (int i = 0; i < E; ++i) {
                long long attendu;
                std::cin >> attendu;
                long long lu = unites[valeur[i]];
                if (lu != attendu) {
                    erreurs += " " + noms[i] + "=" + std::to_string(lu)
                             + "/" + std::to_string(attendu);
                }
            }
            if (erreurs.empty()) {
                ++justes;
                std::cout << "DESSIN " << dessin << " JUSTE" << std::endl;
            } else {
                ++faux;
                std::cout << "DESSIN " << dessin << " FAUX" << erreurs << std::endl;
            }
        }
    }

    std::cout << "JUSTES " << justes << std::endl;
    std::cout << "FAUX " << faux << std::endl;
    std::cout << "UNIFORM1F IGNORES " << ignores << std::endl;

    return 0;
}