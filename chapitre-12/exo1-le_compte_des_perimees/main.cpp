#include <iostream>
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
    // Crée une ressource : réemploie la case libérée le plus récemment,
    // sinon ajoute une case à la fin.
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

    // Une poignée est bonne si sa génération n'est pas 0, si sa case existe,
    // si elle est occupée et si elle porte la même génération.
    bool valide(const Poignee& h) const {
        if (h.generation == 0) return false;
        if (h.numero < 0 || h.numero >= static_cast<int>(cases_.size())) return false;
        const Case& c = cases_[h.numero];
        return c.occupee && c.generation == h.generation;
    }

    // Détruit avec une poignée bonne ; sinon, rien ne se passe.
    void detruit(const Poignee& h) {
        if (!valide(h)) return;
        Case& c = cases_[h.numero];
        c.occupee = false;
        ++c.generation;
        libres_.push_back(h.numero);   // la plus récemment libérée est en fin
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

int main() {
    int T = 0, O = 0;
    if (!(std::cin >> T >> O)) return 0;

    Reserve reserve;
    // handles[k - 1] : poignée reçue à la création de la texture k, jamais modifiée.
    std::vector<Poignee> handles;
    for (int i = 0; i < T; ++i) {
        std::string nom;
        std::cin >> nom;
        handles.push_back(reserve.cree(nom));
    }

    std::vector<int> objets(O);
    for (int i = 0; i < O; ++i) std::cin >> objets[i];

    int C = 0;
    std::cin >> C;

    long long totalPerimees = 0;
    int images = 0;

    for (int c = 0; c < C; ++c) {
        std::string ordre;
        if (!(std::cin >> ordre)) break;

        if (ordre == "DETRUIRE") {
            int k;
            std::cin >> k;
            if (k >= 1 && k <= static_cast<int>(handles.size())) {
                reserve.detruit(handles[k - 1]);
            }
        } else if (ordre == "CREER") {
            std::string nom;
            std::cin >> nom;
            handles.push_back(reserve.cree(nom));
        } else if (ordre == "VALIDE") {
            int k;
            std::cin >> k;
            bool bonne = k >= 1 && k <= static_cast<int>(handles.size()) &&
                         reserve.valide(handles[k - 1]);
            std::cout << "VALIDE " << k << (bonne ? " OUI" : " NON") << std::endl;
        } else if (ordre == "IMAGE") {
            ++images;
            long long perimees = 0;
            std::string vues;
            for (int i = 0; i < O; ++i) {
                int k = objets[i];
                bool bonne = k >= 1 && k <= static_cast<int>(handles.size()) &&
                             reserve.valide(handles[k - 1]);
                if (bonne) {
                    vues += " " + reserve.nom(handles[k - 1]);
                } else {
                    vues += " MANQUANTE";
                    ++perimees;
                }
            }
            if (O == 0) vues = " AUCUN";
            totalPerimees += perimees;
            std::cout << "IMAGE " << images << " PERIMEES " << perimees
                      << " VUES" << vues << std::endl;
        }
    }

    std::cout << "TOTAL PERIMEES " << totalPerimees << std::endl;
    std::cout << "VIVANTES " << reserve.vivantes() << std::endl;
    return 0;
}