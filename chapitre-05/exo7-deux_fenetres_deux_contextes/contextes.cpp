#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Fenetre
{
    std::string nom;
    std::string couleur = "noir";
    int effacements = 0;
};

struct Contexte
{
    int fenetre;                    // indice dans le tableau des fenêtres
    std::string couleur = "noir";   // couleur d'effacement rangée dans ce contexte
};

int main()
{
    int n;
    if (!(std::cin >> n)){
         n = 0;
        }

    std::vector<Fenetre> fenetres;            // dans l'ordre de création
    std::map<std::string, Contexte> contextes;
    std::string courant = "";                 // vide = aucun contexte courant
    int ignores = 0;

    for (int i = 0; i < n; ++i)
    {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "CREER")
        {
            std::string ctx; 
            std::string fen;
            std::cin >> ctx >> fen;
            if (contextes.count(ctx))
            {
                ++ignores;
            }
            else
            {
                Fenetre f;
                f.nom = fen;
                fenetres.push_back(f);
                Contexte c;
                c.fenetre = (int)fenetres.size() - 1;
                contextes[ctx] = c;
            }
        }
        else if (cmd == "COURANT")
        {
            std::string ctx;
            std::cin >> ctx;
            if (ctx == "AUCUN")
                courant = "";
            else if (!contextes.count(ctx))
                ++ignores;
            else
                courant = ctx;
        }
        else if (cmd == "COULEUR")
        {
            std::string couleur;
            std::cin >> couleur;
            if (courant.empty())
                ++ignores;
            else
                contextes[courant].couleur = couleur;   // range seulement, ne dessine rien
        }
        else if (cmd == "EFFACER")
        {
            if (courant.empty())
            {
                ++ignores;
            }
            else
            {
                Contexte& c = contextes[courant];
                Fenetre& f = fenetres[c.fenetre];
                f.couleur = c.couleur;
                ++f.effacements;
            }
        }
    }

    for (std::size_t i = 0; i < fenetres.size(); ++i)
        std::cout << fenetres[i].nom << " " << fenetres[i].couleur
                  << " " << fenetres[i].effacements << std::endl;
    std::cout << "IGNORES " << ignores << std::endl;

    return 0;
}