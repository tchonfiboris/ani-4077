#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>

int main() {
    long long W, H;
    int N;
    std::cin >> W >> H >> N;

    // La fenêtre est la cible 0.
    std::map<int, std::pair<long long, long long>> cibles;
    cibles[0] = {W, H};

    int liee = 0;
    // Au départ, le viewport vaut 0 0 W H.
    long long vx = 0, vy = 0, vl = W, vh = H;

    int dessins = 0, points = 0, malCadres = 0;

    for (int i = 0; i < N; ++i) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "CIBLE") {
            int id;
            long long L, Ht;
            std::cin >> id >> L >> Ht;
            cibles[id] = {L, Ht};  // rien d'autre ne change
        } else if (cmd == "LIER") {
            int id;
            std::cin >> id;
            // Seules les cibles déjà déclarées sont liées.
            // LIER ne touche jamais au viewport.
            if (cibles.count(id)) liee = id;
        } else if (cmd == "VIEWPORT") {
            std::cin >> vx >> vy >> vl >> vh;
        } else if (cmd == "DESSIN") {
            ++dessins;
            long long L = cibles[liee].first, Ht = cibles[liee].second;

            // Zone commune : maximums et minimums.
            long long x0 = std::max(vx, 0LL);
            long long y0 = std::max(vy, 0LL);
            long long x1 = std::min(vx + vl, L);
            long long y1 = std::min(vy + vh, Ht);

            if (x0 >= x1 || y0 >= y1) {
                std::cout << "DESSIN " << dessins << " CIBLE " << liee << " DEHORS" << std::endl;
                ++malCadres;  // DEHORS compte comme mal cadré
            } else {
                long long aire = (x1 - x0) * (y1 - y0);
                long long scene = aire * 100 / (vl * vh);
                long long couvre = aire * 100 / (L * Ht);

                std::string verdict;
                if (vx == 0 && vy == 0 && vl == L && vh == Ht) {
                    verdict = "JUSTE";
                } else if (vx >= 0 && vy >= 0 && vx + vl <= L && vy + vh <= Ht) {
                    verdict = "COIN";
                } else {
                    verdict = "ROGNE";
                }
                if (verdict != "JUSTE") ++malCadres;

                std::cout << "DESSIN " << dessins << " CIBLE " << liee
                          << " ZONE " << x0 << " " << y0 << " " << x1 << " " << y1
                          << " SCENE " << scene << " COUVRE " << couvre
                          << " " << verdict << std::endl;
            }
        } else if (cmd == "POINT") {
            ++points;
            long long nx, ny;
            std::cin >> nx >> ny;
            long long L = cibles[liee].first, Ht = cibles[liee].second;

            long long px = vx + (nx + 100) * vl / 200;
            long long py = vy + (ny + 100) * vh / 200;
            bool hors = (px < 0 || px > L - 1 || py < 0 || py > Ht - 1);

            std::cout << "POINT " << points << " " << px << " " << py;
            if (hors) std::cout << " HORS";
            std::cout << std::endl;
        }
    }

    std::cout << "DESSINS " << dessins << std::endl;
    std::cout << "MAL CADRES " << malCadres << std::endl;
    return 0;
}