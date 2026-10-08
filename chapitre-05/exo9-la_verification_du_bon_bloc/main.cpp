#include <iostream>
#include <string>
#include <vector>

struct Bloc
{
    std::string nom;
    std::string symbole;
    std::vector<std::string> macros;
};

int main()
{
    int b;
    if (!(std::cin >> b)){ 
        b = 0;}

    std::vector<Bloc> blocs(b);
    for (int i = 0; i < b; ++i)
    {
        int k;
        std::cin >> blocs[i].nom >> blocs[i].symbole >> k;
        blocs[i].macros.resize(k);
        for (int j = 0; j < k; ++j)
           { std::cin >> blocs[i].macros[j];}
    }

    int t;
    if (!(std::cin >> t)){
         t = 0;}

    int bons = 0;
    int mauvais = 0;

    for (int i = 0; i < t; ++i)
    {
        std::string cible; 
        std::string attendu;
        int d;
        std::cin >> cible >> attendu >> d;

        std::vector<std::string> definies(d);
        for (int j = 0; j < d; ++j)
            std::cin >> definies[j];

        // Par défaut : le #else final
        std::string nomPris = "REFUS";
        std::string symbolePris = "AUCUN";

        bool pris = false;
        for (int x = 0; x < b && !pris; ++x)
        {
            for (std::size_t m = 0; m < blocs[x].macros.size() && !pris; ++m)
            {
                for (int y = 0; y < d; ++y)
                {
                    if (blocs[x].macros[m] == definies[y])   // comparaison exacte
                    {
                        pris = true;
                        nomPris = blocs[x].nom;
                        symbolePris = blocs[x].symbole;
                        break;
                    }
                }
            }
        }

        bool bon = (nomPris == attendu);
        if (bon) {
            ++bons;} 
            else {
                ++mauvais;}

        std::cout << cible << " " << nomPris << " " << symbolePris << " "
                  << (bon ? "BON BLOC" : "MAUVAIS BLOC") << std::endl;
    }

    std::cout << "BONS " << bons << std::endl;
    std::cout << "MAUVAIS " << mauvais << std::endl;
    
    return 0;
}