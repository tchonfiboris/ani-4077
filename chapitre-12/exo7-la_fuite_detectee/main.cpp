#include <iostream>
#include <string>
#include <vector>

typedef unsigned long long u64;

class Reserve {
public:
    // Réemploie la case libérée le plus récemment, sinon ajoute une case.
    void cree(const std::string& nom) {
        if (!libres_.empty()) {
            int numero = libres_.back();
            libres_.pop_back();
            cases_[numero].occupee = true;
            cases_[numero].nom = nom;
        } else {
            cases_.push_back({true, 1, nom});
        }
    }

    // Une poignée est bonne si sa génération n'est pas 0, si sa case existe,
    // si elle est occupée et si elle porte la même génération.
    bool valide(u64 i, u64 g) const {
        if (g == 0) return false;
        if (i >= cases_.size()) return false;
        const Case& c = cases_[i];
        return c.occupee && c.generation == g;
    }

    // Renvoie vrai si la destruction a eu lieu.
    bool detruit(u64 i, u64 g) {
        if (!valide(i, g)) return false;
        Case& c = cases_[i];
        c.occupee = false;
        ++c.generation;
        libres_.push_back(static_cast<int>(i));
        return true;
    }

    std::size_t nbCases() const { return cases_.size(); }
    bool occupee(std::size_t i) const { return cases_[i].occupee; }
    const std::string& nom(std::size_t i) const { return cases_[i].nom; }

private:
    struct Case {
        bool occupee;
        u64 generation;
        std::string nom;
    };

    std::vector<Case> cases_;
    std::vector<int> libres_;
};

// L'ordre des types est celui du parcours à l'arrêt.
static const char* NOMS_TYPES[4] = {"MAILLAGE", "NUANCEUR", "TEXTURE", "CIBLE"};

static int indexType(const std::string& type) {
    for (int i = 0; i < 4; ++i) {
        if (type == NOMS_TYPES[i]) return i;
    }
    return 3;
}

int main() {
    int N = 0;
    if (!(std::cin >> N)) N = 0;

    Reserve reserves[4];
    long long ignores = 0;

    for (int k = 0; k < N; ++k) {
        std::string ordre, type;
        if (!(std::cin >> ordre >> type)) break;
        const int t = indexType(type);

        if (ordre == "CREER") {
            std::string nom;
            std::cin >> nom;
            reserves[t].cree(nom);
        } else if (ordre == "DETRUIRE") {
            u64 i, g;
            std::cin >> i >> g;
            // Une destruction sans effet ne dit rien : on la compte nous-mêmes.
            if (!reserves[t].detruit(i, g)) ++ignores;
        }
    }

    // À l'arrêt : tout ce qui vit encore est une ressource oubliée.
    long long fuites = 0;
    for (int t = 0; t < 4; ++t) {
        for (std::size_t i = 0; i < reserves[t].nbCases(); ++i) {
            if (reserves[t].occupee(i)) {
                std::cout << "FUITE " << NOMS_TYPES[t] << " "
                          << reserves[t].nom(i) << std::endl;
                ++fuites;
            }
        }
    }

    std::cout << "FUITES " << fuites << std::endl;
    std::cout << "IGNORES " << ignores << std::endl;
    return 0;
}