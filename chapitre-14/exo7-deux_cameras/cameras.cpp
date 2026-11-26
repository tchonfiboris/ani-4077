#include <iostream>
#include <string>
#include <vector>

struct Camera {
    long long cx = 0;
    long long cy = 0;
    long long z = 1;
};

struct SceneObject {
    std::string nature;
    std::string name;
    long long x = 0;
    long long y = 0;
    long long ex = 0;
    long long ey = 0;
};

struct RectBox {
    long long x = 0;
    long long y = 0;
    long long ex = 0;
    long long ey = 0;
};

static RectBox apply_camera(const SceneObject& obj, const Camera& cam) {
    RectBox out;
    out.x = (obj.x - cam.cx) * cam.z;
    out.y = (obj.y - cam.cy) * cam.z;
    out.ex = obj.ex * cam.z;
    out.ey = obj.ey * cam.z;
    return out;
}

static bool is_visible(const RectBox& box, long long L) {
    return (box.x - box.ex <= L) &&
           (box.x + box.ex >= -L) &&
           (box.y - box.ey <= L) &&
           (box.y + box.ey >= -L);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long L = 0;
    if (!(std::cin >> L)) {
        return 0;
    }

    Camera main_cam;
    Camera inset_cam;
    std::cin >> main_cam.cx >> main_cam.cy >> main_cam.z;
    std::cin >> inset_cam.cx >> inset_cam.cy >> inset_cam.z;

    int N = 0;
    std::cin >> N;

    std::vector<SceneObject> objects(N > 0 ? static_cast<std::size_t>(N) : 0);
    for (int i = 0; i < N; ++i) {
        std::cin >> objects[static_cast<std::size_t>(i)].nature
                  >> objects[static_cast<std::size_t>(i)].name
                  >> objects[static_cast<std::size_t>(i)].x
                  >> objects[static_cast<std::size_t>(i)].y
                  >> objects[static_cast<std::size_t>(i)].ex
                  >> objects[static_cast<std::size_t>(i)].ey;
    }

    long long commandes = 0;
    long long ecartees = 0;
    long long calculs = 0;

    std::cout << "PASSE PRINCIPALE\n";
    int visible_main = 0;
    for (const SceneObject& obj : objects) {
        RectBox box;
        if (obj.nature == "MONDE") {
            box = apply_camera(obj, main_cam);
            ++calculs;
        } else {
            box = {obj.x, obj.y, obj.ex, obj.ey};
        }

        if (is_visible(box, L)) {
            std::cout << obj.name << ' ' << box.x << ' ' << box.y << ' ' << box.ex << ' ' << box.ey << '\n';
            ++commandes;
            ++visible_main;
        } else {
            ++ecartees;
        }
    }
    if (visible_main == 0) {
        std::cout << "AUCUN\n";
    }

    std::cout << "PASSE MEDAILLON\n";
    int visible_inset = 0;
    for (const SceneObject& obj : objects) {
        if (obj.nature != "MONDE") {
            continue;
        }
        RectBox box = apply_camera(obj, inset_cam);
        ++calculs;

        if (is_visible(box, L)) {
            std::cout << obj.name << ' ' << box.x << ' ' << box.y << ' ' << box.ex << ' ' << box.ey << '\n';
            ++commandes;
            ++visible_inset;
        } else {
            ++ecartees;
        }
    }
    if (visible_inset == 0) {
        std::cout << "AUCUN\n";
    }

    std::cout << "COMMANDES " << commandes << '\n';
    std::cout << "ECARTEES " << ecartees << '\n';
    std::cout << "CALCULS " << calculs << '\n';

    return 0;
}