#include <string>

// tableau de caractere survivent a leur copie
static const std::string GARDES[] = {
    "hwnd", "hinstance", "nativeWindow", "view", "metalLayer",
    "display", "surface", "width", "height", "dpi"
};

// tableau de caractere ephemere
static const std::string EPHEMERES[] = {
    "hdc", "contexteCourant", "pointeurDePixels", "verrouDeSurface"
};

 // fonction booleene  qui prend en parametre le verdict, la taille, le champ 
static bool contient(const std::string tab[], int taille, const std::string& nom) {
    for (int i = 0; i < taille; ++i) {
        if (tab[i] == nom){
            return true;}
    }
    return false;
}
