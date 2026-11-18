#include <iostream>
#include <map>
#include <string>
#include <vector>

// Une case de la réserve : occupée ou non, avec sa génération et son nom.
struct Case {
    bool occupee;
    long long generation;
    std::string nom;
};

// Une poignée : numéro de case et génération au moment de la création.
struct Poignee {
    long long numero;
    long long generation;
};

class Reserve {
public:
    // Réemploie la case libérée le plus récemment, sinon ajoute une case.
    Poignee cree(const std::string& nom) {
        if (!libres_.empty()) {
            long long numero = libres_.back();
            libres_.pop_back();
            cases_[numero].occupee = true;
            cases_[numero].nom = nom;
            return {numero, cases_[numero].generation};
        }
        cases_.push_back({true, 1, nom});
        return {static_cast<long long>(cases_.size()) - 1, 1};
    }

    // Bonne si la génération n'est pas 0, si la case existe, est occupée
    // et porte la même génération.
    bool valide(const Poignee& h) const {
        if (h.generation == 0) return false;
        if (h.numero < 0 || h.numero >= static_cast<long long>(cases_.size())) return false;
        const Case& c = cases_[h.numero];
        return c.occupee && c.generation == h.generation;
    }

    // Vide la case : sa génération augmente de 1 et elle devient libre.
    void vide(const Poignee& h) {
        if (!valide(h)) return;
        Case& c = cases_[h.numero];
        c.occupee = false;
        ++c.generation;
        libres_.push_back(h.numero);
    }

    const std::string& nom(const Poignee& h) const { return cases_[h.numero].nom; }
    std::size_t nbCases() const { return cases_.size(); }

private:
    std::vector<Case> cases_;
    std::vector<long long> libres_;
};

// Ce que retient une variable : sa poignée dans chaque monde.
struct Variable {
    Poignee a;
    Poignee b;
    bool attend;   // la ressource est déjà en file de destruction
};

// Une ressource en file : son nom, son échéance et sa poignée du monde B.
struct EnFile {
    std::string nom;
    long long echeance;
    Poignee b;
};

int main() {
    long long D = 0;
    int N = 0;
    if (!(std::cin >> D >> N)) return 0;

    Reserve monde_a, monde_b;
    std::map<std::string, Variable> variables;
    std::vector<EnFile> file;

    long long images = 0;
    long long detecteesA = 0, detecteesB = 0;
    std::size_t fileMax = 0;

    for (int k = 1; k <= N; ++k) {
        std::string premier;
        if (!(std::cin >> premier)) break;

        if (premier == "RETIRER") {
            std::string v;
            std::cin >> v;
            Variable& var = variables[v];
            // Il faut une poignée bonne dans les deux mondes, sans attente en cours.
            if (monde_a.valide(var.a) && monde_b.valide(var.b) && !var.attend) {
                file.push_back({monde_b.nom(var.b), images + D, var.b});
                var.attend = true;
                // Monde A : la case se vide tout de suite.
                monde_a.vide(var.a);
                // Monde B : la case reste occupée jusqu'à la destruction réelle.
            }
        } else if (premier == "VOIR") {
            std::string v;
            std::cin >> v;
            const Variable& var = variables[v];
            std::string x = "PERIMEE", y = "PERIMEE";
            if (monde_a.valide(var.a)) x = monde_a.nom(var.a);
            else ++detecteesA;
            if (monde_b.valide(var.b)) y = monde_b.nom(var.b);
            else ++detecteesB;
            std::cout << "VOIR LIGNE " << k << " A " << x << " B " << y << std::endl;
        } else if (premier == "IMAGE") {
            ++images;
            std::vector<EnFile> reste;
            std::string noms;
            for (const EnFile& e : file) {
                if (e.echeance <= images) {
                    noms += " " + e.nom;
                    monde_b.vide(e.b);   // destruction réelle ; A a déjà vidé sa case
                } else {
                    reste.push_back(e);
                }
            }
            file = reste;
            std::cout << "IMAGE " << images << " DETRUITS"
                      << (noms.empty() ? std::string(" AUCUN") : noms) << std::endl;
        } else {
            std::string egal, creer, nom;
            std::cin >> egal >> creer >> nom;
            Variable var;
            var.a = monde_a.cree(nom);
            var.b = monde_b.cree(nom);
            var.attend = false;
            variables[premier] = var;
        }

        if (file.size() > fileMax) fileMax = file.size();
    }

    std::cout << "CASES A " << monde_a.nbCases() << " B " << monde_b.nbCases() << std::endl;
    std::cout << "DETECTEES A " << detecteesA << " B " << detecteesB << std::endl;
    std::cout << "FILE MAX " << fileMax << std::endl;
    std::cout << "EN ATTENTE " << file.size() << std::endl;
    return 0;
}
