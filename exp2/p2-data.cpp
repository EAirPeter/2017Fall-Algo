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
constexpr uint32_t MaxK = 100000;

uint32_t TD[MaxN];

void Print(ofstream &fo, uint32_t n, uint32_t k) {
    fo << n << ' ' << k << endl;
    for (uint32_t i = 0; i < n; ++i)
        fo << TD[i] << ' ';
    fo << endl << endl;
}

void DataA(ofstream &fo, Interval dn, Interval dd, uint32_t vd) {
    auto n = Rint(dn);
    auto k = Rint({1, n});
    auto bd = Rint(dd);
    for (uint32_t i = 0; i < n; ++i)
        TD[i] = Rint({bd, bd + vd});
    Print(fo, n, k);
}

void DataB(ofstream &fo, Interval dn, Interval dd, uint32_t vd) {
    auto n = Rint(dn);
    auto k = uint32_t {1};
    auto bd = Rint(dd);
    for (uint32_t i = 0; i < n; ++i)
        TD[i] = Rint({bd, bd + vd});
    Print(fo, n, k);
}

void DataC(ofstream &fo, Interval dn, Interval dd, uint32_t vd) {
    auto n = Rint(dn);
    auto k = n;
    auto bd = Rint(dd);
    for (uint32_t i = 0; i < n; ++i)
        TD[i] = Rint({bd, bd + vd});
    Print(fo, n, k);
}

void DataD(ofstream &fo, Interval dn, Interval dd, uint32_t vk) {
    auto n = Rint(dn);
    auto p = Rint({1, n - 2});
    auto k = p + vk;
    auto d1 = Rint({dd.first, dd.second - 1});
    auto d2 = Rint({d1 + 1, dd.second});
    for (uint32_t i = 0; i < p; ++i)
        TD[i] = d1;
    for (uint32_t i = p; i < n; ++i)
        TD[i] = d2;
    shuffle(TD, TD + n, Rng);
    Print(fo, n, k);
}

int main() {
    ios_base::sync_with_stdio(false);
    ofstream fo("p2-in-big.txt");
    DataA(fo, {99900, 100000}, {0, 0}, 2000000000);
    DataB(fo, {39990, 40000}, {0, 0}, 2000000000);
    DataC(fo, {39990, 40000}, {0, 0}, 2000000000);
    DataA(fo, {39990, 40000}, {0, 1999999900}, 100);
    DataB(fo, {39990, 40000}, {0, 1999999900}, 100);
    DataC(fo, {39990, 40000}, {0, 1999999900}, 100);
    DataA(fo, {39990, 40000}, {0, 1999999990}, 10);
    DataB(fo, {39990, 40000}, {0, 1999999990}, 10);
    DataC(fo, {39990, 40000}, {0, 1999999990}, 10);
    DataA(fo, {39990, 40000}, {0, 2000000000}, 0);
    DataB(fo, {39990, 40000}, {0, 2000000000}, 0);
    DataC(fo, {39990, 40000}, {0, 2000000000}, 0);
    DataD(fo, {39990, 40000}, {0, 2000000000}, 0);
    DataD(fo, {39990, 40000}, {0, 2000000000}, 1);
    DataD(fo, {39990, 40000}, {0, 2000000000}, 2);
    return 0;
}
