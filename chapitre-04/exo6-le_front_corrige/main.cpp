#include <iostream>
#include <string>

int main() {

    int n;

    if (!(std::cin >> n)){
         n = 0;}

    bool precedentNaif = false;     // mémoire du détecteur naïf
    bool precedentCorrige = false;  // mémoire du détecteur corrigé
    long long questions = 0; 
    long long fausses = 0; 
    long long montants = 0; 
    long long descendants = 0;

    for (int i = 0; i < n; ++i) {

        int e;
        std::string suite;

        if (!(std::cin >> e >> suite)) 
        break;

        bool etat = (e == 1);

        // Corrigé : une seule mise à jour par image, avant toute question
        bool monte = etat && !precedentCorrige;
        bool descend = !etat && precedentCorrige;
        precedentCorrige = etat;

        if (monte){
             ++montants;}
        if (descend) {
            ++descendants;}

        for (char q : suite) {

            if (q != 'M' && q != 'D') 
            continue;  // '-' : aucune question

            // Naïf : répond puis écrit sa mémoire, à chaque question
            bool naif;
            if (q == 'M') {
                naif = etat && !precedentNaif;}
            else          {
                naif = !etat && precedentNaif;}
            precedentNaif = etat;

            bool corrige = (q == 'M') ? monte : descend;

            ++questions;
            if (naif != corrige) {
                ++fausses;}

            std::cout << i << " " << q << " "
                      << (naif ? "OUI" : "NON") << " "
                      << (corrige ? "OUI" : "NON") << " "
                      << (naif == corrige ? "JUSTE" : "FAUX") << std::endl;
        }
    }

    std::cout << "QUESTIONS " << questions << std::endl;
    std::cout << "FAUSSES " << fausses << std::endl;
    std::cout << "MONTANTS " << montants << std::endl;
    std::cout << "DESCENDANTS " << descendants << std::endl;

    return 0;
}
