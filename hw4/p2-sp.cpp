#include <algorithm>
#include <chrono>
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

uint32_t shortest_path_algorithm(
    const vector<uint32_t> &delta,
    const vector<vector<uint32_t>> &alpha,
    const vector<uint32_t> &s1,
    const vector<uint32_t> &s2
) {
    uint32_t vtx = 0;
    auto src = vtx++;
    vector<vector<uint32_t>> lbl(s1.size());
    for (uint32_t i = 0; i < s1.size(); ++i) {
        lbl[i].reserve(s2.size());
        for (uint32_t j = 0; j < s2.size(); ++j)
            lbl[i].emplace_back(vtx++);
    }
    vector<deque<pair<uint32_t, uint32_t>>> adj(vtx);
    auto &&addedge = [&adj] (auto u, auto v, auto w) {
        adj[u].emplace_back(v, w);
    };
    addedge(src, lbl[0][0], min(delta[s1[0]] + delta[s2[0]], alpha[s1[0]][s2[0]]));
    for (uint32_t pfx = delta[s1[0]], i = 1; i < s1.size(); ++i) {
        auto pfx_ = exchange(pfx, pfx + delta[s1[i]]);
        addedge(src, lbl[i][0], min(
            pfx + delta[s2[0]], pfx_ + alpha[s1[i]][s2[0]]
        ));
        addedge(lbl[i - 1][0], lbl[i][0], delta[s1[i]]);
    }
    for (uint32_t pfx = delta[s2[0]], j = 1; j < s2.size(); ++j) {
        auto pfx_ = exchange(pfx, pfx + delta[s2[j]]);
        addedge(src, lbl[0][j], min(
            pfx + delta[s1[0]], pfx_ + alpha[s1[0]][s2[j]]
        ));
        addedge(lbl[0][j - 1], lbl[0][j], delta[s2[j]]);
    }
    for (uint32_t i = 1; i < s1.size(); ++i)
        for (uint32_t j = 1; j < s2.size(); ++j) {
            addedge(lbl[i - 1][j], lbl[i][j], delta[s1[i]]);
            addedge(lbl[i][j - 1], lbl[i][j], delta[s2[j]]);
            addedge(lbl[i - 1][j - 1], lbl[i][j], alpha[s1[i]][s2[j]]);
        }
    vector<uint32_t> dis(vtx, ~uint32_t {});
    vector<unsigned char> inq(vtx);
    deque<uint32_t> que;
    auto &&enq = [&inq, &que] (auto u) {
        if (!inq[u]) {
            inq[u] = true;
            que.emplace_back(u);
        }
    };
    auto &&deq = [&inq, &que] {
        auto u = que.front();
        que.pop_front();
        inq[u] = false;
        return u;
    };
    dis[src] = 0;
    enq(src);
    while (!que.empty()) {
        auto u = deq();
        for (auto &&[v, w] : adj[u])
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                enq(v);
            }
    }
    return dis[lbl[s1.size() - 1][s2.size() - 1]];
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
        auto ans = shortest_path_algorithm(delta, alpha, s1, s2);
        cout << "minimum penalties: " << ans << endl << endl;
    }
    return 0;
}
