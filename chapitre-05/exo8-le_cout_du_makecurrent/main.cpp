#include <iostream>
#include <set>
#include <string>

int main()
{
    long long coutChange; 
    long long coutMeme; 
    long long budget;
    int n;

    if (!(std::cin >> coutChange >> coutMeme >> budget)){
         return 0;
        }
    if (!(std::cin >> n)){
         n = 0;}

    std::set<std::string> distincts;
    std::string precedent = "";
    long long changements = 0;

    for (int i = 0; i < n; ++i)
    {
        std::string ctx;
        std::cin >> ctx;
        distincts.insert(ctx);

        // La première commande compte toujours (precedent est vide au départ)
        if (i == 0 || ctx != precedent)
            ++changements;
        precedent = ctx;
    }

    long long redondants = n - changements;
    long long naif       = changements * coutChange + redondants * coutMeme;
    long long prudent    = changements * coutChange;
    long long regroupe   = (long long)distincts.size() * coutChange;

    // Budget en nanosecondes : budget (µs) * 1000
    long long budgetNs = budget * 1000;
    long long part = naif * 1000 / budgetNs;

    // Plus petit k tel que k * coutChange * 100 >= budget * 1000
    long long cible = budget * 1000;
    long long unite = coutChange * 100;
    long long seuil = (cible + unite - 1) / unite;   // division arrondie vers le haut

    std::cout << "CHANGEMENTS " << changements << std::endl;
    std::cout << "REDONDANTS " << redondants << std::endl;
    std::cout << "NAIF " << naif << std::endl;
    std::cout << "PRUDENT " << prudent << std::endl;
    std::cout << "REGROUPE " << regroupe << std::endl;
    std::cout << "PART " << part << std::endl;
    std::cout << "SEUIL " << seuil << std::endl;
    
    return 0;
}