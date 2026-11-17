#include <iostream>
#include <string>

static int indexCategorie(const std::string& quoi) {
    if (quoi == "PROGRAMME") return 0;
    if (quoi == "TABLEAU") return 1;
    if (quoi == "TEXTURE") return 2;
    return 3; // CIBLE
}

struct Compteur {
    long long dernier[4];
    long long liaisons;
    long long inutiles;
    long long dessins;
    long long elements;
    long long suite;     // plus longue suite d'inutiles
    long long courante;  // suite en cours

    Compteur() { reinit(); }

    void reinit() {
        for (int i = 0; i < 4; ++i) dernier[i] = 0;
        liaisons = inutiles = dessins = elements = suite = courante = 0;
    }

    void lie(int cat, long long id) {
        ++liaisons;
        if (id == dernier[cat]) {
            ++inutiles;
            ++courante;
            if (courante > suite) suite = courante;
        } else {
            dernier[cat] = id;
            courante = 0;
        }
    }

    void dessine(long long e) {
        ++dessins;
        elements += e;
    }

    long long part() const {
        return liaisons == 0 ? 0 : inutiles * 100 / liaisons;
    }
};

int main() {
    int N = 0;
    if (!(std::cin >> N)) N = 0;

    Compteur c;
    int rapports = 0;

    for (int i = 0; i < N; ++i) {
        std::string cmd;
        if (!(std::cin >> cmd)) break;

        if (cmd == "LIE") {
            std::string quoi;
            long long id;
            std::cin >> quoi >> id;
            c.lie(indexCategorie(quoi), id);
        } else if (cmd == "DESSINE") {
            long long e;
            std::cin >> e;
            c.dessine(e);
        } else if (cmd == "RAPPORT") {
            ++rapports;
            std::cout << "LIAISONS " << c.liaisons
                      << " INUTILES " << c.inutiles
                      << " PART " << c.part() << " %"
                      << " DESSINS " << c.dessins
                      << " ELEMENTS " << c.elements
                      << " SUITE " << c.suite << std::endl;
        } else if (cmd == "REINIT") {
            c.reinit();
        }
    }

    std::cout << "RAPPORTS " << rapports << std::endl;
    return 0;
}