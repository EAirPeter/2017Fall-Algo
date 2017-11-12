#include <algorithm>
#include <cstddef>
#include <fstream>
#include <random>

using namespace std;

void data(uint32_t n, uint32_t m, ofstream &fo, mt19937 &rng) {
    fo << n << endl;
    auto prev = rng() % m + 1;
    for (uint32_t i = 0; i < n; ++i) {
        auto val = rng() % m + 1;
        fo << prev << ' ' << val << endl;
        prev = val;
    }
    fo << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    ofstream fo("p1-in-big.txt");
    random_device rd;
    mt19937 rng(rd());
    data(400, 200000, fo, rng);
    data(400, 200000, fo, rng);
    return 0;
}
