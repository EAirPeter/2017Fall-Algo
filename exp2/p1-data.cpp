#include <algorithm>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <numeric>
#include <random>

using namespace std;

using Interval = pair<uint32_t, uint32_t>;

mt19937 Rng((uint32_t) chrono::system_clock::now().time_since_epoch().count());

uint32_t Rint(Interval intv) {
    return Rng() % (intv.second - intv.first + 1) + intv.first;
}

constexpr uint32_t MaxN = 100000;
constexpr uint32_t MaxM = 100000;
constexpr uint32_t MaxW = 20000;

uint32_t TV[MaxN], TE[MaxM], EU[MaxM], EV[MaxM], EW[MaxM];

void Print(ofstream &fo, uint32_t n, uint32_t m) {
    fo << n << ' ' << m << endl;
    for (uint32_t i = 0; i < m; ++i)
        fo << EU[TE[i]] << ' ' << EV[TE[i]] << ' ' << EW[TE[i]] << endl;
    fo << endl;
}

void DataA(ofstream &fo, Interval dn, Interval dm) {
    auto n = Rint(dn);
    auto m = Rint(dm);
    iota(TV, TV + n, 1);
    shuffle(TV, TV + n, Rng);
    for (uint32_t i = 0; i < n - 1; ++i) {
        EU[i] = TV[i];
        EV[i] = TV[i + 1];
        EW[i] = Rint({1, MaxW});
    }
    for (uint32_t i = n - 1; i < m; ++i) {
        EU[i] = Rint({1, n});
        EV[i] = Rint({1, n});
        EW[i] = Rint({1, MaxW});
    }
    iota(TE, TE + m, 0);
    shuffle(TE, TE + m, Rng);
    Print(fo, n, m);
}

void DataB(ofstream &fo, Interval dn) {
    auto n = Rint(dn);
    auto m = n - 1;
    for (uint32_t i = 0; i < n - 1; ++i) {
        EU[i] = i + 1;
        EV[i] = i + 2;
        EW[i] = Rint({1, MaxW});
    }
    sort(EW, EW + n - 1);
    iota(TE, TE + m, 0);
    shuffle(TE, TE + m, Rng);
    Print(fo, n, m);
}

void DataC(ofstream &fo, Interval dn) {
    auto n = Rint(dn);
    auto m = n - 1;
    for (uint32_t i = 0; i < n - 1; ++i) {
        EU[i] = i + 2;
        EV[i] = i + 1;
        EW[i] = Rint({1, MaxW});
    }
    sort(EW, EW + n - 1);
    iota(TE, TE + m, 0);
    shuffle(TE, TE + m, Rng);
    Print(fo, n, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    ofstream fo("p1-in-big.txt");
    DataA(fo, {88890, 90000}, {99990, 100000});
    DataA(fo, {9990, 10000}, {99990, 100000});
    DataA(fo, {990, 1000}, {99990, 100000});
    DataA(fo, {310, 320}, {90000, 100000});
    DataA(fo, {90, 100}, {99990, 100000});
    DataA(fo, {1, 1}, {0, 0});
    DataB(fo, {99990, 100000});
    DataC(fo, {99990, 100000});
    return 0;
}
