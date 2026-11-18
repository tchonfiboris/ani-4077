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

// Une réserve de cases. Le monde INDEX ignore la génération, le monde
// GENERATION la compare.
class Reserve {
public:
    explicit Reserve(bool avecGeneration) : avecGeneration_(avecGeneration) {}

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
        if (h.numero < 0 || h.numero >= static_cast<int>(cases_.size())) return false;
        const Case& c = cases_[h.numero];
        if (!c.occupee) return false;
        if (avecGeneration_) return h.generation != 0 && c.generation == h.generation;
        return true;
    }

    // Détruire avec une poignée bonne ; sinon, rien ne se passe.
    void detruit(const Poignee& h) {
        if (!valide(h)) return;
        Case& c = cases_[h.numero];
        c.occupee = false;
        ++c.generation;
        libres_.push_back(h.numero);
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
    bool avecGeneration_;
    std::vector<Case> cases_;
    std::vector<int> libres_;
};

// Ce que retient une variable : sa poignée dans chaque monde et le nom créé.
struct Variable {
    Poignee index;
    Poignee generation;
    std::string nomCree;
};

int main() {
    int N = 0;
    if (!(std::cin >> N)) N = 0;

    Reserve monde_index(false);
    Reserve monde_generation(true);
    std::map<std::string, Variable> variables;

    long long fauxSilencieux = 0, perimeesDetectees = 0;

    for (int i = 1; i <= N; ++i) {
        std::string premier;
        if (!(std::cin >> premier)) break;

        if (premier == "DETRUIRE") {
            std::string v;
            std::cin >> v;
            // Chaque monde applique sa propre poignée à sa propre réserve.
            monde_index.detruit(variables[v].index);
            monde_generation.detruit(variables[v].generation);
        } else if (premier == "VOIR") {
            std::string v;
            std::cin >> v;
            const Variable& var = variables[v];

            std::string x = "RIEN";
            if (monde_index.valide(var.index)) x = monde_index.nom(var.index);

            std::string y = "PERIMEE";
            if (monde_generation.valide(var.generation)) {
                y = monde_generation.nom(var.generation);
            }

            if (x != "RIEN" && x != var.nomCree) ++fauxSilencieux;
            if (y == "PERIMEE") ++perimeesDetectees;

            std::cout << "VOIR LIGNE " << i << " INDEX " << x
                      << " GENERATION " << y << std::endl;
        } else {
            std::string egal, creer, nom;
            std::cin >> egal >> creer >> nom;
            Variable var;
            var.index = monde_index.cree(nom);
            var.generation = monde_generation.cree(nom);
            var.nomCree = nom;
            variables[premier] = var;
        }
    }

    std::cout << "FAUX SILENCIEUX " << fauxSilencieux << std::endl;
    std::cout << "PERIMEES DETECTEES " << perimeesDetectees << std::endl;
    std::cout << "VIVANTES INDEX " << monde_index.vivantes()
              << " GENERATION " << monde_generation.vivantes() << std::endl;
    return 0;
}