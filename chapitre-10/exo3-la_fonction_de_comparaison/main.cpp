#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    int W, N;
    std::cin >> W >> N;

    std::string couleur(W, '.');
    std::vector<int> profondeur(W, 100);

    bool test = false;
    bool masque = true;
    std::string fonction = "LESS";

    long long ecrits = 0, profondeurs = 0, jetes = 0;

    for (int i = 0; i < N; ++i) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "TEST") {
            std::string v;
            std::cin >> v;
            test = (v == "ON");
        } else if (cmd == "MASK") {
            std::string v;
            std::cin >> v;
            masque = (v == "ON");
        } else if (cmd == "FUNC") {
            std::cin >> fonction;
        } else if (cmd == "CLEAR") {
            couleur.assign(W, '.');
            profondeur.assign(W, 100);
        } else if (cmd == "SEG") {
            char c;
            long long debut, longueur;
            int z;
            std::cin >> c >> debut >> longueur >> z;

            // Les pixels hors de la bande sont ignorés.
            long long a = std::max(0LL, debut);
            long long b = std::min((long long)W, debut + longueur);

            for (long long p = a; p < b; ++p) {
                if (!test) {
                    // Test éteint : la couleur est écrite, jamais la profondeur.
                    couleur[p] = c;
                    ++ecrits;
                    continue;
                }

                int d = profondeur[p];
                bool passe = false;
                if (fonction == "LESS") passe = (z < d);
                else if (fonction == "LEQUAL") passe = (z <= d);
                else if (fonction == "GREATER") passe = (z > d);
                else if (fonction == "ALWAYS") passe = true;
                else if (fonction == "NEVER") passe = false;

                if (passe) {
                    couleur[p] = c;
                    ++ecrits;
                    // Le masque ne compte que quand le test passe.
                    if (masque) {
                        profondeur[p] = z;
                        ++profondeurs;
                    }
                } else {
                    ++jetes;  // rien n'est écrit
                }
            }
        }
    }

    std::cout << "COULEUR " << couleur << std::endl;
    std::cout << "PROFONDEUR";
    for (int p = 0; p < W; ++p) std::cout << " " << profondeur[p];
    std::cout << std::endl;
    std::cout << "ECRITS " << ecrits << std::endl;
    std::cout << "PROFONDEURS " << profondeurs << std::endl;
    std::cout << "JETES " << jetes << std::endl;
    return 0;
}