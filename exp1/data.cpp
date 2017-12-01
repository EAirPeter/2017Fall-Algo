#include <chrono>
#include <cstdint>
#include <fstream>
#include <random>

using namespace std;

constexpr uint32_t MaxP = 10000;
constexpr uint32_t MaxN = 100;
constexpr uint32_t MaxM = 20;
constexpr uint32_t MaxT = 30;

int main() {
    ios_base::sync_with_stdio(false);
    mt19937 rng((uint32_t) chrono::system_clock::now().time_since_epoch().count());
    ofstream fo("in-big.txt");
    for (uint32_t i = 0; i < 40; ++i) {
        auto n = MaxN - 20 + rng() % 21;
        auto m = MaxM - 4 + rng() % 5;
        auto t = MaxT - 6 + rng() % 7;
        auto maxp = min(MaxP, n * m * t);
        auto p = maxp - 200 + rng() % 201;
        fo << p << ' ' << n << ' ' << m << ' ' << t << endl;
        for (uint32_t j = 0; j < p; ++j) {
            auto u = rng() % n + 1;
            auto v = rng() % m + 1;
            auto w = rng() % t + 1;
            fo << u << ' ' << v << ' ' << w << endl;
        }
        fo << endl;
    }
    return 0;
}
