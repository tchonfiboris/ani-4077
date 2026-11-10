#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::string version;
    int N;
    std::cin >> version >> N;

    int completes = 0, noires = 0, refusees = 0;

    for (int i = 0; i < N; ++i) {
        std::string nom, cf, pf, filtreMin, filtreMag;
        long long cl, ch, pl, ph, niv;
        std::cin >> nom >> cf >> cl >> ch >> pf >> pl >> ph >> filtreMin >> filtreMag >> niv;

        bool couleurPresente = (cf != "AUCUNE");
        bool profPresente = (pf != "AUCUNE");

        // 1. Sans aucune surface.
        if (!couleurPresente && !profPresente) {
            std::cout << nom << " MISSING_ATTACHMENT" << std::endl;
            ++refusees;
            continue;
        }

        // 2-3. Une surface présente est invalide si une taille vaut 0,
        // si son format ne va pas à sa place, ou si DEPTH24 en ES2.
        bool invalide = false;
        if (couleurPresente) {
            if (cl == 0 || ch == 0) invalide = true;
            if (cf != "RGBA8") invalide = true;
        }
        if (profPresente) {
            if (pl == 0 || ph == 0) invalide = true;
            if (pf != "DEPTH16" && pf != "DEPTH24") invalide = true;
            if (pf == "DEPTH24" && version == "ES2") invalide = true;
        }
        if (invalide) {
            std::cout << nom << " INCOMPLETE_ATTACHMENT" << std::endl;
            ++refusees;
            continue;
        }

        // 4-5. Dimensions et zone de dessin.
        long long L, H;
        if (couleurPresente && profPresente) {
            if ((cl != pl || ch != ph) && version == "ES2") {
                std::cout << nom << " INCOMPLETE_DIMENSIONS" << std::endl;
                ++refusees;
                continue;
            }
            L = std::min(cl, pl);
            H = std::min(ch, ph);
        } else if (couleurPresente) {
            L = cl;
            H = ch;
        } else {
            L = pl;
            H = ph;
        }

        // 6-7. Lecture : le filtre ne touche pas à la complétude.
        if (filtreMin == "DEFAUT") filtreMin = "NEAREST_MIPMAP_LINEAR";

        bool noire = false;
        if (filtreMin.find("MIPMAP") != std::string::npos) {
            long long m = std::max(cl, ch);  // plus grand côté de la couleur
            long long chaine = 1;
            while (m > 1) {  // 1 + floor(log2(m))
                m /= 2;
                ++chaine;
            }
            if (niv < chaine) noire = true;
        }

        std::cout << nom << " COMPLETE " << L << "x" << H
                  << " LECTURE " << (noire ? "NOIRE" : "OK") << std::endl;
        ++completes;
        if (noire) ++noires;
    }

    std::cout << "COMPLETES " << completes << std::endl;
    std::cout << "NOIRES " << noires << std::endl;
    std::cout << "REFUSEES " << refusees << std::endl;
    return 0;
}