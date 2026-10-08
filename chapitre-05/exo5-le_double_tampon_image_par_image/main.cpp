#include <iostream>
#include <string>
#include <vector>

struct Tampon
{
    std::vector<std::string> elements{ "noir" };
    bool complet = true;
};

std::string contenu(const Tampon& t)
{
    std::string s;
    for (std::size_t i = 0; i < t.elements.size(); ++i)
    {
        if (i > 0) s += "+";
        s += t.elements[i];
    }
    return s;
}

int main()
{
    std::string mode;
    long long largeur; 
    long long hauteur; 
    long long bits;
    int n;
    if (!(std::cin >> mode >> largeur >> hauteur >> bits)){
         return 0;
        }
    if (!(std::cin >> n)){
         n = 0;
        }

    bool dbl = (mode == "DOUBLE");
    long long memoire = largeur * hauteur * bits / 8;
    if (dbl){
         memoire = memoire * 2;
        }

    Tampon buffer[2];
    int dessin = 0;              // tampon de dessin (derrière)
    int montre = dbl ? 1 : 0;    // tampon montré (devant)
    int incompletes = 0;

    std::cout << "MEMOIRE " << memoire << std::endl;

    for (int i = 0; i < n; ++i)
    {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "EFFACER")
        {
            std::string couleur;
            std::cin >> couleur;
            buffer[dessin].elements.clear();
            buffer[dessin].elements.push_back(couleur);
            buffer[dessin].complet = false;
        }
        else if (cmd == "DESSINER")
        {
            std::string objet;
            std::cin >> objet;
            buffer[dessin].elements.push_back(objet);
            buffer[dessin].complet = false;
        }
        else if (cmd == "ECHANGER")
        {
            buffer[dessin].complet = true;
            if (dbl)
            {
                int tmp = dessin;
                dessin = montre;
                montre = tmp;
            }
        }
        else if (cmd == "AFFICHER")
        {
            const Tampon& t = buffer[montre];
            std::cout << "ECRAN " << contenu(t) << " "
                      << (t.complet ? "COMPLETE" : "INCOMPLETE") << std::endl;
            if (!t.complet){
                 ++incompletes;
                }
        }
    }

    std::cout << "INCOMPLETES " << incompletes << std::endl;

    return 0;
}