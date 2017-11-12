#include <algorithm>
#include <cstddef>
#include <fstream>
#include <random>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    ofstream fo("p2-in-big.txt");
    random_device rd;
    mt19937 rng(rd());
    constexpr uint32_t n = 100000;
    fo << n << endl;
    for (uint32_t i = 0; i < n; ++i) {
        auto t1 = rng();
        auto t2 = rng();
        auto [sta, fin] = minmax(t1, t2);
        fo << sta << ' ' << fin << endl;
    }
    return 0;
}
