#include <algorithm>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <random>

using namespace std;

using Interval = pair<uint32_t, uint32_t>;

constexpr uint32_t MaxP = 10000;
constexpr uint32_t MaxN = 100;
constexpr uint32_t MaxM = 20;
constexpr uint32_t MaxT = 30;

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

void DataB(
    ofstream &fo, mt19937 &rng,
    uint32_t p, uint32_t n, uint32_t m, uint32_t t
) {
    fo << p << ' ' << n << ' ' << m << ' ' << t << endl;
    uint32_t XStud[12], XProf[12];
    bool VStud[MaxN] {}, VProf[MaxM] {};
    for (uint32_t i = 0; i < 12; ++i) {
        XStud[i] = rng() % n;
        XProf[i] = rng() % m;
        VStud[XStud[i]] = true;
        VProf[XProf[i]] = true;
    }
    uint32_t cnt = 0;
    for (uint32_t i = 0; i < n; ++i)
        for (uint32_t j = 0; j < m; ++j)
            if(!VStud[i] && !VProf[j])
                for (uint32_t k = 0; k < t; ++k)
                    Buf[cnt++] = (i * m + j) * t + k;
    shuffle(Buf, Buf + cnt, rng);
    cnt = p - t * 8;
    for (uint32_t i = 0; i < 12; ++i)
        for (uint32_t j = 0; j < t; ++j)
            Buf[cnt++] = (XStud[i] * m + XProf[i]) * t + j;
    shuffle(Buf + p - t * 8, Buf + cnt, rng);
    shuffle(Buf, Buf + p, rng);
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
    if (p > n * m * t)
        p = rint({n * m * t - dp.second + dp.first, n * m * t});
    f(fo, rng, p, n, m, t);
}

int main() {
    ios_base::sync_with_stdio(false);
    mt19937 rng((uint32_t) chrono::system_clock::now().time_since_epoch().count());
    ofstream fo("in-big.txt");
    for (uint32_t i = 0; i < 4; ++i) {
        Data(fo, rng, DataA, {9000, 10000}, {90, 100}, {16, 20}, {24, 30});
        Data(fo, rng, DataA, {9000, 10000}, {90, 100}, {16, 20}, {24, 30});
        Data(fo, rng, DataA, {9000, 10000}, {90, 100}, {16, 20}, {24, 30});
        Data(fo, rng, DataA, {9000, 10000}, {90, 100}, {16, 20}, {24, 30});
        Data(fo, rng, DataA, {6000, 8000}, {19, 19}, {19, 19}, {28, 30});
        Data(fo, rng, DataA, {6000, 8000}, {19, 19}, {20, 20}, {28, 30});
        Data(fo, rng, DataA, {6000, 8000}, {20, 20}, {19, 19}, {28, 30});
        Data(fo, rng, DataA, {6000, 8000}, {20, 20}, {20, 20}, {28, 30});
        Data(fo, rng, DataB, {9000, 10000}, {90, 100}, {16, 20}, {24, 30});
        Data(fo, rng, DataB, {9000, 10000}, {90, 100}, {16, 20}, {24, 30});
        Data(fo, rng, DataB, {9000, 10000}, {90, 100}, {16, 20}, {24, 30});
        Data(fo, rng, DataB, {9000, 10000}, {90, 100}, {16, 20}, {24, 30});
    }
    return 0;
}
