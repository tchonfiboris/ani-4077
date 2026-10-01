#include <iostream>
#include <vector>

int main() {

    int k;

    if (!(std::cin >> k)) {
        k = 0;}

    std::vector<long long> durees;

    for (int i = 0; i < k; ++i) {
        long long t;

        if (!(std::cin >> t)) 
        break;
        durees.push_back(t);
    }

    int m;

    if (!(std::cin >> m)) {
        m = 0;}

    std::vector<long long> debut; 
    std::vector<long long> fin;

    for (int i = 0; i < m; ++i) {
        long long a; 
        long long b;

        if (!(std::cin >> a >> b)) 
        break;
        debut.push_back(a);
        fin.push_back(b);
    }

    m = (int)debut.size();

    long long pireDuree = -1; 
    long long pirePerdus = 0;

    for (long long t : durees) {
        long long etat = 0; 
        long long fronts = 0;
        long long derniereLecture = -2;  // indice de la dernière lecture pressée

        for (int i = 0; i < m; ++i) {

            long long premiere = (debut[i] + t - 1) / t;  // première lecture >= debut

            if (premiere * t >= fin[i]) 
            continue;          // aucune lecture dans le clic

            ++etat;
            long long derniere = (fin[i] + t - 1) / t - 1;  // dernière lecture < fin

            // Nouveau front si la lecture précédente n'était pas pressée
            if (premiere > derniereLecture + 1) {
                ++fronts;}
            derniereLecture = derniere;
        }

        long long perdus = m - etat;
        
        std::cout << "PERIODE " << t << " FILE " << m << " ETAT " << etat
                  << " FRONTS " << fronts << " PERDUS " << perdus <<  std::endl;

        if (perdus > pirePerdus) {  // strict : à égalité, la première lue reste
            pirePerdus = perdus;
            pireDuree = t;
        }
    }

    if (pireDuree < 0) {
        std::cout << "PIRE AUCUN" <<  std::endl;}
    else               {
        std::cout << "PIRE " << pireDuree <<  std::endl;}

    return 0;
}
