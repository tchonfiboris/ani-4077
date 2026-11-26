#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N = 0;
    if (!(std::cin >> N)) {
        return 0;
    }

    long long broken_a = 0;
    long long broken_b = 0;
    long long repaired = 0;
    long long broken_by_flip = 0;
    long long lines_a = 0; // une par objet INTERFACE
    long long lines_b = 0; // une par objet MONDE

    for (int i = 0; i < N; ++i) {
        std::string name, nature, state;
        std::cin >> name >> nature >> state;

        if (nature == "INTERFACE") {
            ++lines_a;
        } else if (nature == "MONDE") {
            ++lines_b;
        }

        bool ok_a = true;
        bool ok_b = true;

        if (state != "ECRIT") {
            ok_a = (nature == "MONDE");
            ok_b = (nature == "INTERFACE");
        }

        if (!ok_a) {
            ++broken_a;
        }
        if (!ok_b) {
            ++broken_b;
        }
        if (!ok_a && ok_b) {
            ++repaired;
        }
        if (ok_a && !ok_b) {
            ++broken_by_flip;
        }

        std::cout << name
                  << " A " << (ok_a ? "OK" : "CASSE")
                  << " B " << (ok_b ? "OK" : "CASSE") << '\n';
    }

    std::cout << "CASSES A " << broken_a << '\n';
    std::cout << "CASSES B " << broken_b << '\n';
    std::cout << "REPARES " << repaired << '\n';
    std::cout << "CASSES PAR L INVERSION " << broken_by_flip << '\n';
    std::cout << "LIGNES A " << lines_a << '\n';
    std::cout << "LIGNES B " << lines_b << '\n';

    if (lines_a < lines_b) {
        std::cout << "MOINS DE LIGNES A\n";
    } else if (lines_b < lines_a) {
        std::cout << "MOINS DE LIGNES B\n";
    } else {
        std::cout << "MOINS DE LIGNES EGALITE\n";
    }

    return 0;
}