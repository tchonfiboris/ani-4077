#include <iostream>
#include <string>
#include <vector>

// Coûts supposés (en nanosecondes) d'une machine : hypothèses, pas des mesures.
struct Machine {
    std::string nom;
    long long cp, ct, ca, cd;
};

// Nombre de liaisons et de dessins d'un ordre de dessin.
struct Ordre {
    long long p, t, a, d;

    long long liaisons() const { return p + t + a; }

    long long temps(const Machine& m) const {
        return p * m.cp + t * m.ct + a * m.ca + d * m.cd;
    }
};

// Pourcentage entier de (avant - apres) / avant, 0 si avant vaut 0.
static long long economie(long long avant, long long apres) {
    if (avant == 0) return 0;
    return (avant - apres) * 100 / avant;
}

int main() {
    int K = 0;
    if (!(std::cin >> K)) return 0;

    std::vector<Machine> machines(K);
    for (int i = 0; i < K; ++i) {
        std::cin >> machines[i].nom >> machines[i].cp >> machines[i].ct
                 >> machines[i].ca >> machines[i].cd;
    }

    std::string etiquette;
    Ordre creation{0, 0, 0, 0}, regroupe{0, 0, 0, 0};
    std::cin >> etiquette >> creation.p >> creation.t >> creation.a >> creation.d;
    std::cin >> etiquette >> regroupe.p >> regroupe.t >> regroupe.a >> regroupe.d;

    const long long x = creation.liaisons();
    const long long y = regroupe.liaisons();
    const long long e = economie(x, y);

    std::cout << "LIAISONS CREATION " << x << " REGROUPE " << y
              << " ECONOMIE " << e << " %" << std::endl;

    for (const Machine& m : machines) {
        const long long tc = creation.temps(m);
        const long long tr = regroupe.temps(m);
        const long long f = economie(tc, tr);
        std::cout << m.nom << " CREATION " << tc << " REGROUPE " << tr
                  << " ECONOMIE " << f << " % ECART " << (f - e) << std::endl;
    }
    return 0;
}
