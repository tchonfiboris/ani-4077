#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct DrawCmd {
    std::string name;
    long long prog = 0;
    long long tex = 0;
    int x0 = 0;
    int x1 = 0;
    long long z = 0;
    long long color = 0;
    int order_idx = 0;
};

static long long count_bindings(const std::vector<DrawCmd>& cmds) {
    long long cache_prog = 0;
    long long cache_tex = 0;
    long long cache_vao = 0;
    long long emitted = 0;

    for (const DrawCmd& cmd : cmds) {
        if (cmd.prog != cache_prog) {
            cache_prog = cmd.prog;
            ++emitted;
        }
        if (cmd.tex != cache_tex) {
            cache_tex = cmd.tex;
            ++emitted;
        }
        if (1LL != cache_vao) {
            cache_vao = 1LL;
            ++emitted;
        }
    }

    return emitted;
}

static std::vector<long long> render_row(int width, int test_enabled, const std::vector<DrawCmd>& cmds) {
    std::vector<long long> colors(static_cast<std::size_t>(width), 0LL);
    std::vector<long long> depths(static_cast<std::size_t>(width), 100LL);

    for (const DrawCmd& cmd : cmds) {
        int left = std::max(0, cmd.x0);
        int right = std::min(width - 1, cmd.x1);
        for (int x = left; x <= right; ++x) {
            std::size_t idx = static_cast<std::size_t>(x);
            if (test_enabled == 0 || cmd.z < depths[idx]) {
                colors[idx] = cmd.color;
                depths[idx] = cmd.z;
            }
        }
    }

    return colors;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int W = 0;
    int test_flag = 0;
    int N = 0;
    if (!(std::cin >> W >> test_flag >> N)) {
        return 0;
    }

    std::vector<DrawCmd> submitted(N > 0 ? static_cast<std::size_t>(N) : 0);
    for (int i = 0; i < N; ++i) {
        DrawCmd cmd;
        std::cin >> cmd.name >> cmd.prog >> cmd.tex >> cmd.x0 >> cmd.x1 >> cmd.z >> cmd.color;
        cmd.order_idx = i;
        submitted[static_cast<std::size_t>(i)] = cmd;
    }

    std::vector<DrawCmd> sorted = submitted;
    std::stable_sort(sorted.begin(), sorted.end(), [](const DrawCmd& a, const DrawCmd& b) {
        if (a.prog != b.prog) {
            return a.prog < b.prog;
        }
        return a.tex < b.tex;
    });

    const long long submitted_emitted = count_bindings(submitted);
    const long long sorted_emitted = count_bindings(sorted);

    const std::vector<long long> submitted_colors = render_row(W, test_flag, submitted);
    const std::vector<long long> sorted_colors = render_row(W, test_flag, sorted);

    long long diff_pixels = 0;
    for (int x = 0; x < W; ++x) {
        std::size_t idx = static_cast<std::size_t>(x);
        if (submitted_colors[idx] != sorted_colors[idx]) {
            ++diff_pixels;
        }
    }

    std::cout << "ORDRE";
    for (const DrawCmd& cmd : sorted) {
        std::cout << ' ' << cmd.name;
    }
    std::cout << '\n';

    std::cout << "SOUMIS EMISES " << submitted_emitted << '\n';
    std::cout << "TRIE EMISES " << sorted_emitted << '\n';
    std::cout << "IMAGE IDENTIQUE " << (diff_pixels == 0 ? "OUI" : "NON") << '\n';
    std::cout << "PIXELS DIFFERENTS " << diff_pixels << '\n';

    return 0;
}