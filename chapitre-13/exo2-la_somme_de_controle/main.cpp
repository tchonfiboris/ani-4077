#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct ImageData {
    int width = 0;
    int height = 0;
    std::vector<uint8_t> rgb; // taille = width * height * 3
    uint64_t byte_count = 0;
    uint32_t checksum = 0;
};

static uint32_t adler32_bytes(const std::string& header, const std::vector<uint8_t>& pixels) {
    constexpr uint64_t MOD = 65521;
    uint64_t a = 1;
    uint64_t b = 0;

    for (unsigned char ch : header) {
        a = (a + static_cast<uint64_t>(ch)) % MOD;
        b = (b + a) % MOD;
    }

    for (uint8_t px : pixels) {
        a = (a + static_cast<uint64_t>(px)) % MOD;
        b = (b + a) % MOD;
    }

    return static_cast<uint32_t>((b << 16) + a);
}

static bool read_image(ImageData& img) {
    std::string tag;
    int w = 0;
    int h = 0;
    if (!(std::cin >> tag >> w >> h)) {
        return false;
    }

    img.width = w;
    img.height = h;

    const std::size_t total_samples = static_cast<std::size_t>(w) * static_cast<std::size_t>(h) * 3;
    img.rgb.resize(total_samples);

    for (std::size_t i = 0; i < total_samples; ++i) {
        int val = 0;
        std::cin >> val;
        img.rgb[i] = static_cast<uint8_t>(val);
    }

    std::ostringstream oss;
    oss << "P6\n" << w << ' ' << h << "\n255\n";
    const std::string header = oss.str();

    img.byte_count = static_cast<uint64_t>(header.size()) + static_cast<uint64_t>(total_samples);
    img.checksum = adler32_bytes(header, img.rgb);
    return true;
}

static void print_image_summary(char label, const ImageData& img) {
    std::cout << label
              << " TAILLE " << img.width << ' ' << img.height
              << " OCTETS " << img.byte_count
              << " SOMME " << std::hex << std::setw(8) << std::setfill('0') << img.checksum
              << std::dec << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ImageData imgA, imgB;
    if (!read_image(imgA) || !read_image(imgB)) {
        return 0;
    }

    print_image_summary('A', imgA);
    print_image_summary('B', imgB);

    if (imgA.checksum == imgB.checksum) {
        std::cout << "IDENTIQUES OUI\n";
    } else {
        std::cout << "IDENTIQUES NON\n";
    }

    if (imgA.width != imgB.width || imgA.height != imgB.height) {
        std::cout << "DIFFERENCES TAILLE\n";
        std::cout << "PREMIERE AUCUNE\n";
        return 0;
    }

    uint64_t diff_pixels = 0;
    bool has_first = false;
    int first_x = 0;
    int first_y = 0;

    for (int y = 0; y < imgA.height; ++y) {
        for (int x = 0; x < imgA.width; ++x) {
            const std::size_t idx = (static_cast<std::size_t>(y) * static_cast<std::size_t>(imgA.width) +
                                     static_cast<std::size_t>(x)) * 3;
            bool px_diff = (imgA.rgb[idx] != imgB.rgb[idx]) ||
                           (imgA.rgb[idx + 1] != imgB.rgb[idx + 1]) ||
                           (imgA.rgb[idx + 2] != imgB.rgb[idx + 2]);
            if (px_diff) {
                ++diff_pixels;
                if (!has_first) {
                    has_first = true;
                    first_x = x;
                    first_y = y;
                }
            }
        }
    }

    std::cout << "DIFFERENCES " << diff_pixels << '\n';
    if (has_first) {
        std::cout << "PREMIERE " << first_x << ' ' << first_y << '\n';
    } else {
        std::cout << "PREMIERE AUCUNE\n";
    }

    return 0;
}