#include <iostream>
#include <map>
#include <string>

// Espace de couleur : LINEAIRE si le mot après le dernier souligné
// est une donnée (pas une couleur), SRGB sinon.
std::string espaceDe(const std::string& nom) {
    std::size_t pos = nom.rfind('_');
    if (pos == std::string::npos) {
        return "SRGB";
    }
    std::string mot = nom.substr(pos + 1);
    if (mot == "normal" || mot == "rugosite" || mot == "hauteur" ||
        mot == "metal" || mot == "occlusion") {
        return "LINEAIRE";
    }
    return "SRGB";
}

int main() {
    int N;
    std::cin >> N;

    std::map<std::string, int> refs;  // nom -> nombre de références
    int creations = 0, reutilisations = 0, srgb = 0, lineaires = 0;

    for (int i = 0; i < N; ++i) {
        std::string cmd, nom;
        std::cin >> cmd >> nom;

        if (cmd == "DEMANDE") {
            auto it = refs.find(nom);
            if (it != refs.end()) {
                ++it->second;
                ++reutilisations;
                std::cout << "REUTILISE " << nom << " REFS " << it->second << "\n";
            } else {
                std::string e = espaceDe(nom);
                refs[nom] = 1;
                ++creations;
                if (e == "SRGB") ++srgb; else ++lineaires;
                std::cout << "CREE " << nom << " ESPACE " << e << " REFS 1\n";
            }
        } else if (cmd == "RENDS") {
            auto it = refs.find(nom);
            if (it == refs.end()) {
                std::cout << "RENDS " << nom << " INCONNU\n";
            } else {
                --it->second;
                if (it->second == 0) {
                    refs.erase(it);
                    std::cout << "DETRUIT " << nom << "\n";
                } else {
                    std::cout << "RENDS " << nom << " REFS " << it->second << "\n";
                }
            }
        }
    }

    std::cout << "CREATIONS " << creations << "\n";
    std::cout << "REUTILISATIONS " << reutilisations << "\n";
    std::cout << "VIVANTES " << refs.size() << "\n";
    std::cout << "SRGB " << srgb << "\n";
    std::cout << "LINEAIRES " << lineaires << "\n";

    return 0;
}
