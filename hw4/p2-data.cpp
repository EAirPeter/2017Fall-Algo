#include <algorithm>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <random>

using namespace std;

using interval = pair<uint32_t, uint32_t>;

void data(
    uint32_t nch, const interval &delta, const interval (&alpha)[2],
    uint32_t len_, ofstream &fo, mt19937 &rng
) {
    auto &&rint = [&rng] (const interval &intv) {
        return rng() % (intv.second - intv.first + 1) + intv.first;
    };
    fo << nch << endl;
    for (uint32_t i = 1; i < nch; ++i)
        fo << rint(delta) << ' ';
    fo << rint(delta) << endl;
    for (uint32_t i = 0; i < nch; ++i) {
        for (uint32_t j = 1; j < nch; ++j)
            fo << rint(alpha[i != j - 1]) << ' ';
        fo << rint(alpha[i != nch - 1]) << endl;
    }
    for (uint32_t j = 0; j < 2; ++j) {
        auto len = len_ - rint({0, 10});
        fo << len << endl;
        for (uint32_t i = 1; i < len; ++i)
            fo << rint({0, nch - 1}) << ' ';
        fo << rint({0, nch - 1}) << endl;
    }
    fo << endl;
}

void datafile(const char *file, uint32_t len, mt19937 &rng) {
    ofstream fo(file);
    data(64, {1, 1}, {{0, 0}, {1, 1}}, len, fo, rng);
    data(64, {1, 20000}, {{0, 0}, {1, 20000}}, len, fo, rng);
    data(64, {1, 10000}, {{0, 0}, {10001, 20000}}, len, fo, rng);
    data(64, {10001, 20000}, {{0, 0}, {1, 10000}}, len, fo, rng);
    data(64, {0, 20000}, {{0, 20000}, {0, 20000}}, len, fo, rng);
    data(64, {0, 10000}, {{10001, 20000}, {0, 10000}}, len, fo, rng);
}

int main() {
    ios_base::sync_with_stdio(false);
    mt19937 rng((uint32_t) chrono::system_clock::now().time_since_epoch().count());
    datafile("p2-in-big.txt", 1000, rng);
    datafile("p2-in-huge.txt", 10000, rng);
    return 0;
}
