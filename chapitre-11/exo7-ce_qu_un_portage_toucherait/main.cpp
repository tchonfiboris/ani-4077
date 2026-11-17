#include <iostream>
#include <string>
#include <vector>

struct Fichier {
    std::string nom;
    std::string sorte;
    long long L;
    long long G;
};

int main() {
    int N = 0;
    if (!(std::cin >> N)) N = 0;

    std::vector<Fichier> fichiers(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> fichiers[i].nom >> fichiers[i].sorte
                 >> fichiers[i].L >> fichiers[i].G;
    }

    // Première passe : repérer les fuites avant de décider quoi que ce soit.
    long long fuites = 0;
    for (const Fichier& f : fichiers) {
        if (f.sorte == "INTERFACE" && f.G > 0) ++fuites;
    }

    long long cout_ = 0, sur = 0;
    for (const Fichier& f : fichiers) {
        sur += f.L;

        if (f.sorte == "INTERFACE" && f.G > 0) {
            std::cout << f.nom << " FUITE " << f.L << std::endl;
            cout_ += f.L;
        } else if (fuites > 0 && f.sorte == "APPLICATION") {
            std::cout << f.nom << " REECRIT " << f.L << std::endl;
            cout_ += f.L;
        } else if (f.G == 0) {
            std::cout << f.nom << " INCHANGE" << std::endl;
        } else if (f.sorte == "APPLICATION") {
            std::cout << f.nom << " REVOIR " << f.G << std::endl;
            cout_ += f.G;
        } else {
            // IMPLEMENTATION qui nomme OpenGL
            std::cout << f.nom << " REECRIT " << f.L << std::endl;
            cout_ += f.L;
        }
    }

    std::cout << "COUT " << cout_ << std::endl;
    std::cout << "SUR " << sur << std::endl;
    if (sur == 0) {
        std::cout << "PART AUCUNE" << std::endl;
    } else {
        std::cout << "PART " << cout_ * 100 / sur << " %" << std::endl;
    }
    std::cout << "FUITES " << fuites << std::endl;
    return 0;
}