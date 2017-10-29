#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct task {
    double sta; // start time
    double fin; // finish time
    size_t id;  // id
};

size_t ntask;           // number of tasks
vector<task> tasks;     // tasks
vector<size_t> answer;  // answer to print

void ism() {
    // greedy approach
    sort(
        tasks.begin(), tasks.end(),
        [] (auto &lhs, auto &rhs) {
            return lhs.fin != rhs.fin ? lhs.fin < rhs.fin : lhs.id < rhs.id;
        }
    );
    answer.clear();
    double finish = -1.0;
    for (auto &tsk : tasks)
        if (tsk.sta >= finish) {
            finish = tsk.fin;
            answer.push_back(tsk.id);
        }
    sort(answer.begin(), answer.end());
}

int main() {
    ios_base::sync_with_stdio(false);
    // capable of accepting multiple sets of input
    while (cin >> ntask) {
        tasks.resize(ntask);
        size_t cnt = 0;
        for (auto &tsk : tasks) {
            cin >> tsk.sta >> tsk.fin;
            tsk.id = cnt++;
        }
        ism();
        cout << "maximum tasks = " << answer.size() << ", selecting:";
        for (auto id : answer)
            cout << ' ' << id;
        cout << endl << endl;
    }
    return 0;
}
