#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {

    long long duree;
    int f;
    
    if (!(std::cin >> duree >> f)) return 0;
    if (f < 0) f = 0;

    int e;
    if (!(std::cin >> e)) e = 0;

    std::vector<long long> temps(e);
    std::vector<std::string> types(e);
    int lus = 0;
    for (int i = 0; i < e; ++i) {
        if (!(std::cin >> temps[i] >> types[i])) break;
        ++lus;
    }
    e = lus;

    int k;

    if (!(std::cin >> k)) k = 0;
    std::vector<std::string> chaine;
    for (int i = 0; i < k; ++i) {
        std::string t;
        if (!(std::cin >> t)) break;
        chaine.push_back(t);
    }
    k = (int)chaine.size();

    // Rangement dans les images
    std::vector<long long> parImage(f, 0);
    for (int i = 0; i < e; ++i) {
        if (duree > 0) {
            long long img = temps[i] / duree;
            if (img >= 0 && img < f) ++parImage[img];
        }
    }

    long long vides = 0; 
    long long une = 0; 
    long long plusieurs = 0; 
    long long maxi = 0;

    for (int i = 0; i < f; ++i) {
        long long c = parImage[i];
        if (c == 0) ++vides;
        else if (c == 1) ++une;
        else ++plusieurs;
        if (c > maxi) maxi = c;
    }

    // Fréquence de chaque type de la chaîne, et coût avec la chaîne donnée
    std::vector<long long> freq(k, 0);
    long long absents = 0;      // événements dont le type n'est pas dans la chaîne
    long long comparaisons = 0;

    for (int i = 0; i < e; ++i) {
        int pos = -1;
        for (int j = 0; j < k; ++j) {
            if (chaine[j] == types[i]) { pos = j; break; }
        }
        if (pos < 0) {
            ++absents;
            comparaisons += k;       // tous les tests échouent
        } else {
            ++freq[pos];
            comparaisons += pos + 1;
        }
    }

    // Chaîne triée : plus fréquent d'abord, égalités dans l'ordre de départ
    std::vector<int> ordre(k);

    for (int i = 0; i < k; ++i) ordre[i] = i;
    std::stable_sort(ordre.begin(), ordre.end(),
                     [&](int a, int b) { return freq[a] > freq[b]; });

    long long triees = absents * k;
    for (int p = 0; p < k; ++p) {
        triees += freq[ordre[p]] * (p + 1);
    }

    std::cout << "VIDES " << vides << std::endl;
    std::cout << "UNE " << une << std::endl;
    std::cout << "PLUSIEURS " << plusieurs << std::endl;
    std::cout << "MAX " << maxi << std::endl;
    std::cout << "TOTAL " << e << std::endl;
    std::cout << "COMPARAISONS " << comparaisons << std::endl;
    std::cout << "COMPARAISONS TRIEES " << triees << std::endl;
    std::cout << "ORDRE";
    if (k == 0) {
        std::cout << " AUCUN";
    } else {
        for (int p = 0; p < k; ++p) 
        std::cout << " " << chaine[ordre[p]];
    }
    std::cout << std::endl;

    return 0;
}
