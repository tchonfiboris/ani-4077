#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

int main() {
    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<std::string> noms(n);
    std::vector<long long> lignes(n);
    long long total = 0, commun = 0;

    for (int i = 0; i < n; ++i) {
        std::cin >> noms[i] >> lignes[i];
        total += lignes[i];
        if (noms[i] == "Common") commun += lignes[i];
    }

    // Parts en millièmes : on multiplie avant de diviser
    for (int i = 0; i < n; ++i) {
        long long part = (total == 0) ? 0 : lignes[i] * 1000 / total;
        std::cout << noms[i] << " " << lignes[i] << " " << part << "\n";
    }

    // RAPPORT en centièmes
    long long rapport = (commun == 0) ? 0 : (total - commun) * 100 / commun;

    // MOITIE : on trie une copie, du plus gros au plus petit
    long long moitie = 0;
    if (total > 0) {
        std::vector<long long> tri = lignes;
        std::sort(tri.begin(), tri.end(), std::greater<long long>());
        long long cible = total / 2, somme = 0;
        for (long long v : tri) {
            if (somme >= cible) break;
            somme += v;
            ++moitie;
        }
    }

    std::cout << "TOTAL " << total << "\n";
    std::cout << "RAPPORT " << rapport << "\n";
    std::cout << "MOITIE " << moitie << "\n";
    return 0;
}