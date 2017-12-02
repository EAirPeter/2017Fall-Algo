#include <algorithm>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <random>

using namespace std;

using Interval = pair<uint32_t, uint32_t>;

constexpr uint32_t MaxP = 16;
constexpr uint32_t MaxN = 12;
constexpr uint32_t MaxM = 16;
constexpr uint32_t MaxT = 12;

uint32_t Buf[MaxN * MaxM * MaxT];

void DataA(
    ofstream &fo, mt19937 &rng,
    uint32_t p, uint32_t n, uint32_t m, uint32_t t
) {
    fo << p << ' ' << n << ' ' << m << ' ' << t << endl;
    auto tot = n * m * t;
    for (uint32_t i = 0; i < tot; ++i)
        Buf[i] = i;
    shuffle(Buf, Buf + tot, rng);
    for (uint32_t i = 0; i < p; ++i) {
        auto stud = Buf[i] / (m * t) + 1;
        auto prof = Buf[i] % (m * t) / t + 1;
        auto time = Buf[i] % t + 1;
        fo << stud << ' ' << prof  << ' ' << time << endl;
    }
    fo << endl;
}

template<class F>
void Data(
    ofstream &fo, mt19937 &rng, F f,
    const Interval &dp, const Interval &dn, const Interval &dm, const Interval &dt
) {
    auto &&rint = [&rng] (const Interval &intv) {
        return rng() % (intv.second - intv.first + 1) + intv.first;
    };
    auto n = rint(dn);
    auto m = rint(dm);
    auto t = rint(dt);
    auto p = rint(dp);
    f(fo, rng, p, n, m, t);
}

int main() {
    ios_base::sync_with_stdio(false);
    mt19937 rng((uint32_t) chrono::system_clock::now().time_since_epoch().count());
    ofstream fo("in-small.txt");
    for (uint32_t i = 0; i < 8; ++i) {
        Data(fo, rng, DataA, {18, 20}, {9, 12}, {8, 16}, {6, 12});
        Data(fo, rng, DataA, {18, 20}, {9, 12}, {8, 16}, {6, 12});
        Data(fo, rng, DataA, {18, 20}, {9, 12}, {8, 16}, {6, 12});
        Data(fo, rng, DataA, {18, 20}, {9, 12}, {8, 16}, {6, 12});
        Data(fo, rng, DataA, {16, 20}, {12, 12}, {12, 12}, {8, 12});
        Data(fo, rng, DataA, {16, 20}, {12, 12}, {16, 16}, {8, 12});
        Data(fo, rng, DataA, {16, 20}, {16, 16}, {12, 12}, {8, 12});
        Data(fo, rng, DataA, {16, 20}, {16, 16}, {16, 16}, {8, 12});
    }
    return 0;
}
