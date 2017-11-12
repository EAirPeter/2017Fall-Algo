#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct process {
    uint32_t sta; // start time
    uint32_t fin; // finish time
};


vector<uint32_t> an_efficient_algorithm(vector<process> proces) {
    // greedy approach
    sort(
        proces.begin(), proces.end(),
        [] (auto &lhs, auto &rhs) {
            return lhs.fin != rhs.fin ? lhs.fin < rhs.fin : lhs.sta < rhs.sta;
        }
    );
    vector<uint32_t> answer;
    for (auto &prc : proces)
        if (answer.empty() || answer.back() < prc.sta)
            answer.emplace_back(prc.fin);
    return move(answer);
}

int main() {
    ios_base::sync_with_stdio(false);
    // capable of accepting multiple sets of input
    size_t nproces;
    while (cin >> nproces) {
        vector<process> proces(nproces);
        for (auto &prc : proces)
            cin >> prc.sta >> prc.fin;
        auto answer = an_efficient_algorithm(move(proces));
        cout << "select " << answer.size() << " time points:";
        for (auto time : answer)
            cout << ' ' << time;
        cout << endl << endl;
    }
    return 0;
}
