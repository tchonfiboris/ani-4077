#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Quad {
    long long x = 0;
    long long y = 0;
    long long ex = 0;
    long long ey = 0;
};

static Quad compute_expected(const std::string& need,
                             const Quad& q,
                             long long cx,
                             long long cy,
                             long long z) {
    bool do_disp = (need == "TOUT" || need == "DEPLACEMENT");
    bool do_zoom = (need == "TOUT" || need == "ZOOM");

    Quad out = q;
    if (do_disp) {
        out.x -= cx;
        out.y -= cy;
    }
    if (do_zoom) {
        out.x *= z;
        out.y *= z;
        out.ex *= z;
        out.ey *= z;
    }
    return out;
}

static bool subset_can_express_need(int mask, const std::string& need) {
    // bit 0: IGNORER_CAMERA
    // bit 1: IGNORER_DEPLACEMENT
    // bit 2: IGNORER_ZOOM
    bool has_cam = (mask & 1) != 0;
    bool has_disp = (mask & 2) != 0;
    bool has_zoom = (mask & 4) != 0;

    if (need == "TOUT") {
        return true;
    }
    if (need == "ZOOM") {
        return has_disp && !has_cam;
    }
    if (need == "DEPLACEMENT") {
        return has_zoom && !has_cam;
    }
    if (need == "RIEN") {
        return has_cam || (has_disp && has_zoom);
    }
    return false;
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

    std::string line;
    std::getline(std::cin, line); // fin de ligne CX CY Z

    bool known_cam = false;
    bool known_disp = false;
    bool known_zoom = false;
    int F = 0;

    if (std::getline(std::cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        std::istringstream iss(line);
        iss >> F;
        for (int i = 0; i < F; ++i) {
            std::string flag;
            if (iss >> flag) {
                if (flag == "IGNORER_CAMERA") {
                    known_cam = true;
                } else if (flag == "IGNORER_DEPLACEMENT") {
                    known_disp = true;
                } else if (flag == "IGNORER_ZOOM") {
                    known_zoom = true;
                }
            }
        }
    }

    int N = 0;
    if (!(std::cin >> N)) {
        N = 0;
    }

    long long wrong_count = 0;
    std::vector<std::string> present_needs;
    present_needs.reserve(N > 0 ? static_cast<std::size_t>(N) : 0);

    for (int i = 0; i < N; ++i) {
        std::string name, need;
        Quad orig;
        std::cin >> name >> need >> orig.x >> orig.y >> orig.ex >> orig.ey;
        present_needs.push_back(need);

        bool ign_cam = false;
        bool ign_disp = false;
        bool ign_zoom = false;

        if (need == "RIEN") {
            if (known_cam) {
                ign_cam = true;
            } else if (known_disp && known_zoom) {
                ign_disp = true;
                ign_zoom = true;
            }
        } else if (need == "ZOOM") {
            if (known_disp) {
                ign_disp = true;
            }
        } else if (need == "DEPLACEMENT") {
            if (known_zoom) {
                ign_zoom = true;
            }
        }

        bool apply_disp = !(ign_cam || ign_disp);
        bool apply_zoom = !(ign_cam || ign_zoom);

        Quad rhi = orig;
        if (apply_disp) {
            rhi.x -= cx;
            rhi.y -= cy;
        }
        if (apply_zoom) {
            rhi.x *= z;
            rhi.y *= z;
            rhi.ex *= z;
            rhi.ey *= z;
        }

        Quad exp_q = compute_expected(need, orig, cx, cy, z);
        bool is_ok = (rhi.x == exp_q.x) &&
                     (rhi.y == exp_q.y) &&
                     (rhi.ex == exp_q.ex) &&
                     (rhi.ey == exp_q.ey);

        if (!is_ok) {
            ++wrong_count;
        }

        std::cout << name << ' '
                  << rhi.x << ' ' << rhi.y << ' ' << rhi.ex << ' ' << rhi.ey << ' '
                  << (is_ok ? "JUSTE\n" : "FAUX\n");
    }

    int needed_fields = 0;
    if (!present_needs.empty()) {
        needed_fields = 3;
        for (int mask = 0; mask < 8; ++mask) {
            bool ok_all = true;
            for (const std::string& nd : present_needs) {
                if (!subset_can_express_need(mask, nd)) {
                    ok_all = false;
                    break;
                }
            }
            if (ok_all) {
                int bits = __builtin_popcount(static_cast<unsigned int>(mask));
                if (bits < needed_fields) {
                    needed_fields = bits;
                }
            }
        }
    }

    std::cout << "FAUX " << wrong_count << '\n';
    std::cout << "CHAMPS " << F << '\n';
    std::cout << "CHAMPS NECESSAIRES " << needed_fields << '\n';

    return 0;
}