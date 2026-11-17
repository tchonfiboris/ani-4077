#include <iostream>
#include <string>

// Compare a et b : renvoie "MONTE" si a > b, "BAISSE" si a < b, "STABLE" sinon.
static const char* sens(long long a, long long b) {
    if (a > b) return "MONTE";
    if (a < b) return "BAISSE";
    return "STABLE";
}

int main() {
    int N = 0;
    if (!(std::cin >> N)) N = 0;

    long long L0 = 0, I0 = 0;   // version précédente
    long long trompeurs = 0;
    std::string meilleur = "AUCUN";
    long long meilleurL = 0;

    for (int i = 0; i < N; ++i) {
        std::string nom;
        long long L, I;
        if (!(std::cin >> nom >> L >> I)) break;

        long long part = I * 100 / L;
        long long utiles = L - I;

        if (i == 0) {
            std::cout << nom << " PART " << part << " % UTILES " << utiles
                      << " DEPART" << std::endl;
        } else {
            const char* total = sens(L, L0);
            // Parts exactes par produits en croix : I/L contre I0/L0.
            const char* partSens = sens(I * L0, I0 * L);

            bool trompeur = (std::string(total) == "MONTE" && std::string(partSens) == "BAISSE") ||
                            (std::string(total) == "BAISSE" && std::string(partSens) == "MONTE");
            if (trompeur) ++trompeurs;

            std::cout << nom << " PART " << part << " % UTILES " << utiles
                      << " TOTAL " << total << " PART " << partSens << " "
                      << (trompeur ? "TROMPEUR" : "COHERENT") << std::endl;
        }

        // Meilleure version : plus petit total, la première en cas d'égalité.
        if (i == 0 || L < meilleurL) {
            meilleurL = L;
            meilleur = nom;
        }

        L0 = L;
        I0 = I;
    }

    std::cout << "TROMPEURS " << trompeurs << std::endl;
    std::cout << "MEILLEUR " << meilleur << std::endl;
    return 0;
}