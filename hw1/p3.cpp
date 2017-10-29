#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct task {
    double sta; // start time
    double fin; // finish time
    double val; // value
    size_t id;  // id
};

struct state {
                // when considering tasks[0..i] (sorted)
    double val; // maximum value
    size_t idx; // index of the last selected task, ~0 represents that this is the first one
    bool sel;   // whether tasks[i] is selected
};

size_t ntask;           // number of tasks
vector<task> tasks;     // tasks
vector<state> states;   // states, for dynamic programming use
vector<size_t> answer;  // answer to print


void ism() {
    // dynamic programming approach
    sort(
        tasks.begin(), tasks.end(),
        [] (auto &lhs, auto &rhs) {
            return lhs.fin != rhs.fin ? lhs.fin < rhs.fin : lhs.id < rhs.id;
        }
    );
    states.resize(ntask);
    // considering if there exists a task with negative value
    states[0].sel = tasks[0].val > 0.0;
    states[0].val = tasks[0].val > 0.0 ? tasks[0].val : 0.0;
    states[0].idx = ~ size_t {};
    for (size_t i = 1; i < tasks.size(); ++i) {
        auto it = upper_bound(
            tasks.begin(), tasks.begin() + (ptrdiff_t) i, tasks[i].sta,
            [] (auto val, auto &tsk) {
                return val < tsk.fin;
            }
        );
        // it == tasks.begin() means the current task conflicts with all previous tasks
        // the last task that does not conflict with the current one
        auto prev = it == tasks.begin() ? ~size_t {} : (size_t) (it - tasks.begin()) - 1;
        // if select task i 
        auto vsel = it == tasks.begin() ? tasks[i].val : states[prev].val + tasks[i].val;
        // if not
        auto vnot = states[i - 1].val;
        if (vsel > vnot) {
            states[i].val = vsel;
            states[i].idx = states[prev].sel ? prev : states[prev].idx;
            states[i].sel = true;
        }
        else {
            states[i].val = vnot;
            states[i].idx = states[i - 1].sel ? i - 1 : states[i - 1].idx;
            states[i].sel = false;
        }
    }
    answer.clear();
    for (auto i = states.back().sel ? ntask - 1 : states.back().idx;
        i != ~size_t {}; i = states[i].idx)
    {
        answer.push_back(tasks[i].id);
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
            cin >> tsk.sta >> tsk.fin >> tsk.val;
            tsk.id = cnt++;
        }
        ism();
        cout << "maximum value = " << states.back().val;
        cout << ", selecting " << answer.size() << " tasks:";
        for (auto id : answer)
            cout << ' ' << id;
        cout << endl << endl;
    }
    return 0;
}
