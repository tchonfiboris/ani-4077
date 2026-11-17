#include <iostream>
#include <string>

int main() {
    int N = 0;
    if (!(std::cin >> N)) N = 0;

    long long reel = 0;      // programme que porte la carte
    long long retenu = 0;    // programme que le cache croit en place
    bool connu = true;       // le cache connaît-il sa valeur ?

    long long appels = 0, evites = 0, directs = 0, faux = 0;
    long long dessins = 0;

    for (int i = 0; i < N; ++i) {
        std::string cmd;
        if (!(std::cin >> cmd)) break;

        if (cmd == "ACTIVE") {
            long long p;
            std::cin >> p;
            if (connu && retenu == p) {
                ++evites;
            } else {
                ++appels;
                reel = p;
                retenu = p;
                connu = true;
            }
        } else if (cmd == "DIRECT") {
            long long p;
            std::cin >> p;
            reel = p;
            ++directs;
        } else if (cmd == "OUBLIE") {
            connu = false;
        } else if (cmd == "DESSINE") {
            long long p;
            std::cin >> p;
            ++dessins;
            if (reel == p) {
                std::cout << "DESSIN " << dessins << " JUSTE" << std::endl;
            } else {
                ++faux;
                std::cout << "DESSIN " << dessins << " FAUX "
                          << reel << "/" << p << std::endl;
            }
        }
    }

    std::cout << "APPELS " << appels << std::endl;
    std::cout << "EVITES " << evites << std::endl;
    std::cout << "DIRECTS " << directs << std::endl;
    std::cout << "FAUX " << faux << std::endl;
    return 0;
}