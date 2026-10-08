#include <iostream>
#include <string>
#include <vector>

int main()
{
    const char* noms[5] = { "peripherique", "format", "contexte", "courant", "chargement" };

    int e;
    if (!(std::cin >> e)){
         e = 0;}

    long long somme[5] = { 0, 0, 0, 0, 0 };
    for (int i = 0; i < e; ++i)
        for (int k = 0; k < 5; ++k)
        {
            long long d;
            std::cin >> d;
            somme[k] += d;
        }

    long long totalSomme = 0;
    for (int k = 0; k < 5; ++k)
       { totalSomme += somme[k];}

    int plusCher = 0;
    for (int k = 1; k < 5; ++k)
        if (somme[k] > somme[plusCher])   // strict : à égalité, le premier reste
           { plusCher = k;}

    for (int k = 0; k < 5; ++k)
    {
        long long moyenne = (e == 0) ? 0 : somme[k] / e;
        long long part = (totalSomme == 0) ? 0 : somme[k] * 1000 / totalSomme;
        std::cout << noms[k] << " " << moyenne << " " << part << std::endl;
    }

    long long total = (e == 0) ? 0 : totalSomme / e;
    long long images = (total + 16666) / 16667;

    std::cout << "PLUS CHER " << noms[plusCher] << std::endl;
    std::cout << "TOTAL " << total << std::endl;
    std::cout << "IMAGES " << images << std::endl;

    return 0;
}
