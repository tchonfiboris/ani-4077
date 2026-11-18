#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

typedef unsigned long long u64;

// Une case de la réserve : occupée ou non, avec sa génération et le nom
// de son occupant actuel.
struct Case {
    bool occupee;
    u64 generation;
    std::string nom;
};

class Reserve {
public:
    // Réemploie la case libérée le plus récemment, sinon ajoute une case.
    void cree(const std::string& nom, u64& i, u64& g) {
        if (!libres_.empty()) {
            u64 numero = libres_.back();
            libres_.pop_back();
            cases_[numero].occupee = true;
            cases_[numero].nom = nom;
            i = numero;
            g = cases_[numero].generation;
        } else {
            cases_.push_back({true, 1, nom});
            i = cases_.size() - 1;
            g = 1;
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

    // Détruit avec une poignée bonne ; renvoie vrai en cas de succès.
    bool detruit(u64 i, u64 g) {
        if (!valide(i, g)) return false;
        Case& c = cases_[i];
        c.occupee = false;
        ++c.generation;
        libres_.push_back(i);
        return true;
    }

    const std::string& nom(u64 i) const { return cases_[i].nom; }
    bool occupee(u64 i) const { return cases_[i].occupee; }

private:
    std::vector<Case> cases_;
    std::vector<u64> libres_;
};

int main() {
    int N = 0;
    if (!(std::cin >> N)) N = 0;

    Reserve reserve;
    // Table à part : le nom créé avec chaque poignée rendue. La case ne garde
    // que le nom de son occupant actuel, et la ressource détruite ne garde rien.
    std::map<std::pair<u64, u64>, std::string> noms;
    long long perimees = 0, inconnues = 0;

    for (int k = 0; k < N; ++k) {
        std::string ordre;
        if (!(std::cin >> ordre)) break;

        if (ordre == "CREER") {
            std::string nom;
            std::cin >> nom;
            u64 i, g;
            reserve.cree(nom, i, g);
            noms[{i, g}] = nom;
            std::cout << "CREER " << nom << " " << i << " " << g << std::endl;
        } else if (ordre == "DETRUIRE") {
            u64 i, g;
            std::cin >> i >> g;
            std::string nom = "RIEN";
            if (reserve.valide(i, g)) nom = reserve.nom(i);
            reserve.detruit(i, g);
            std::cout << "DETRUIRE " << i << " " << g << " " << nom << std::endl;
        } else if (ordre == "VOIR") {
            u64 i, g;
            std::cin >> i >> g;
            if (reserve.valide(i, g)) {
                std::cout << "VOIR " << i << " " << g << " " << reserve.nom(i) << std::endl;
            } else {
                auto it = noms.find({i, g});
                if (it != noms.end()) {
                    ++perimees;
                    std::string x = reserve.occupee(i) ? reserve.nom(i) : std::string("VIDE");
                    std::cout << "VOIR " << i << " " << g << " PERIMEE "
                              << it->second << " CASE " << x << std::endl;
                } else {
                    ++inconnues;
                    std::cout << "VOIR " << i << " " << g << " INCONNUE" << std::endl;
                }
            }
        }
    }

    std::cout << "PERIMEES " << perimees << std::endl;
    std::cout << "INCONNUES " << inconnues << std::endl;
    std::cout << "NOMS GARDES " << noms.size() << std::endl;
    return 0;
}
