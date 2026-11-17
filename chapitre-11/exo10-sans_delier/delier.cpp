#include <iostream>
#include <map>
#include <string>

// État d'un tableau de sommets : son tampon d'index et celui qu'il doit avoir.
struct Tableau {
    long long index;
    long long attendu;
    Tableau() : index(0), attendu(0) {}
};

int main() {
    int N = 0, D = 0;
    if (!(std::cin >> N >> D)) return 0;

    std::map<long long, Tableau> tableaux;
    long long lie = 0;       // tableau actuellement lié, 0 au départ
    long long appels = 0;    // nombre de glBindVertexArray, y compris vers 0
    long long faux = 0;
    long long dessins = 0;

    auto lieTableau = [&](long long v) {
        ++appels;
        lie = v;
    };

    for (int i = 0; i < N; ++i) {
        std::string cmd;
        if (!(std::cin >> cmd)) break;

        if (cmd == "CREE") {
            long long v, e;
            std::cin >> v >> e;
            lieTableau(v);
            tableaux[v].index = e;
            tableaux[v].attendu = e;
            lieTableau(0);
        } else if (cmd == "TELEVERSE") {
            long long e;
            std::cin >> e;
            // Un autre code lie un tampon d'index : il atteint le tableau lié.
            if (lie != 0) tableaux[lie].index = e;
        } else if (cmd == "DESSINE") {
            long long v;
            std::cin >> v;
            lieTableau(v);
            ++dessins;
            const Tableau& t = tableaux[v];
            if (t.index == t.attendu) {
                std::cout << "DESSIN " << dessins << " " << v << " JUSTE" << std::endl;
            } else {
                ++faux;
                std::cout << "DESSIN " << dessins << " " << v << " FAUX INDEX "
                          << t.index << "/" << t.attendu << std::endl;
            }
            if (D == 1) lieTableau(0);
        }
    }

    long long corrompus = 0;
    for (const auto& paire : tableaux) {
        if (paire.second.index != paire.second.attendu) ++corrompus;
    }

    std::cout << "APPELS " << appels << std::endl;
    std::cout << "CORROMPUS " << corrompus << std::endl;
    std::cout << "FAUX " << faux << std::endl;
    return 0;
}
