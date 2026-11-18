#include <iostream>
#include <string>
#include <vector>

static bool estEspace(char c) { return c == ' ' || c == '\t' || c == '\r'; }

static bool estMotChar(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') || c == '_';
}

// Un mot est interdit s'il contient GL_, Camera, Scene, ou gl suivi d'une
// majuscule de A à Z.
static bool estInterdit(const std::string& mot) {
    if (mot.find("GL_") != std::string::npos) return true;
    if (mot.find("Camera") != std::string::npos) return true;
    if (mot.find("Scene") != std::string::npos) return true;
    for (std::size_t i = 0; i + 2 < mot.size(); ++i) {
        if (mot[i] == 'g' && mot[i + 1] == 'l' && mot[i + 2] >= 'A' && mot[i + 2] <= 'Z')
            return true;
    }
    return false;
}

int main() {
    std::string ligne;
    int N = 0;
    if (std::getline(std::cin, ligne) && !ligne.empty()) N = std::stoi(ligne);

    bool dansBloc = false;   // dans un commentaire /* ... */, parfois sur plusieurs lignes
    int lignesDeCode = 0;
    std::vector<std::string> interdits;

    for (int n = 1; n <= N; ++n) {
        if (!std::getline(std::cin, ligne)) ligne.clear();

        // Retire les commentaires : le code de la ligne est ce qui reste.
        std::string code;
        std::size_t i = 0;
        while (i < ligne.size()) {
            if (dansBloc) {
                if (ligne[i] == '*' && i + 1 < ligne.size() && ligne[i + 1] == '/') {
                    dansBloc = false;
                    i += 2;
                } else {
                    ++i;
                }
            } else if (ligne[i] == '/' && i + 1 < ligne.size() && ligne[i + 1] == '*') {
                dansBloc = true;
                code += ' ';          // un commentaire compte comme une espace
                i += 2;
            } else if (ligne[i] == '/' && i + 1 < ligne.size() && ligne[i + 1] == '/') {
                break;                // le reste de la ligne est un commentaire
            } else {
                code += ligne[i];
                ++i;
            }
        }

        bool aDuCode = false;
        for (char c : code) {
            if (!estEspace(c)) {
                aDuCode = true;
                break;
            }
        }
        if (aDuCode) ++lignesDeCode;

        // Découpe le code en mots et cherche les mots interdits.
        std::size_t k = 0;
        while (k < code.size()) {
            if (!estMotChar(code[k])) {
                ++k;
                continue;
            }
            std::size_t debut = k;
            while (k < code.size() && estMotChar(code[k])) ++k;
            std::string mot = code.substr(debut, k - debut);
            if (estInterdit(mot)) {
                std::cout << "LIGNE " << n << " " << mot << std::endl;
                interdits.push_back(mot);
            }
        }
    }

    std::cout << "LIGNES DE CODE " << lignesDeCode << std::endl;
    std::cout << "INTERDITS " << interdits.size() << std::endl;
    std::cout << "VERDICT " << (interdits.empty() ? "PROPRE" : "REFUSE") << std::endl;
    return 0;
}