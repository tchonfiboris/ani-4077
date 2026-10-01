#include <iostream>
#include <vector>
#include <deque>
#include <string>

struct Resultat {
    long long maxi = 0; 
    long long perdus = 0; 
    long long rattrapage = 0; 
    long long retard = 0;
};

static Resultat simuler(long long c, const std::vector<long long>& arrivees, bool tout) {

    long long n = (long long)arrivees.size();
    std::deque<long long> file;  // image d'arrivée de chaque événement
    Resultat r;
    long long derniere = -1;     // dernière image où quelque chose a été consommé

    for (long long k = 0; ; ++k) {
        // 1 et 2 : arrivées, le plus ancien est retiré si la file est pleine
        if (k < n) {
            for (long long j = 0; j < arrivees[k]; ++j) {
                if ((long long)file.size() == c) {
                    file.pop_front();
                    ++r.perdus;
                }
                file.push_back(k);
            }
        }

        // 3 : taille juste après les arrivées
        r.maxi = std::max(r.maxi, (long long)file.size());

        // 4 et 5 : consommation et retard
        while (!file.empty()) {
            r.retard = std::max(r.retard, k - file.front());
            file.pop_front();
            derniere = k;
            if (!tout) break;  // mode IF : un seul événement
        }

        // 6 : arrêt
        if (k >= n - 1 && file.empty()) 
        break;
    }

    // 7 : rattrapage
    if (derniere >= 0){ 
        r.rattrapage = std::max(0LL, derniere - (n - 1));
        return r;}
}

static void afficher(const std::string& mode, const Resultat& r) {
    std::cout << mode << " MAX " << r.maxi << " PERDUS " << r.perdus
              << " RATTRAPAGE " << r.rattrapage << " RETARD " << r.retard << std::endl;
}
