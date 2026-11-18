#include <iostream>
#include <map>
#include <string>
#include <vector>

// Une case de la réserve : occupée ou non, avec sa génération et son nom.
struct Case {
    bool occupee;
    int generation;
    std::string nom;
};

// Une poignée : numéro de case et génération au moment de la création.
struct Poignee {
    int numero;
    int generation;
};

class Reserve {
public:
    // Réemploie la case libérée le plus récemment, sinon ajoute une case.
    Poignee cree(const std::string& nom) {
        if (!libres_.empty()) {
            int numero = libres_.back();
            libres_.pop_back();
            cases_[numero].occupee = true;
            cases_[numero].nom = nom;
            return {numero, cases_[numero].generation};
        }
        cases_.push_back({true, 1, nom});
        return {static_cast<int>(cases_.size()) - 1, 1};
    }

    bool valide(const Poignee& h) const {
        if (h.generation == 0) return false;
        if (h.numero < 0 || h.numero >= static_cast<int>(cases_.size())) return false;
        const Case& c = cases_[h.numero];
        return c.occupee && c.generation == h.generation;
    }

    // Renvoie vrai si la destruction a vidé une case.
    bool detruit(const Poignee& h) {
        if (!valide(h)) return false;
        Case& c = cases_[h.numero];
        c.occupee = false;
        ++c.generation;
        libres_.push_back(h.numero);
        return true;
    }

    const std::string& nom(const Poignee& h) const { return cases_[h.numero].nom; }

    int vivantes() const {
        int n = 0;
        for (const Case& c : cases_) {
            if (c.occupee) ++n;
        }
        return n;
    }

private:
    std::vector<Case> cases_;
    std::vector<int> libres_;
};

static const char* NOMS_TYPES[4] = {"MAILLAGE", "NUANCEUR", "TEXTURE", "CIBLE"};

static int indexType(const std::string& type) {
    for (int i = 0; i < 4; ++i) {
        if (type == NOMS_TYPES[i]) return i;
    }
    return 3;
}

enum Genre { CREER, DETRUIRE, VOIR };

struct Ligne {
    Genre genre;
    std::string variable;
    int type;
    std::string nom;   // pour CREER
};

struct Variable {
    int type;          // TYPEV : le type de sa création
    Poignee poignee;
};

int main() {
    int N = 0;
    if (!(std::cin >> N)) N = 0;

    // Lecture du script.
    std::vector<Ligne> lignes(N);
    for (int i = 0; i < N; ++i) {
        std::string premier;
        std::cin >> premier;
        if (premier == "DETRUIRE" || premier == "VOIR") {
            std::string type, v;
            std::cin >> type >> v;
            lignes[i] = {premier == "VOIR" ? VOIR : DETRUIRE, v, indexType(type), ""};
        } else {
            std::string egal, creer, type, nom;
            std::cin >> egal >> creer >> type >> nom;
            lignes[i] = {CREER, premier, indexType(type), nom};
        }
    }

    // Le compilateur : une variable a le type de sa création.
    std::map<std::string, int> typesVariables;
    std::vector<bool> refusee(N, false);
    std::vector<std::string> refus;
    for (int i = 0; i < N; ++i) {
        const Ligne& l = lignes[i];
        if (l.genre == CREER) {
            typesVariables[l.variable] = l.type;
        } else if (typesVariables[l.variable] != l.type) {
            refusee[i] = true;
            refus.push_back("REFUS LIGNE " + std::to_string(i + 1) + " " +
                            NOMS_TYPES[typesVariables[l.variable]] + " VERS " +
                            NOMS_TYPES[l.type]);
        }
    }

    std::cout << (refus.empty() ? "COMPILATION ACCEPTEE" : "COMPILATION REFUSEE")
              << std::endl;
    for (const std::string& r : refus) std::cout << r << std::endl;

    // Exécution sans marque : une poignée n'est que deux entiers.
    std::cout << "EXECUTION SANS MARQUE" << std::endl;
    Reserve reserves[4];
    std::map<std::string, Variable> variables;
    long long detruitsATort = 0, vusATort = 0;

    for (int i = 0; i < N; ++i) {
        const Ligne& l = lignes[i];
        if (l.genre == CREER) {
            variables[l.variable] = {l.type, reserves[l.type].cree(l.nom)};
        } else if (l.genre == DETRUIRE) {
            bool detruit = reserves[l.type].detruit(variables[l.variable].poignee);
            if (detruit && refusee[i]) ++detruitsATort;
        } else {
            const Poignee& h = variables[l.variable].poignee;
            if (reserves[l.type].valide(h)) {
                std::cout << "VOIR LIGNE " << (i + 1) << " "
                          << reserves[l.type].nom(h) << std::endl;
                if (refusee[i]) ++vusATort;
            } else {
                std::cout << "VOIR LIGNE " << (i + 1) << " PERIMEE" << std::endl;
            }
        }
    }

    std::cout << "DETRUITS A TORT " << detruitsATort << std::endl;
    std::cout << "VUS A TORT " << vusATort << std::endl;
    std::cout << "VIVANTS " << reserves[0].vivantes() << " " << reserves[1].vivantes()
              << " " << reserves[2].vivantes() << " " << reserves[3].vivantes()
              << std::endl;
    return 0;
}