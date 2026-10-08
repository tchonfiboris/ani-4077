#include <iostream>
#include <string>
#include <vector>

struct Format { 
    int numero; 
    int c; 
    int p; 
    int s; 
    int d; 
};

const char* etat(int demande, int offert)
{
    if (offert == demande) return "EXACT";
    if (offert < demande) return "RABOTE";
    return "PLUS";
}

int main()
{
    int dc; 
    int dp; 
    int ds; 
    int dd;
    if (!(std::cin >> dc >> dp >> ds >> dd)){
         return 0;
        }

    int n;
    if (!(std::cin >> n)){
         n = 0;
        }

    bool trouve = false;
    Format best{};
    int bestManque = 0; 
    int bestExces = 0;

    for (int i = 0; i < n; ++i)
    {
        Format f;
        std::cin >> f.numero >> f.c >> f.p >> f.s >> f.d;
        if (f.d != dd) continue; // le double tampon ne se négocie pas

        int dem[3] = { dc, dp, ds };
        int off[3] = { f.c, f.p, f.s };
        int manque = 0; 
        int exces = 0;
        for (int k = 0; k < 3; ++k)
        {
            if (off[k] < dem[k]) {
                manque += dem[k] - off[k];
            }
            else{
                exces  += off[k] - dem[k];
            }
        }

        bool meilleur = !trouve || manque < bestManque  || (manque == bestManque && exces < bestExces) || (manque == bestManque && exces == bestExces && f.numero < best.numero);

        if (meilleur)
        {
            trouve = true;
            best = f;
            bestManque = manque;
            bestExces = exces;
        }
    }

    if (!trouve)
    {
        std::cout << "AUCUN FORMAT" << std::endl;
        return 0;
    }

    int rabotes = 0;
    if (best.c < dc) ++rabotes;
    if (best.p < dp) ++rabotes;
    if (best.s < ds) ++rabotes;

    std::cout << "FORMAT " << best.numero << std::endl;
    std::cout << "couleur "    << dc << " " << best.c << " " << etat(dc, best.c) << std::endl;
    std::cout << "profondeur " << dp << " " << best.p << " " << etat(dp, best.p) << std::endl;
    std::cout << "pochoir "    << ds << " " << best.s << " " << etat(ds, best.s) << std::endl;
    std::cout << "RABOTES " << rabotes << std::endl;
    
    return 0;
}