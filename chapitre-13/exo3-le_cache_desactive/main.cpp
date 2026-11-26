#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long N = 0;
    if (!(std::cin >> N)) {
        return 0;
    }

    long long last_prog = 0;
    long long last_tex = 0;
    long long last_vao = 0;
    long long last_target = 0;

    long long emit_prog = 0;
    long long emit_tex = 0;
    long long emit_vao = 0;
    long long emit_target = 0;

    // Passe initiale sur la fenetre : cible 0
    long long target_req = 0;
    if (target_req != last_target) {
        last_target = target_req;
        ++emit_target;
    }

    for (long long i = 0; i < N; ++i) {
        long long p = 0;
        long long t = 0;
        long long m = 0;
        std::cin >> p >> t >> m;

        if (p != last_prog) {
            last_prog = p;
            ++emit_prog;
        }
        if (t != last_tex) {
            last_tex = t;
            ++emit_tex;
        }
        if (m != last_vao) {
            last_vao = m;
            ++emit_vao;
        }
    }

    const long long ancien = 4 * N;
    const long long demandees = 1 + 3 * N;

    const long long avec_cache = emit_prog + emit_tex + emit_vao + emit_target;
    const long long evitees_cache = demandees - avec_cache;

    const long long sans_cache = 3 * N + emit_target;
    const long long evitees_sans_cache = demandees - sans_cache;

    const long long ecart_total = ancien - avec_cache;
    const long long ecart_deliage = ancien - demandees;
    const long long ecart_cache = evitees_cache;

    std::cout << "ANCIEN " << ancien << '\n';
    std::cout << "DEMANDEES " << demandees << '\n';
    std::cout << "AVEC CACHE " << avec_cache << " EVITEES " << evitees_cache << '\n';
    std::cout << "SANS CACHE " << sans_cache << " EVITEES " << evitees_sans_cache << '\n';
    std::cout << "EMIS PROGRAMME " << emit_prog
              << " TEXTURE " << emit_tex
              << " TABLEAU " << emit_vao
              << " CIBLE " << emit_target << '\n';
    std::cout << "ECART TOTAL " << ecart_total
              << " DELIAGE " << ecart_deliage
              << " CACHE " << ecart_cache << '\n';

    return 0;
}