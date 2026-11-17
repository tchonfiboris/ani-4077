#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Objet {
    std::string nom;
    long long p, t, m;
};

enum Categorie { PROGRAMME = 0, TEXTURE = 1, TABLEAU = 2 };

struct Compteur {
    long long dernier[3];
    long long liaisons;
    long long inutiles;

    Compteur() : liaisons(0), inutiles(0) {
        for (int i = 0; i < 3; ++i) dernier[i] = 0;
    }

    void lie(Categorie cat, long long id) {
        ++liaisons;
        if (id == dernier[cat]) {
            ++inutiles;
        } else {
            dernier[cat] = id;
        }
    }

    // Dessiner lie le maillage, puis le délie si deliage vaut 1.
    void dessine(const Objet& o, bool deliage) {
        lie(TABLEAU, o.m);
        if (deliage) lie(TABLEAU, 0);
    }
};

int main() {
    int N = 0, D = 0;
    if (!(std::cin >> N >> D)) return 0;

    std::vector<Objet> objets(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> objets[i].nom >> objets[i].p >> objets[i].t >> objets[i].m;
    }
    const bool deliage = (D == 1);

    // Ordre de création : programme, texture, dessin pour chaque objet.
    Compteur creation;
    for (int i = 0; i < N; ++i) {
        creation.lie(PROGRAMME, objets[i].p);
        creation.lie(TEXTURE, objets[i].t);
        creation.dessine(objets[i], deliage);
    }

    // Ordre regroupé : programme croissant, puis texture croissante,
    // puis ordre de création à l'intérieur du groupe.
    std::vector<int> ordre(N);
    for (int i = 0; i < N; ++i) ordre[i] = i;
    std::sort(ordre.begin(), ordre.end(), [&](int a, int b) {
        if (objets[a].p != objets[b].p) return objets[a].p < objets[b].p;
        if (objets[a].t != objets[b].t) return objets[a].t < objets[b].t;
        return a < b;
    });

    Compteur regroupe;
    for (int k = 0; k < N; ++k) {
        const Objet& o = objets[ordre[k]];
        bool nouveauProgramme = (k == 0) || objets[ordre[k - 1]].p != o.p;
        bool nouvelleTexture = nouveauProgramme || objets[ordre[k - 1]].t != o.t;
        if (nouveauProgramme) regroupe.lie(PROGRAMME, o.p);
        if (nouvelleTexture) regroupe.lie(TEXTURE, o.t);
        regroupe.dessine(o, deliage);
    }

    // Affichage.
    if (N == 0) {
        std::cout << "ORDRE AUCUN" << std::endl;
    } else {
        std::cout << "ORDRE";
        for (int k = 0; k < N; ++k) std::cout << " " << objets[ordre[k]].nom;
        std::cout << std::endl;
    }

    std::cout << "CREATION LIAISONS " << creation.liaisons
              << " INUTILES " << creation.inutiles << std::endl;
    std::cout << "REGROUPE LIAISONS " << regroupe.liaisons
              << " INUTILES " << regroupe.inutiles << std::endl;

    if (N == 0) {
        std::cout << "ECONOMIE AUCUNE" << std::endl;
    } else {
        long long a = creation.liaisons;
        long long e = a - regroupe.liaisons;
        long long p = e * 100 / a;
        std::cout << "ECONOMIE " << e << " SUR " << a << " SOIT " << p << " %" << std::endl;
    }

    std::cout << "UTILES " << (regroupe.liaisons - regroupe.inutiles) << std::endl;
    return 0;
}