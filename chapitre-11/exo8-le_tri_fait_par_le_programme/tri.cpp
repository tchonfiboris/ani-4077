#include <algorithm>
#include <iostream>
#include <set>
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

    // Un dessin lie le maillage, puis le tableau 0 si D vaut 1.
    void dessine(const Objet& o, bool deliage) {
        lie(TABLEAU, o.m);
        if (deliage) lie(TABLEAU, 0);
    }

    long long utiles() const { return liaisons - inutiles; }
};

int main() {
    int N = 0, D = 0;
    std::string cle;
    if (!(std::cin >> N >> D >> cle)) return 0;

    std::vector<Objet> objets(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> objets[i].nom >> objets[i].p >> objets[i].t >> objets[i].m;
    }
    const bool deliage = (D == 1);
    const bool avecMaillage = (cle == "PTM");

    // Version imbriquée : deux boucles, programme puis texture.
    Compteur imbrique;
    {
        std::set<long long> programmes;
        for (const Objet& o : objets) programmes.insert(o.p);
        for (long long p : programmes) {
            imbrique.lie(PROGRAMME, p);
            std::set<long long> textures;
            for (const Objet& o : objets) {
                if (o.p == p) textures.insert(o.t);
            }
            for (long long t : textures) {
                imbrique.lie(TEXTURE, t);
                for (const Objet& o : objets) {
                    if (o.p == p && o.t == t) imbrique.dessine(o, deliage);
                }
            }
        }
    }

    // Version triée : tri stable par clé, puis un seul parcours.
    std::vector<Objet> tries = objets;
    std::stable_sort(tries.begin(), tries.end(),
                     [&](const Objet& a, const Objet& b) {
                         if (a.p != b.p) return a.p < b.p;
                         if (a.t != b.t) return a.t < b.t;
                         if (avecMaillage) return a.m < b.m;
                         return false;
                     });

    Compteur trie;
    for (std::size_t k = 0; k < tries.size(); ++k) {
        const Objet& o = tries[k];
        bool nouveauProgramme = (k == 0) || tries[k - 1].p != o.p;
        bool nouvelleTexture = nouveauProgramme || tries[k - 1].t != o.t;
        if (nouveauProgramme) trie.lie(PROGRAMME, o.p);
        if (nouvelleTexture) trie.lie(TEXTURE, o.t);
        trie.dessine(o, deliage);
    }

    std::cout << "ORDRE";
    for (const Objet& o : tries) std::cout << " " << o.nom;
    std::cout << std::endl;

    std::cout << "IMBRIQUE LIAISONS " << imbrique.liaisons
              << " UTILES " << imbrique.utiles() << std::endl;
    std::cout << "TRIE LIAISONS " << trie.liaisons
              << " UTILES " << trie.utiles() << std::endl;
    std::cout << "MEME COMPTE "
              << (imbrique.liaisons == trie.liaisons ? "OUI" : "NON") << std::endl;
    std::cout << "UTILES GAGNEES " << (imbrique.utiles() - trie.utiles()) << std::endl;
    return 0;
}
