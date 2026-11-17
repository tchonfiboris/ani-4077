#include <iostream>
#include <string>

static bool estMaj(char c) { return c >= 'A' && c <= 'Z'; }

static bool estMotChar(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') || c == '_';
}

// Vrai si la chaîne contient un nom OpenGL (glX... ou GL_...) en début de mot.
static bool contientNomGL(const std::string& s) {
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (i > 0 && estMotChar(s[i - 1])) continue;
        if (i + 2 < s.size() && s[i] == 'g' && s[i + 1] == 'l' && estMaj(s[i + 2]))
            return true;
        if (i + 2 < s.size() && s[i] == 'G' && s[i + 1] == 'L' && s[i + 2] == '_')
            return true;
    }
    return false;
}

static void retirerCR(std::string& s) {
    if (!s.empty() && s.back() == '\r') s.pop_back();
}

int main() {
    std::string ligne;
    if (!std::getline(std::cin, ligne)) return 0;
    retirerCR(ligne);
    int F = ligne.empty() ? 0 : std::stoi(ligne);

    long long entLignes = 0, entGL = 0, srcLignes = 0, srcGL = 0, cachees = 0;
    std::string plusLourd = "AUCUN";
    long long meilleur = 0;

    for (int f = 0; f < F; ++f) {
        if (!std::getline(std::cin, ligne)) break;
        retirerCR(ligne);
        // "FICHIER nom K"
        std::size_t dernier = ligne.rfind(' ');
        int K = std::stoi(ligne.substr(dernier + 1));
        std::string nom = ligne.substr(8, dernier - 8);

        long long g = 0, r = 0;
        for (int i = 0; i < K; ++i) {
            std::string l;
            std::getline(std::cin, l);
            retirerCR(l);
            std::size_t pos = l.find("//");
            bool juste = contientNomGL(pos == std::string::npos ? l : l.substr(0, pos));
            bool grep = (pos == std::string::npos) && contientNomGL(l);
            if (juste) ++g;
            if (grep) ++r;
            if (juste && !grep) ++cachees;
        }

        std::cout << nom << " LIGNES " << K << " GL " << g << " GREP " << r << std::endl;

        bool entete = nom.size() >= 2 && nom.compare(nom.size() - 2, 2, ".h") == 0;
        if (entete) { entLignes += K; entGL += g; }
        else        { srcLignes += K; srcGL += g; }

        if (g > meilleur) { meilleur = g; plusLourd = nom; }
    }

    std::cout << "ENTETES LIGNES " << entLignes << " GL " << entGL << std::endl;
    std::cout << "SOURCES LIGNES " << srcLignes << " GL " << srcGL << std::endl;
    std::cout << "PLUS LOURD " << plusLourd << std::endl;
    std::cout << "CACHEES " << cachees << std::endl;
    return 0;
}