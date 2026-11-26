#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct TypeInfo {
    long long size = 0;
    long long align = 1;
};

static long long align_up(long long value, long long align) {
    if (align <= 1) {
        return value;
    }
    long long rem = value % align;
    if (rem == 0) {
        return value;
    }
    return value + (align - rem);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string target_kw;
    int bits = 64;
    if (!(std::cin >> target_kw >> bits)) {
        return 0;
    }

    const long long ptr_size = (bits == 32) ? 4LL : 8LL;

    std::unordered_map<std::string, TypeInfo> types;
    types["bool"] = {1LL, 1LL};
    types["int"] = {4LL, 4LL};
    types["float"] = {4LL, 4LL};
    types["pointeur"] = {ptr_size, ptr_size};

    int S = 0;
    if (!(std::cin >> S)) {
        S = 0;
    }

    std::unordered_map<std::string, long long> struct_sizes;
    struct_sizes.reserve(static_cast<std::size_t>(S) * 2 + 1);

    for (int i = 0; i < S; ++i) {
        std::string kw, sname;
        int K = 0;
        std::cin >> kw >> sname >> K;

        long long cursor = 0;
        long long raw_sum = 0;
        long long max_align = 1;

        for (int f = 0; f < K; ++f) {
            std::string ftype;
            long long count = 1;
            std::cin >> ftype >> count;

            TypeInfo info = types[ftype];
            long long field_bytes = info.size * count;

            cursor = align_up(cursor, info.align);
            cursor += field_bytes;
            raw_sum += field_bytes;
            max_align = std::max(max_align, info.align);
        }

        long long total_size = align_up(cursor, max_align);
        long long loss = total_size - raw_sum;

        types[sname] = {total_size, max_align};
        struct_sizes[sname] = total_size;

        std::cout << sname
                  << " TAILLE " << total_size
                  << " ALIGNEMENT " << max_align
                  << " PERTE " << loss << '\n';
    }

    int E = 0;
    if (std::cin >> E) {
        for (int i = 0; i < E; ++i) {
            std::string kw, nameA, nameB;
            std::cin >> kw >> nameA >> nameB;
            long long diff = struct_sizes[nameA] - struct_sizes[nameB];
            std::cout << "ECART " << nameA << ' ' << nameB << ' ' << diff << '\n';
        }
    }

    return 0;
}