#include <iostream>
#include <string>
#include <vector>

// Position d'un nom dans l'ordre, -1 s'il est absent
static int position(const std::vector<std::string>& ordre, const std::string& nom) {
    for (size_t i = 0; i < ordre.size(); ++i) {
        if (ordre[i] == nom) return (int)i;
    }
    return -1;
}

int main() {

    int d;

    if (!(std::cin >> d)) {
        d = 0;}

    std::vector<std::string> modules(d), besoins(d);

    for (int i = 0; i < d; ++i) {
        if (!(std::cin >> modules[i] >> besoins[i])) {
            d = i;
            modules.resize(d);
            besoins.resize(d);
            break;
        }
    }

    int o;

    if (!(std::cin >> o)){
         o = 0;}

    std::vector<std::string> ordre;

    for (int i = 0; i < o; ++i) {
        std::string nom;
        if (!(std::cin >> nom)) 
        break;
        ordre.push_back(nom);
    }

    int nonResolus = 0; 
    int absents = 0;

    for (int i = 0; i < d; ++i) {
        int pa = position(ordre, modules[i]);
        int pb = position(ordre, besoins[i]);

        const char* verdict;
        if (pa < 0 || pb < 0) {
            // absent : on ne regarde pas les positions
            verdict = "ABSENT";
            ++absents;
        } else if (pa < pb) {
            verdict = "OK";
        } else {
            // A ne précède pas B (y compris A == B)
            verdict = "NON RESOLU";
            ++nonResolus;
        }

        std::cout << modules[i] << " " << besoins[i] << " " << verdict << std::endl;
    }

    bool linuxOk = (nonResolus == 0 && absents == 0);
    bool windowsOk = (absents == 0);

    std::cout << "NON RESOLUS " << nonResolus << std::endl;
    std::cout << "ABSENTS " << absents << "\n";
    std::cout << "LINUX " << (linuxOk ? "OK" : "ECHEC") << std::endl;
    std::cout << "WINDOWS " << (windowsOk ? "OK" : "ECHEC") << std::endl;

    return 0;
}
