#include <algorithm>
#include <iostream>
#include <vector>

// Résultat du comptage en ordre regroupé pour une scène de n objets.
struct Cout {
    long long liaisons;
    long long utiles;
};

static long long pgcd(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

struct Scene {
    long long S, T, G;
    int D;

    // Ordre de création : 3 liaisons par objet (programme, texture, tableau)
    // plus le déliage éventuel.
    long long creation(long long n) const { return n * (3 + D); }

    // Ordre regroupé, calculé sans fabriquer les objets un par un.
    Cout regroupe(long long n) const {
        if (n == 0) return {0, 0};

        const long long NG = (n + G - 1) / G;           // groupes utilisés
        const long long lastLen = n - (NG - 1) * G;     // taille du dernier groupe
        const long long nbProg = NG < S ? NG : S;       // programmes utilisés

        // Les départs de groupe d'un même programme se répètent avec la période P.
        const long long pas = (S % T) * (G % T) % T;
        const long long P = T / pgcd(pas, T);

        long long liaisons = nbProg;   // une liaison par programme utilisé
        long long utiles = nbProg;     // des identifiants croissants, donc utiles
        long long precedentMax = -1;

        std::vector<long long> diff(T + 1);
        for (long long q = 0; q < nbProg; ++q) {
            const long long K = (NG - q + S - 1) / S;   // groupes de ce programme
            std::fill(diff.begin(), diff.end(), 0);

            auto marque = [&](long long g, long long len) {
                if (len >= T) {
                    diff[0] += 1;
                    diff[T] -= 1;
                    return;
                }
                long long s = (g * G) % T;
                if (s + len <= T) {
                    diff[s] += 1;
                    diff[s + len] -= 1;
                } else {
                    diff[s] += 1;
                    diff[T] -= 1;
                    diff[0] += 1;
                    diff[s + len - T] -= 1;
                }
            };

            const long long limite = K < P ? K : P;
            for (long long k = 0; k < limite; ++k) {
                long long g = q + k * S;
                marque(g, g == NG - 1 ? lastLen : G);
            }
            if (K - 1 >= limite) {   // le dernier groupe peut être partiel
                long long g = q + (K - 1) * S;
                marque(g, g == NG - 1 ? lastLen : G);
            }

            long long compte = 0, mini = -1, maxi = -1, courant = 0;
            for (long long r = 0; r < T; ++r) {
                courant += diff[r];
                if (courant > 0) {
                    ++compte;
                    if (mini < 0) mini = r;
                    maxi = r;
                }
            }

            liaisons += compte;
            utiles += compte;
            // Même texture que la dernière du programme précédent : inutile.
            if (q > 0 && mini == precedentMax) {
                --utiles;
            }
            precedentMax = maxi;
        }

        // Tableau : un dessin lie le maillage 1, puis le tableau 0 si D vaut 1.
        liaisons += n * (1 + D);
        utiles += (D == 1) ? 2 * n : 1;

        return {liaisons, utiles};
    }
};

int main() {
    Scene sc;
    long long B = 0, Q = 0;
    if (!(std::cin >> sc.S >> sc.T >> sc.G >> sc.D >> B >> Q)) return 0;

    for (long long i = 0; i < Q; ++i) {
        long long n;
        std::cin >> n;
        Cout c = sc.regroupe(n);
        std::cout << "OBJETS " << n
                  << " CREATION " << sc.creation(n)
                  << " REGROUPE " << c.liaisons
                  << " UTILES " << c.utiles << std::endl;
    }

    // Plus grande scène tenant dans le budget, pour chaque ordre.
    long long maxCreation = B / (3 + sc.D);

    // Le coût regroupé ne baisse jamais quand n grandit : recherche dichotomique.
    // Il vaut au moins n * (1 + D), ce qui borne n.
    long long lo = 0, hi = B / (1 + sc.D);
    while (lo < hi) {
        long long milieu = lo + (hi - lo + 1) / 2;
        if (sc.regroupe(milieu).liaisons <= B) lo = milieu;
        else hi = milieu - 1;
    }

    std::cout << "MAX CREATION " << maxCreation << std::endl;
    std::cout << "MAX REGROUPE " << lo << std::endl;
    return 0;
}