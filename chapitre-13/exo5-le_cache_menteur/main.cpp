#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct ChannelState {
    long long reel = 0;
    long long cache = 0;
    long long demande = 0;
};

struct PolicyResult {
    long long emises = 0;
    long long evitees = 0;
    long long faux = 0;
    long long premier = 0; // 0 signifie AUCUN
};

static PolicyResult replay_log(const std::vector<std::string>& lines, bool reset_on_image) {
    ChannelState prog;
    ChannelState tex;
    PolicyResult res;
    long long draw_count = 0;

    for (const std::string& line : lines) {
        std::istringstream iss(line);
        std::string cmd;
        if (!(iss >> cmd)) {
            continue;
        }

        if (cmd == "IMAGE") {
            if (reset_on_image) {
                prog.cache = 0;
                tex.cache = 0;
            }
        } else if (cmd == "LIE") {
            std::string cat;
            long long id = 0;
            iss >> cat >> id;
            ChannelState& ch = (cat == "PROGRAMME") ? prog : tex;
            ch.demande = id;
            if (ch.cache == id) {
                ++res.evitees;
            } else {
                ++res.emises;
                ch.reel = id;
                ch.cache = id;
            }
        } else if (cmd == "DEHORS") {
            std::string cat;
            long long id = 0;
            iss >> cat >> id;
            ChannelState& ch = (cat == "PROGRAMME") ? prog : tex;
            ch.reel = id;
        } else if (cmd == "DESSINE") {
            ++draw_count;
            bool wrong = (prog.reel != prog.demande) || (tex.reel != tex.demande);
            if (wrong) {
                ++res.faux;
                if (res.premier == 0) {
                    res.premier = draw_count;
                }
            }
        }
    }

    return res;
}

static void print_policy(const std::string& name, const PolicyResult& r) {
    std::cout << name
              << " EMISES " << r.emises
              << " EVITEES " << r.evitees
              << " FAUX " << r.faux
              << " PREMIER ";
    if (r.premier == 0) {
        std::cout << "AUCUN\n";
    } else {
        std::cout << r.premier << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N = 0;
    if (!(std::cin >> N)) {
        return 0;
    }

    std::string dummy;
    std::getline(std::cin, dummy); // consomme la fin de ligne de N

    std::vector<std::string> lines;
    lines.reserve(N > 0 ? static_cast<std::size_t>(N) : 0);

    for (int i = 0; i < N; ++i) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            break;
        }
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        lines.push_back(line);
    }

    PolicyResult vide_res = replay_log(lines, true);
    PolicyResult garde_res = replay_log(lines, false);

    print_policy("VIDE", vide_res);
    print_policy("GARDE", garde_res);

    return 0;
}