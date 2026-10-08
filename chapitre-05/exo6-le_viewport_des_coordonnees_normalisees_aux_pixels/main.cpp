#include <iostream>
#include <string>

int main()
{
    long long largeur;
    long long hauteur;
    long long facteur;
    long long vx, vy, vl, vh;
    int n;

    if (!(std::cin >> largeur >> hauteur >> facteur)){
         return 0;
        }
    std::cin >> vx >> vy >> vl >> vh;
    if (!(std::cin >> n)){
         n = 0;
   }
    // Taille physique de la fenêtre (division entière)
    long long W = largeur * facteur / 100;
    long long H = hauteur * facteur / 100;

    int coupes = 0; 
    int hors = 0;

    for (int i = 0; i < n; ++i)
    {
        std::string nom;
        long long x; 
        long long y;
        std::cin >> nom >> x >> y;

        // Coupé : on ne calcule rien d'autre
        if (x < -1000 || x > 1000 || y < -1000 || y > 1000)
        {
            std::cout << nom << " COUPE\n";
            ++coupes;
            continue;
        }

        long long px = vx + (x + 1000) * vl / 2000;
        long long py = vy + (y + 1000) * vh / 2000;

        if (px >= W || py >= H)
        {
            std::cout << nom << " " << px << " " << py << " HORS FENETRE" << std::endl;
            ++hors;
            continue;
        }

        // OpenGL compte depuis le bas, l'écran depuis le haut
        long long ligne = H - 1 - py;
        std::cout << nom << " " << px << " " << py << " " << ligne << std::endl;
    }

    // Couverture du viewport, bornée à la fenêtre
    long long finX = (vx + vl < W) ? vx + vl : W;
    long long finY = (vy + vh < H) ? vy + vh : H;
    long long cl = finX - vx;
    long long ch = finY - vy;
    if (cl < 0){ cl = 0;}
    if (ch < 0){ ch = 0;}

    long long couverture = 0;
    if (W * H != 0)
        couverture = cl * ch * 1000 / (W * H);

    std::cout << "COUPES " << coupes << std::endl;
    std::cout << "HORS " << hors << std::endl;
    std::cout << "COUVERTURE " << couverture << std::endl;
    
    return 0;
}