#include <iostream>
#include <string>
#include <vector>

typedef unsigned long long u64;

// Les quatre causes d'échec d'une recherche, testées dans cet ordre.
enum Cause { OK, NULLE, HORS_BORNES, VIDE, PERIMEE };

static const char* nomCause(Cause c) {
    switch (c) {
        case NULLE: return "NULLE";
        case HORS_BORNES: return "HORS_BORNES";
        case VIDE: return "VIDE";
        case PERIMEE: return "PERIMEE";
        default: return "";
    }
}

class Reserve {
public:
    Reserve() : tete_(-1), vivants_(0), retraits_(0) {}

    // Pose : réemploie la case libérée le plus récemment, sinon en ajoute une.
    void pose(const std::string& nom, u64& i, u64& g) {
        if (tete_ != -1) {
            int numero = tete_;
            tete_ = cases_[numero].suivante;   // la liste vit dans les trous
            cases_[numero].occupee = true;
            cases_[numero].nom = nom;
            cases_[numero].suivante = -1;
            i = static_cast<u64>(numero);
            g = cases_[numero].generation;
        } else {
            cases_.push_back({true, 1, nom, -1});
            i = cases_.size() - 1;
            g = 1;
        }
        ++vivants_;
    }

    // Première cause vraie, dans l'ordre : NULLE, HORS_BORNES, VIDE, PERIMEE.
    Cause examine(u64 i, u64 g) const {
        if (g == 0) return NULLE;
        if (i >= cases_.size()) return HORS_BORNES;
        const Case& c = cases_[i];
        if (!c.occupee) return VIDE;
        if (c.generation != g) return PERIMEE;
        return OK;
    }

    const std::string& nom(u64 i) const { return cases_[i].nom; }

    // Retire si la poignée est bonne ; renvoie vrai en cas de succès.
    bool retire(u64 i, u64 g) {
        if (examine(i, g) != OK) return false;
        Case& c = cases_[i];
        c.occupee = false;
        ++c.generation;
        c.suivante = tete_;                    // la case devient la tête de liste
        tete_ = static_cast<int>(i);
        --vivants_;
        ++retraits_;
        return true;
    }

    u64 vivants() const { return vivants_; }
    u64 nbCases() const { return cases_.size(); }
    u64 retraits() const { return retraits_; }

private:
    struct Case {
        bool occupee;
        u64 generation;
        std::string nom;
        int suivante;   // case libre suivante, valable seulement si la case est libre
    };

    std::vector<Case> cases_;
    int tete_;          // dernière case libérée, -1 s'il n'y en a pas
    u64 vivants_;
    u64 retraits_;
};

int main() {
    int N = 0;
    if (!(std::cin >> N)) N = 0;

    Reserve reserve;

    for (int k = 0; k < N; ++k) {
        std::string ordre;
        if (!(std::cin >> ordre)) break;

        if (ordre == "POSER") {
            std::string nom;
            std::cin >> nom;
            u64 i, g;
            reserve.pose(nom, i, g);
            std::cout << "POSER " << nom << " " << i << " " << g << std::endl;
        } else if (ordre == "RETIRER") {
            u64 i, g;
            std::cin >> i >> g;
            std::string nom;
            bool bonne = (reserve.examine(i, g) == OK);
            if (bonne) nom = reserve.nom(i);
            reserve.retire(i, g);
            std::cout << "RETIRER " << i << " " << g << " "
                      << (bonne ? nom : std::string("RIEN")) << std::endl;
        } else if (ordre == "TROUVER") {
            u64 i, g;
            std::cin >> i >> g;
            Cause c = reserve.examine(i, g);
            std::cout << "TROUVER " << i << " " << g << " "
                      << (c == OK ? reserve.nom(i) : std::string(nomCause(c)))
                      << std::endl;
        }
    }

    std::cout << "VIVANTS " << reserve.vivants() << std::endl;
    std::cout << "CASES " << reserve.nbCases() << std::endl;
    std::cout << "RETRAITS " << reserve.retraits() << std::endl;
    return 0;
}