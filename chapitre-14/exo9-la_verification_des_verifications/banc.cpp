#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct BenchLine {
    bool is_fault = false; // true = FAUTE, false = SAIN
    std::string code;
};

static std::string strip_cr(std::string s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
    return s;
}

static bool is_word_char(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return std::isalnum(uc) != 0 || c == '_';
}

static bool in_range(char c, char lo, char hi) {
    return c >= lo && c <= hi;
}

static bool match_char_class(char ch,
                             const std::string& pat,
                             std::size_t open_bracket,
                             std::size_t& close_bracket) {
    std::size_t idx = open_bracket + 1;
    bool matched = false;

    while (idx < pat.size() && pat[idx] != ']') {
        if (idx + 2 < pat.size() && pat[idx + 1] == '-') {
            char lo = pat[idx];
            char hi = pat[idx + 2];
            if ((in_range(lo, 'A', 'Z') && in_range(hi, 'A', 'Z')) ||
                (in_range(lo, 'a', 'z') && in_range(hi, 'a', 'z')) ||
                (in_range(lo, '0', '9') && in_range(hi, '0', '9'))) {
                if (ch >= lo && ch <= hi) {
                    matched = true;
                }
                idx += 3;
                continue;
            }
        }
        if (ch == pat[idx]) {
            matched = true;
        }
        ++idx;
    }

    if (idx < pat.size() && pat[idx] == ']') {
        close_bracket = idx;
    } else {
        close_bracket = pat.size();
    }
    return matched;
}

static bool match_at(const std::string& line,
                     std::size_t pos,
                     const std::string& pat,
                     std::size_t p_idx) {
    std::size_t s_idx = pos;
    std::size_t i = p_idx;

    while (i < pat.size()) {
        if (pat[i] == '[') {
            if (s_idx >= line.size()) {
                return false;
            }
            std::size_t close_b = 0;
            if (!match_char_class(line[s_idx], pat, i, close_b)) {
                return false;
            }
            ++s_idx;
            i = (close_b < pat.size()) ? (close_b + 1) : pat.size();
        } else {
            if (s_idx >= line.size() || line[s_idx] != pat[i]) {
                return false;
            }
            ++s_idx;
            ++i;
        }
    }

    return true;
}

static bool line_matches_pattern(const std::string& line, const std::string& pat) {
    if (pat.empty()) {
        return false;
    }

    bool require_word_boundary = false;
    std::size_t p_start = 0;

    if (pat.size() >= 2 && pat[0] == '\\' && pat[1] == 'b') {
        require_word_boundary = true;
        p_start = 2;
    }

    for (std::size_t pos = 0; pos <= line.size(); ++pos) {
        if (require_word_boundary) {
            bool boundary_ok = (pos == 0) || !is_word_char(line[pos - 1]);
            if (!boundary_ok) {
                continue;
            }
        }
        if (match_at(line, pos, pat, p_start)) {
            return true;
        }
    }

    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    if (!std::getline(std::cin, line)) {
        return 0;
    }
    line = strip_cr(line);

    int M = 0;
    std::istringstream mss(line);
    mss >> M;

    std::vector<std::string> patterns;
    patterns.reserve(M > 0 ? static_cast<std::size_t>(M) : 0);
    for (int i = 0; i < M; ++i) {
        std::string pat;
        if (mss >> pat) {
            patterns.push_back(pat);
        }
    }

    int N = 0;
    if (!(std::cin >> N)) {
        N = 0;
    }
    std::getline(std::cin, line);

    std::vector<BenchLine> lines;
    lines.reserve(N > 0 ? static_cast<std::size_t>(N) : 0);

    for (int i = 0; i < N; ++i) {
        if (!std::getline(std::cin, line)) {
            break;
        }
        line = strip_cr(line);

        std::size_t sp = line.find(' ');
        std::string kind = (sp == std::string::npos) ? line : line.substr(0, sp);
        std::string code = (sp == std::string::npos) ? std::string() : line.substr(sp + 1);

        BenchLine bl;
        bl.is_fault = (kind == "FAUTE");
        bl.code = code;
        lines.push_back(bl);
    }

    const std::size_t num_pat = patterns.size();
    const std::size_t num_lines = lines.size();

    std::vector<std::vector<bool>> matches(num_lines, std::vector<bool>(num_pat, false));

    long long total_faults = 0;
    long long found_faults = 0;
    long long total_healthy = 0;
    long long accepted_healthy = 0;

    for (std::size_t i = 0; i < num_lines; ++i) {
        bool any_match = false;
        for (std::size_t j = 0; j < num_pat; ++j) {
            bool m = line_matches_pattern(lines[i].code, patterns[j]);
            matches[i][j] = m;
            if (m) {
                any_match = true;
            }
        }

        if (lines[i].is_fault) {
            ++total_faults;
            if (any_match) {
                ++found_faults;
            }
        } else {
            ++total_healthy;
            if (!any_match) {
                ++accepted_healthy;
            }
        }
    }

    std::cout << "BANC FAUTES TROUVEES " << found_faults << " SUR " << total_faults << '\n';
    std::cout << "BANC SAINS ACCEPTES " << accepted_healthy << " SUR " << total_healthy << '\n';
    if (found_faults == total_faults && accepted_healthy == total_healthy) {
        std::cout << "BANC PASSE\n";
    } else {
        std::cout << "BANC ECHOUE\n";
    }

    long long untested_count = 0;

    for (std::size_t j = 0; j < num_pat; ++j) {
        long long lost = 0;
        for (std::size_t i = 0; i < num_lines; ++i) {
            if (!lines[i].is_fault || !matches[i][j]) {
                continue;
            }
            bool other_matches = false;
            for (std::size_t k = 0; k < num_pat; ++k) {
                if (k != j && matches[i][k]) {
                    other_matches = true;
                    break;
                }
            }
            if (!other_matches) {
                ++lost;
            }
        }

        if (lost == 0) {
            ++untested_count;
        }

        std::cout << "SANS " << patterns[j] << " PERD " << lost << '\n';
    }

    std::cout << "NON EPROUVES " << untested_count << '\n';

    return 0;
}