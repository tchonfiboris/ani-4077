#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Rule {
    std::string filename;
    std::vector<std::string> patterns;
};

struct Violation {
    int line = 0;
    std::string pattern;
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

static std::vector<std::string> strip_comments_keep_lines(const std::vector<std::string>& raw_lines) {
    std::string combined;
    for (std::size_t i = 0; i < raw_lines.size(); ++i) {
        combined += raw_lines[i];
        if (i + 1 < raw_lines.size()) {
            combined.push_back('\n');
        }
    }

    std::string cleaned;
    cleaned.reserve(combined.size());

    bool in_block = false;
    std::size_t i = 0;
    while (i < combined.size()) {
        if (in_block) {
            if (combined[i] == '*' && i + 1 < combined.size() && combined[i + 1] == '/') {
                in_block = false;
                i += 2;
            } else {
                if (combined[i] == '\n') {
                    cleaned.push_back('\n');
                }
                ++i;
            }
        } else {
            if (combined[i] == '/' && i + 1 < combined.size() && combined[i + 1] == '/') {
                while (i < combined.size() && combined[i] != '\n') {
                    ++i;
                }
            } else if (combined[i] == '/' && i + 1 < combined.size() && combined[i + 1] == '*') {
                in_block = true;
                i += 2;
            } else {
                cleaned.push_back(combined[i]);
                ++i;
            }
        }
    }

    std::vector<std::string> out_lines;
    std::size_t start = 0;
    while (true) {
        std::size_t nl = cleaned.find('\n', start);
        if (nl == std::string::npos) {
            out_lines.push_back(cleaned.substr(start));
            break;
        }
        out_lines.push_back(cleaned.substr(start, nl - start));
        start = nl + 1;
    }

    return out_lines;
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
    int R = 0;
    if (!(std::cin >> R)) {
        return 0;
    }
    std::getline(std::cin, line);

    std::vector<Rule> rules;
    rules.reserve(R > 0 ? static_cast<std::size_t>(R) : 0);

    for (int i = 0; i < R; ++i) {
        if (!std::getline(std::cin, line)) {
            break;
        }
        line = strip_cr(line);
        std::istringstream iss(line);
        Rule r;
        int K = 0;
        iss >> r.filename >> K;
        r.patterns.reserve(K > 0 ? static_cast<std::size_t>(K) : 0);
        for (int j = 0; j < K; ++j) {
            std::string pat;
            if (iss >> pat) {
                r.patterns.push_back(pat);
            }
        }
        rules.push_back(r);
    }

    int F = 0;
    if (!(std::cin >> F)) {
        F = 0;
    }
    std::getline(std::cin, line);

    std::unordered_map<std::string, std::vector<std::string>> files_clean;
    files_clean.reserve(static_cast<std::size_t>(F) * 2 + 1);

    for (int f = 0; f < F; ++f) {
        if (!std::getline(std::cin, line)) {
            break;
        }
        line = strip_cr(line);
        std::istringstream iss(line);
        std::string kw, nom;
        int L = 0;
        iss >> kw >> nom >> L;

        std::vector<std::string> raw_lines;
        raw_lines.reserve(L > 0 ? static_cast<std::size_t>(L) : 0);
        for (int l = 0; l < L; ++l) {
            std::string text_line;
            if (!std::getline(std::cin, text_line)) {
                text_line.clear();
            }
            raw_lines.push_back(strip_cr(text_line));
        }

        files_clean[nom] = strip_comments_keep_lines(raw_lines);
    }

    long long total_faults = 0;

    for (const Rule& r : rules) {
        auto it = files_clean.find(r.filename);
        if (it == files_clean.end()) {
            std::cout << "ABSENT " << r.filename << '\n';
            ++total_faults;
            continue;
        }

        const std::vector<std::string>& clines = it->second;
        long long file_faults = 0;
        std::vector<Violation> shown;

        for (std::size_t idx = 0; idx < clines.size(); ++idx) {
            int line_num = static_cast<int>(idx + 1);
            for (const std::string& pat : r.patterns) {
                if (line_matches_pattern(clines[idx], pat)) {
                    ++file_faults;
                    ++total_faults;
                    if (shown.size() < 5) {
                        shown.push_back({line_num, pat});
                    }
                }
            }
        }

        if (file_faults == 0) {
            std::cout << "OK " << r.filename << '\n';
        } else {
            std::cout << "REFUSE " << r.filename << '\n';
            for (const Violation& v : shown) {
                std::cout << "LIGNE " << v.line << " MOTIF " << v.pattern << '\n';
            }
        }
    }

    int exit_code = (total_faults == 0) ? 0 : 1;
    std::cout << "FAUTES " << total_faults << '\n';
    std::cout << "CODE " << exit_code << '\n';

    return exit_code;
}