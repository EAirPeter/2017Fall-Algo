#include <algorithm>
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

uint32_t dynamic_programming_algorithm(
    const vector<uint32_t> &delta,
    const vector<vector<uint32_t>> &alpha,
    const vector<uint32_t> &s1_,
    const vector<uint32_t> &s2_
) {
    auto s1 = s1_.data() - 1;
    auto s2 = s2_.data() - 1;
    vector<uint32_t> f;
    f.reserve(s2_.size() + 1);
    f.emplace_back();
    for (uint32_t j = 1; j <= s2_.size(); ++j)
        f.emplace_back(f.back() + delta[s2[j]]);
    for (uint32_t i = 1; i <= s1_.size(); ++i) {
        auto f_ = exchange(f[0], f[0] + delta[s1[i]]);
        for (uint32_t j = 1; j <= s2_.size(); ++j) {
            f_ = exchange(f[j], min(f_ + alpha[s1[i]][s2[j]],
                min(f[j] + delta[s1[i]], f[j - 1] + delta[s2[j]])
            ));
        }
    }
    return f[s2_.size()];
}

int main() {
    ios_base::sync_with_stdio(false);
    // capable of accepting multiple sets of input
    size_t nchset;
    while (cin >> nchset) {
        vector<uint32_t> delta(nchset);
        vector<vector<uint32_t>> alpha(nchset, vector<uint32_t>(nchset));
        for (uint32_t i = 0; i < nchset; ++i)
            cin >> delta[i];
        for (uint32_t i = 0; i < nchset; ++i)
            for (uint32_t j = 0; j < nchset; ++j)
                cin >> alpha[i][j];
        size_t ns1, ns2;
        cin >> ns1;
        vector<uint32_t> s1(ns1);
        for (uint32_t i = 0; i < ns1; ++i)
            cin >> s1[i];
        cin >> ns2;
        vector<uint32_t> s2(ns2);
        for (uint32_t i = 0; i < ns2; ++i)
            cin >> s2[i];
        auto ans = dynamic_programming_algorithm(delta, alpha, s1, s2);
        cout << "minimum penalties: " << ans << endl << endl;
    }
    return 0;
}
