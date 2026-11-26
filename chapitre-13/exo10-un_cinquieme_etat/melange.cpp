#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct OpaqueFrag {
    long long z = 0;
    long long v = 0;
};

struct AlphaFrag {
    std::string name;
    long long z = 0;
    long long v = 0;
    long long a = 0;
    int orig_idx = 0;
};

static long long factor_value(const std::string& mode, long long a) {
    if (mode == "UN") {
        return 100LL;
    }
    if (mode == "ZERO") {
        return 0LL;
    }
    if (mode == "ALPHA") {
        return a;
    }
    if (mode == "UNMOINSALPHA") {
        return 100LL - a;
    }
    return 0LL;
}

static long long blend_pixel(long long dst,
                             long long v,
                             long long a,
                             const std::string& src_mode,
                             const std::string& dst_mode) {
    const long long fs = factor_value(src_mode, a);
    const long long fd = factor_value(dst_mode, a);
    long long res = (v * fs + dst * fd) / 100LL;
    if (res > 255LL) {
        res = 255LL;
    }
    return res;
}

static long long run_transparent_pass(long long start_val,
                                      long long opaque_depth,
                                      const std::vector<AlphaFrag>& frags,
                                      const std::string& src_mode,
                                      const std::string& dst_mode,
                                      long long& hidden_out) {
    long long cur = start_val;
    long long hidden = 0;

    for (const AlphaFrag& f : frags) {
        if (f.z < opaque_depth) {
            cur = blend_pixel(cur, f.v, f.a, src_mode, dst_mode);
        } else {
            ++hidden;
        }
    }

    hidden_out = hidden;
    return cur;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string src_mode, dst_mode;
    if (!(std::cin >> src_mode >> dst_mode)) {
        return 0;
    }

    int N = 0;
    std::cin >> N;
    std::vector<OpaqueFrag> opaques(N > 0 ? static_cast<std::size_t>(N) : 0);
    for (int i = 0; i < N; ++i) {
        std::cin >> opaques[static_cast<std::size_t>(i)].z
                  >> opaques[static_cast<std::size_t>(i)].v;
    }

    int M = 0;
    std::cin >> M;
    std::vector<AlphaFrag> given(M > 0 ? static_cast<std::size_t>(M) : 0);
    for (int i = 0; i < M; ++i) {
        AlphaFrag f;
        std::cin >> f.name >> f.z >> f.v >> f.a;
        f.orig_idx = i;
        given[static_cast<std::size_t>(i)] = f;
    }

    long long pixel_val = 0LL;
    long long pixel_depth = 100LL;

    for (const OpaqueFrag& op : opaques) {
        if (op.z < pixel_depth) {
            pixel_val = op.v;
            pixel_depth = op.z;
        }
    }

    std::cout << "OPAQUE " << pixel_val << ' ' << pixel_depth << '\n';

    std::vector<AlphaFrag> reversed(given.rbegin(), given.rend());

    std::vector<AlphaFrag> back_to_front = given;
    std::stable_sort(back_to_front.begin(), back_to_front.end(), [](const AlphaFrag& a, const AlphaFrag& b) {
        return a.z > b.z;
    });

    long long hidden_given = 0;
    long long hidden_rev = 0;
    long long hidden_btf = 0;

    const long long res_given = run_transparent_pass(pixel_val, pixel_depth, given, src_mode, dst_mode, hidden_given);
    const long long res_rev = run_transparent_pass(pixel_val, pixel_depth, reversed, src_mode, dst_mode, hidden_rev);
    const long long res_btf = run_transparent_pass(pixel_val, pixel_depth, back_to_front, src_mode, dst_mode, hidden_btf);

    std::cout << "DONNE " << res_given << '\n';
    std::cout << "INVERSE " << res_rev << '\n';
    std::cout << "ARRIERE AVANT " << res_btf << '\n';
    std::cout << "ORDRE COMPTE " << (res_given != res_rev ? "OUI\n" : "NON\n");
    std::cout << "CACHES " << hidden_given << '\n';

    return 0;
}