#include <iostream>

int main() {
    long long T, M;
    std::cin >> T >> M;

    // Niveau maximum : log2(T), le dernier niveau a pour côté 1
    int niveauMax = 0;
    for (long long c = T; c > 1; c /= 2) {
        ++niveauMax;
    }

    long long scintillent = 0;

    for (long long i = 0; i < M; ++i) {
        long long S;
        std::cin >> S;

        // Plus grand d dans [0, niveauMax] dont le côté est encore >= S
        int d = 0;
        long long cote = T;
        while (d < niveauMax && cote / 2 >= S) {
            cote /= 2;
            ++d;
        }

        // Sans mipmaps : un pixel couvre r x r texels et n'en lit qu'un
        long long k = 1;
        if (S < T) {
            long long r = T / S;
            k = r * r;
        }
        if (k > 1) {
            ++scintillent;
        }

        std::cout << "ECRAN " << S << " NIVEAU " << d
                  << " COTE " << cote << " UN SUR " << k << std::endl;
    }

    std::cout << "NIVEAU MAX " << niveauMax << std::endl;
    std::cout << "SCINTILLENT " << scintillent << std::endl;

    return 0;
}