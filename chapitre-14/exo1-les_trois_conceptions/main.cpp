#include <iostream>
#include <string>
#include <vector>

struct RectVals {
    long long x = 0;
    long long y = 0;
    long long ex = 0;
    long long ey = 0;
};

static RectVals apply_camera(const RectVals& in, long long cx, long long cy, long long z) {
    RectVals out;
    out.x = (in.x - cx) * z;
    out.y = (in.y - cy) * z;
    out.ex = in.ex * z;
    out.ey = in.ey * z;
    return out;
}

static long long checksum(const std::vector<RectVals>& vals) {
    constexpr long long MOD = 1000003LL;
    long long total = 0;

    for (std::size_t i = 0; i < vals.size(); ++i) {
        const long long k = static_cast<long long>(i + 1);
        const RectVals& v = vals[i];
        const long long term = k * (v.x + 3LL * v.y + 5LL * v.ex + 7LL * v.ey);
        total += term;
    }

    long long rem = total % MOD;
    if (rem < 0) {
        rem += MOD;
    }
    return rem;
}

static bool same_rect(const RectVals& a, const RectVals& b) {
    return a.x == b.x && a.y == b.y && a.ex == b.ex && a.ey == b.ey;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long cx = 0;
    long long cy = 0;
    long long z = 1;
    if (!(std::cin >> cx >> cy >> z)) {
        return 0;
    }

    int N = 0;
    if (!(std::cin >> N)) {
        N = 0;
    }

    std::vector<RectVals> scene_vals;
    std::vector<RectVals> rhi_vals;
    std::vector<RectVals> buggy_vals;

    scene_vals.reserve(N > 0 ? static_cast<std::size_t>(N) : 0);
    rhi_vals.reserve(N > 0 ? static_cast<std::size_t>(N) : 0);
    buggy_vals.reserve(N > 0 ? static_cast<std::size_t>(N) : 0);

    long long displaced = 0;

    for (int i = 0; i < N; ++i) {
        std::string nature;
        RectVals orig;
        std::cin >> nature >> orig.x >> orig.y >> orig.ex >> orig.ey;

        RectVals transformed = apply_camera(orig, cx, cy, z);

        RectVals s_val = (nature == "MONDE") ? transformed : orig;
        RectVals r_val = (nature == "MONDE") ? transformed : orig; // exception posée sur INTERFACE
        RectVals b_val = transformed;

        scene_vals.push_back(s_val);
        rhi_vals.push_back(r_val);
        buggy_vals.push_back(b_val);

        if (!same_rect(s_val, b_val)) {
            ++displaced;
        }
    }

    const long long sum_scene = checksum(scene_vals);
    const long long sum_rhi = checksum(rhi_vals);
    const long long sum_buggy = checksum(buggy_vals);

    std::cout << "SCENE " << sum_scene << '\n';
    std::cout << "RHI " << sum_rhi << '\n';
    std::cout << "RHI-BOGUE " << sum_buggy << '\n';

    std::cout << (sum_scene == sum_rhi ? "SCENE ET RHI IDENTIQUES\n" : "SCENE ET RHI DIFFERENTES\n");
    std::cout << (sum_scene == sum_buggy ? "SCENE ET RHI-BOGUE IDENTIQUES\n" : "SCENE ET RHI-BOGUE DIFFERENTES\n");
    std::cout << "DEPLACEES " << displaced << '\n';

    return 0;
}