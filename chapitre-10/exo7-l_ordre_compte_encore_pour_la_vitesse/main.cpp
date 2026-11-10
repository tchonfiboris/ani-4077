#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Objet {
    char c;
    long long x, y, l, h;
    int z;
};

struct Resultat {
    long long nuanceur = 0;
    long long rejetes = 0;
    long long couverts = 0;
};

// Dessine les objets dans l'ordre donné, sur une grille neuve :
// profondeur 100 partout, test allumé, fonction LESS.
Resultat dessiner(const std::vector<Objet>& objets, int W, int H) {
    std::vector<std::vector<int>> profondeur(H, std::vector<int>(W, 100));
    std::vector<std::vector<char>> passe(H, std::vector<char>(W, 0));
    Resultat r;

    for (const auto& o : objets) {
        // Ce qui sort de la grille est ignoré.
        long long x0 = std::max(0LL, o.x), x1 = std::min((long long)W, o.x + o.l);
        long long y0 = std::max(0LL, o.y), y1 = std::min((long long)H, o.y + o.h);

        for (long long py = y0; py < y1; ++py) {
            for (long long px = x0; px < x1; ++px) {
                if (o.z < profondeur[py][px]) {
                    ++r.nuanceur;  // le nuanceur travaille
                    profondeur[py][px] = o.z;
                    passe[py][px] = 1;
                } else {
                    ++r.rejetes;  // jeté avant le nuanceur
                }
            }
        }
    }

    for (int py = 0; py < H; ++py)
        for (int px = 0; px < W; ++px)
            if (passe[py][px]) ++r.couverts;

    return r;
}

int main() {
    int W, H, N;
    std::cin >> W >> H >> N;

    std::vector<Objet> donne(N);
    for (auto& o : donne) std::cin >> o.c >> o.x >> o.y >> o.l >> o.h >> o.z;

    if (N == 0) {
        std::cout << "AUCUN" << std::endl;
        return 0;
    }

    // Tris stables : à z égal, l'ordre de lecture est gardé.
    std::vector<Objet> proche = donne, loin = donne;
    std::stable_sort(proche.begin(), proche.end(),
                     [](const Objet& a, const Objet& b) { return a.z < b.z; });
    std::stable_sort(loin.begin(), loin.end(),
                     [](const Objet& a, const Objet& b) { return a.z > b.z; });

    Resultat rd = dessiner(donne, W, H);
    Resultat rp = dessiner(proche, W, H);
    Resultat rl = dessiner(loin, W, H);

    const char* noms[3] = {"DONNE", "PROCHE_DABORD", "LOIN_DABORD"};
    Resultat res[3] = {rd, rp, rl};

    for (int i = 0; i < 3; ++i)
        std::cout << noms[i] << " NUANCEUR " << res[i].nuanceur
                  << " REJETES " << res[i].rejetes << std::endl;

    // MEILLEUR : plus petit NUANCEUR, égalité → premier dans l'ordre d'affichage.
    int meilleur = 0;
    for (int i = 1; i < 3; ++i)
        if (res[i].nuanceur < res[meilleur].nuanceur) meilleur = i;

    // COUVERTS et GASPILLES se calculent sur DONNE.
    std::cout << "COUVERTS " << rd.couverts << std::endl;
    std::cout << "MEILLEUR " << noms[meilleur] << std::endl;
    std::cout << "GASPILLES " << rd.nuanceur - rd.couverts << std::endl;
    return 0;
}