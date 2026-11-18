#include <iostream>

typedef unsigned long long u64;

int main() {
    long long Q = 0;
    if (!(std::cin >> Q) || Q == 0) {
        std::cout << "AUCUN" << std::endl;
        return 0;
    }

    for (long long q = 1; q <= Q; ++q) {
        u64 B, K, R;
        std::cin >> B >> K >> R;

        const u64 M = 1ULL << B;   // la génération compte modulo 2^B

        // La case part à la génération 1 : après K cycles, elle vaut (1 + K) mod M.
        const u64 generation = (1 + K) % M;
        const bool premiereValide = (generation == 1);

        // Cycles j de 1 à K après lesquels la génération vaut 0 : j = M-1, 2M-1, ...
        const u64 nulles = (K + 1) / M;
        // Cycles j de 1 à K après lesquels elle vaut de nouveau 1 : j = M, 2M, ...
        const u64 resurrections = K / M;

        // Parade : une case sert les générations 1 à M-1, soit M-1 poses, et il y a
        // K + 1 poses en tout (la ressource initiale comprise).
        const u64 poses = K + 1;
        const u64 parPose = M - 1;
        const u64 cases = (poses + parPose - 1) / parPose;

        // Jours entiers avant la première résurrection : M / (R * 86400).
        // Si R dépasse M, le quotient est nul : on évite ainsi tout débordement.
        u64 jours = 0;
        if (R <= M) jours = M / (R * 86400ULL);

        std::cout << "REQUETE " << q
                  << " GENERATION " << generation
                  << " PREMIERE " << (premiereValide ? "VALIDE" : "PERIMEE")
                  << " NULLES " << nulles
                  << " RESURRECTIONS " << resurrections
                  << " CASES " << cases
                  << " JOURS " << jours << std::endl;
    }
    return 0;
}