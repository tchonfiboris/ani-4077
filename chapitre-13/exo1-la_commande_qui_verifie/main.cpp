#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static std::string strip_cr(std::string s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
    return s;
}

static bool is_ident_char(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return std::isalnum(uc) != 0 || c == '_';
}

static bool is_upper_alpha(char c) {
    return c >= 'A' && c <= 'Z';
}

static bool has_gl_name(const std::string& line) {
    if (line.find("//") != std::string::npos) {
        return false;
    }

    for (std::size_t i = 0; i < line.size(); ++i) {
        bool word_start = (i == 0) || !is_ident_char(line[i - 1]);
        if (!word_start) {
            continue;
        }

        if (i + 2 < line.size() &&
            line[i] == 'G' &&
            line[i + 1] == 'L' &&
            line[i + 2] == '_') {
            return true;
        }

        if (i + 2 < line.size() &&
            line[i] == 'g' &&
            line[i + 1] == 'l' &&
            is_upper_alpha(line[i + 2])) {
            return true;
        }
    }

    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int V = 0;
    if (!(std::cin >> V)) {
        return 0;
    }

    std::string line;
    std::getline(std::cin, line); // consomme la fin de la ligne V

    if (V <= 0) {
        std::cout << "PREMIERE PROPRE AUCUNE\n";
        std::cout << "RECHUTES 0\n";
        std::cout << "SCRIPT AUCUN\n";
        return 0;
    }

    std::string first_clean = "AUCUNE";
    int relapses = 0;
    bool prev_clean = false;
    bool last_clean = false;

    for (int v = 0; v < V; ++v) {
        std::string header;
        if (!std::getline(std::cin, header)) {
            break;
        }
        header = strip_cr(header);

        std::string tag;
        std::string name;
        int K = 0;
        std::istringstream hss(header);
        hss >> tag >> name >> K;

        std::vector<int> flagged_lines;
        for (int line_no = 1; line_no <= K; ++line_no) {
            std::string src_line;
            if (!std::getline(std::cin, src_line)) {
                break;
            }
            src_line = strip_cr(src_line);
            if (has_gl_name(src_line)) {
                flagged_lines.push_back(line_no);
            }
        }

        bool is_clean = flagged_lines.empty();
        if (is_clean) {
            std::cout << name << " PROPRE\n";
            if (first_clean == "AUCUNE") {
                first_clean = name;
            }
        } else {
            std::cout << name << " SALE";
            for (int idx : flagged_lines) {
                std::cout << ' ' << idx;
            }
            std::cout << '\n';
            if (prev_clean) {
                ++relapses;
            }
        }

        prev_clean = is_clean;
        last_clean = is_clean;
    }

    std::cout << "PREMIERE PROPRE " << first_clean << '\n';
    std::cout << "RECHUTES " << relapses << '\n';
    std::cout << (last_clean ? "SCRIPT OK\n" : "SCRIPT ECHEC\n");

    return 0;
}