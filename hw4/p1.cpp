#include <algorithm>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct matrix {
    uint32_t row;   // rows
    uint32_t col;   // columns
};

uint64_t the_algorithm(vector<matrix> mats) {
    // dynamic programming approach
    // f[i][j] = minimum scalar multiplications needed for mats[i..j]
    // the final answer is f[0][mats.size() - 1]
    vector<vector<uint64_t>> f(mats.size(), vector<uint64_t>(mats.size(), ~uint64_t {}));
    for (uint32_t j = 0; j < mats.size(); ++j) {
        f[j][j] = 0;
        for (uint32_t i = j - 1; i < j; --i) {
            for (uint32_t k = i; k < j; ++k) {
                f[i][j] = min(
                    f[i][j],
                    f[i][k] + f[k + 1][j] + (uint64_t)
                    mats[i].row * mats[k].col * mats[j].col
                );
            }
        }
    }
    return f[0][mats.size() - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    // timing
    using namespace chrono;
    high_resolution_clock::duration tot {};
    // capable of accepting multiple sets of input
    size_t nmat;
    while (cin >> nmat) {
        vector<matrix> mats(nmat);
        for (auto &mat : mats)
            cin >> mat.row >> mat.col;
        auto sta = high_resolution_clock::now();
        auto ans = the_algorithm(move(mats));
        auto fin = high_resolution_clock::now();
        cout << "minimum scalar multiplications: " << ans << endl << endl;
        tot += fin - sta;
    }
    cerr << "total time: ";
    cerr << duration_cast<microseconds>(tot).count() << " us" << endl;
    return 0;
}
