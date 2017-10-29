#include <cstring>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

size_t row, col;
vector<string> grd;                 // the original input
vector<pair<size_t, size_t>> bla;   // the coordinate of black grids
vector<pair<size_t, size_t>> whi;   // the coordinate of white grids
vector<vector<size_t>> lbl;         // the label of a grid, mapping to the original input
vector<vector<size_t>> adj;         // list of white grids which are adjacent to a black grid
vector<unsigned char> vis;          // whether a white grid has been visited
vector<size_t> mat;                 // which black grid is matched with a white grid

bool match(size_t lb) {
    // dertermine whether the black grid can be matched with a white grid
    // a part of hungarian algorithm
    for (auto lw : adj[lb])
        if (!vis[lw]) {
            vis[lw] = true;
            if (!~mat[lw] || match(mat[lw])) {
                // the white grid has not been used before
                // or a match is found for the previous black grid matched with the white grid
                mat[lw] = lb;
                return true;
            }
        }
    return false;
}

bool tiling() {
    // separate grids into black and white ones
    // black grid if ((i + j) % 2 == 0), white if not
    lbl.resize(row);
    bla.clear();
    whi.clear();
    for (size_t i = 0; i < row; ++i) {
        lbl[i].resize(col);
        for (size_t j = 0; j < col; ++j)
            if (grd[i][j] == '.') {
                if ((i + j) % 2) {
                    // white grid
                    lbl[i][j] = whi.size();
                    whi.emplace_back(i, j);
                }
                else {
                    // black grid
                    lbl[i][j] = bla.size();
                    bla.emplace_back(i, j);
                }
            }
    }
    if (bla.size() != whi.size()) {
        // of course there is no solution
        return false;
    }
    adj.resize(bla.size());
    for (size_t lb = 0; lb < bla.size(); ++lb) {
        auto &&addadj = [lb](auto x, auto y) {
            // test whether the coordinate (x, y) is valid
            // and the grid at (x, y) is available
            if (x < row && y < col && grd[x][y] == '.') {
                adj[lb].push_back(lbl[x][y]);
            }
        };
        auto [x, y] = bla[lb];
        adj[lb].clear();
        addadj(x - 1, y);
        addadj(x + 1, y);
        addadj(x, y - 1);
        addadj(x, y + 1);
    }
    // implementing hungarian algorithm
    mat.resize(whi.size());
    memset(mat.data(), 0xff, sizeof(size_t) * mat.size());
    vis.resize(whi.size());
    for (size_t lb = 0; lb < bla.size(); ++lb) {
        memset(vis.data(), 0, sizeof(unsigned char) * vis.size());
        if (!match(lb)) {
            // there is no white grid for the black grid, no solution
            return false;
        }
    }
    // every black grid is matched with a white grid
    // the tiling solution is represented by mat
    return true;
}

void print() {
    string revn(col * 2 + 1, '+');
    string rodd(col * 2 + 1, '|');
    for (size_t i = 0; i < col; ++i) {
        revn[i * 2 + 1] = '-';
        rodd[i * 2 + 1] = ' ';
    }
    vector<string> out(row * 2 + 1);
    for (size_t i = 0; i < row; ++i) {
        out[i * 2] = revn;
        out[i * 2 + 1] = rodd;
    }
    out.back() = revn;
    for (size_t i = 0; i < row; ++i)
        for (size_t j = 0; j < col; ++j)
            if (grd[i][j] != '.')
                out[i * 2 + 1][j * 2 + 1] = '#';
    for (size_t lw = 0; lw < whi.size(); ++lw) {
        auto lb = mat[lw];
        auto [bx, by] = bla[lb];
        auto [wx, wy] = whi[lw];
        out[bx + wx + 1][by + wy + 1] = ' ';
    }
    for (auto &s : out)
        cout << s << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    // capable of accepting multiple sets of input
    while (cin >> row >> col) {
        grd.resize(row);
        for (size_t i = 0; i < row; ++i)
            cin >> grd[i];
        auto ans = tiling();
        if (ans) {
            cout << "yes" << endl;
            print();
        }
        else {
            cout << "no" << endl;
        }
        cout << endl;
    }
    return 0;
}
