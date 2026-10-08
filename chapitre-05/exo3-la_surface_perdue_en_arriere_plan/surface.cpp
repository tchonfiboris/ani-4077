#include <iostream>
#include <string>
#include <vector>

struct Evt { 
    int t; 
    std::string nom; 
};

void jouer(const std::vector<Evt>& evts, bool corrige)
{
    bool vivante = true;
    int numero = 0;        // numéro de la surface actuelle
    bool attache = true;   // le programme est attaché au départ
    int numAttache = 0;    // numéro de la surface à laquelle il est attaché
    int images = 0; 
    int erreurs = 0; 
    int sommeils = 0; 
    int rattachements = 0;

    for (const Evt& e : evts)
    {
        if (e.nom == "PERTE")
        {
            vivante = false;
        }
        else if (e.nom == "RETOUR")
        {
            vivante = true;
            ++numero;
        }
        else if (e.nom == "IMAGE")
        {
            bool bonne = vivante && numero == numAttache;
            if (!corrige)
            {
                if (bonne) ++images; else ++erreurs;
            }
            else if (!attache)
            {
                ++sommeils;
            }
            else if (bonne)
            {
                ++images;
            }
            else
            {
                ++erreurs;
                attache = false;
            }
        }
        else if (corrige && e.nom == "CACHEE")
        {
            attache = false;
        }
        else if (corrige && e.nom == "MONTREE")
        {
            if (!attache && vivante)
            {
                attache = true;
                numAttache = numero;
                ++rattachements;
            }
        }
    }

    std::cout << (corrige ? "MODE CORRIGE" : "MODE NAIF") << std::endl;
    std::cout << "IMAGES " << images << std::endl;
    std::cout << "ERREURS " << erreurs << std::endl;
    std::cout << "SOMMEILS " << sommeils << std::endl;
    std::cout << "RATTACHEMENTS " << rattachements << std::endl;
}

int main()
{
    int n;
    if (!(std::cin >> n)){ 
        n = 0;
    }
    std::vector<Evt> evts(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> evts[i].t >> evts[i].nom;
    }

    jouer(evts, false);
    jouer(evts, true);

    return 0;
}