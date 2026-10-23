#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct GridState {
    int x, y;  
    int remain; 
    int steps;  
};

class ShortestPathSolver {
private:
    int m, n, k;             
    vector<vector<int>> grid;  // 存放地图数据（0为空地，1为砖墙）

public:
    ShortestPathSolver() : m(0), n(0), k(0) {}

    void inputData() {
        if (!(cin >> m >> n >> k)) return;

        grid.assign(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> grid[i][j];
            }
        }
    }

    void printOutput(int result) {
        cout << result << endl;
    }

    int solve() {
        if (m == 1 && n == 1)return 0;
        if (k >= m + n - 2)return m + n - 2;
        queue<GridState>q;
        q.push({ 0, 0, k, 0 });
        int dx[4] = { -1,1,0,0 };
        int dy[4] = { 0,0,-1,1 };
        vector<vector<int>>visited(m, vector<int>(n, -1));
        visited[0][0] = k;
        while (!q.empty()) {
            GridState curr=q.front();
            q.pop();
            if (curr.x == m - 1 && curr.y == n - 1)return curr.steps;
            for (int i = 0; i < 4; i++) {
                int x = curr.x + dx[i];
                int y = curr.y + dy[i];
                if (x >= 0 && x < m && y >= 0 && y < n) {
                    int next_remain = curr.remain-grid[x][y];
                    if (next_remain >= 0 && next_remain > visited[x][y]) {
                        visited[x][y] = next_remain;
                        q.push({x, y, next_remain, curr.steps + 1});
                    }
                }
            }
        }
        return -1;
    }
};

int main() {
    ShortestPathSolver solver;

    solver.inputData();            
    int ans = solver.solve();        
    solver.printOutput(ans);   

    return 0;
}