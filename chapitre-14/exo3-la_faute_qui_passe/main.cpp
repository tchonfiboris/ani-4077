#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct CodeLine {
    bool is_fault = false; // true = FAUTE, false = SAIN
    std::string code;
};

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

static bool in_range(char c, char lo, char hi) {
    return c >= lo && c <= hi;
}

static bool match_char_class(char ch, const std::string& pat, std::size_t open_bracket, std::size_t& close_bracket) {
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

static bool match_at(const std::string& line, std::size_t pos, const std::string& pat, std::size_t p_idx) {
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
            bool boundary_ok = (pos == 0) || !is_ident_char(line[pos - 1]);
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

static bool is_line_found(const std::string& line, const std::vector<std::string>& patterns) {
    for (const std::string& pat : patterns) {
        if (line_matches_pattern(line, pat)) {
            return true;
        }
    }
    return false;
}

static std::string rename_identifiers(const std::string& line,
                                    const std::string& old_name,
                                    const std::string& new_name) {
    std::string out;
    out.reserve(line.size());

    std::size_t i = 0;
    while (i < line.size()) {
        if (is_ident_char(line[i])) {
            std::size_t start = i;
            while (i < line.size() && is_ident_char(line[i])) {
                ++i;
            }
            std::string ident = line.substr(start, i - start);
            if (ident == old_name) {
                out += new_name;
            } else {
                out += ident;
            }
        } else {
            out.push_back(line[i]);
            ++i;
        }
    }

    return out;
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

    std::vector<CodeLine> lines;
    lines.reserve(N > 0 ? static_cast<std::size_t>(N) : 0);

    for (int i = 0; i < N; ++i) {
        if (!std::getline(std::cin, line)) {
            break;
        }
        line = strip_cr(line);

        CodeLine cl;
        std::size_t sp = line.find(' ');
        std::string kind = (sp == std::string::npos) ? line : line.substr(0, sp);
        std::string text = (sp == std::string::npos) ? std::string() : line.substr(sp + 1);

        cl.is_fault = (kind == "FAUTE");
        cl.code = text;
        lines.push_back(cl);
    }

    int R = 0;
    if (!(std::cin >> R)) {
        R = 0;
    }

    std::vector<std::pair<std::string, std::string>> renames;
    renames.reserve(R > 0 ? static_cast<std::size_t>(R) : 0);
    for (int r = 0; r < R; ++r) {
        std::string old_n, new_n;
        if (std::cin >> old_n >> new_n) {
            renames.emplace_back(old_n, new_n);
        }
    }

    long long total_fault_lines = 0;
    long long before_found = 0;
    long long before_alerts = 0;
    std::vector<bool> before_matched(lines.size(), false);

    for (std::size_t idx = 0; idx < lines.size(); ++idx) {
        int k = static_cast<int>(idx + 1);
        bool found = is_line_found(lines[idx].code, patterns);
        before_matched[idx] = found;

        if (lines[idx].is_fault) {
            ++total_fault_lines;
            if (found) {
                ++before_found;
                std::cout << "LIGNE " << k << " FAUTE TROUVEE\n";
            } else {
                std::cout << "LIGNE " << k << " FAUTE PASSEE\n";
            }
        } else {
            if (found) {
                ++before_alerts;
                std::cout << "LIGNE " << k << " SAIN ALERTE\n";
            } else {
                std::cout << "LIGNE " << k << " SAIN OK\n";
            }
        }
    }

    for (const auto& ren : renames) {
        for (CodeLine& cl : lines) {
            cl.code = rename_identifiers(cl.code, ren.first, ren.second);
        }
    }

    long long after_found = 0;
    long long after_alerts = 0;
    long long slipped_by_rename = 0;

    for (std::size_t idx = 0; idx < lines.size(); ++idx) {
        bool after_matched = is_line_found(lines[idx].code, patterns);
        if (lines[idx].is_fault) {
            if (after_matched) {
                ++after_found;
            }
            if (before_matched[idx] && !after_matched) {
                ++slipped_by_rename;
            }
        } else {
            if (after_matched) {
                ++after_alerts;
            }
        }
    }

    std::cout << "AVANT TROUVEES " << before_found << " SUR " << total_fault_lines
              << " ALERTES " << before_alerts << '\n';
    std::cout << "APRES TROUVEES " << after_found << " SUR " << total_fault_lines
              << " ALERTES " << after_alerts << '\n';
    std::cout << "PASSEES PAR RENOMMAGE " << slipped_by_rename << '\n';

    return 0;
}