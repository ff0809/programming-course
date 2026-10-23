#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct PuzzleState {
    string board;
    int steps;
};

class SlidingPuzzleSolver {
private:
    vector<vector<int>> board;
    const string target = "123450";
    const vector<vector<int>> neighbors = {
        {1, 3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {2, 4}
    };

public:
    SlidingPuzzleSolver() : board(2, vector<int>(3, 0)) {}

    void inputData() {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 3; ++j) {
                cin >> board[i][j];
            }
        }
    }

    // BFS分支限界
    int solve() {
        string start = "";
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 3; ++j) {
                start += to_string(board[i][j]);
            }
        }

        queue<PuzzleState> q;
        unordered_set<string> visited;

        q.push({ start, 0 });
        visited.insert(start);

        while (!q.empty()) {
            PuzzleState curr = q.front();
            q.pop();

            if (curr.board == target) {
                return curr.steps;
            }

            int zero_idx = curr.board.find('0');
            for (int next_idx : neighbors[zero_idx]) {
                string nextboard = curr.board;
                swap(nextboard[zero_idx], nextboard[next_idx]);
                if (visited.find(nextboard) == visited.end()) {
                    q.push({ nextboard, curr.steps + 1 });
                    visited.insert(nextboard);
                }
            }
        }
        return -1;
    }

    void printOutput(int result) {
        cout << result << endl;
    }
};

int main() {
    SlidingPuzzleSolver solver;

    solver.inputData();
    int ans = solver.solve();
    solver.printOutput(ans);

    return 0;
}