#include <iostream>
#include <string>
#include <vector>

int main() {
    int K;
    std::cin >> K;

    std::vector<std::string> noms(K);
    std::vector<long long> composantes(K);
    for (int i = 0; i < K; ++i) {
        std::cin >> noms[i] >> composantes[i];
    }

    long long V;
    std::cin >> V;

    // Pas : taille d'un sommet entier, chaque composante est un float de 4 octets
    long long pas = 0;
    for (int i = 0; i < K; ++i) {
        pas += composantes[i] * 4;
    }

    // Décalage : taille de tous les attributs qui précèdent
    long long decalage = 0;
    for (int i = 0; i < K; ++i) {
        std::cout << "ATTRIB " << i << " " << noms[i]
                  << " COMPOSANTES " << composantes[i]
                  << " DECALAGE " << decalage << std::endl;
        decalage += composantes[i] * 4;
    }

    std::cout << "PAS " << pas << std::endl;
    std::cout << "TAMPON " << V * pas << std::endl;

    return 0;
}
