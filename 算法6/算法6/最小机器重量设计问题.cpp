#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Node {
    int level;        
    int cp;           
    int cw;           
    vector<int> path;  

    // 重载 < 运算符，使权重小的节点优先出队（构造小顶堆）
    bool operator<(const Node& other) const {
        return cw > other.cw;
    }
};

class MachineDesignSolver {
private:
    int n, m, d;                   
    vector<vector<int>> c;         
    vector<vector<int>> w;        
    int bestw;                   
    vector<int> best_path;         

public:
    MachineDesignSolver() : n(0), m(0), d(0), bestw(INT_MAX) {}

    void inputData() {
        cin >> n >> m >> d;

        c.assign(n, vector<int>(m));
        w.assign(n, vector<int>(m));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> c[i][j];
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> w[i][j];
            }
        }
    }

    void printOutput() {
        cout << bestw << endl;
        for (int i = 0; i < n; ++i) {
            cout << best_path[i] << (i == n - 1 ? "" : " ");
        }
        cout << endl;
    }

    void solve() {
        priority_queue<Node>pq;
        bestw = INT_MAX;
        Node root = { 0,0,0,{} };
        pq.push(root);
        while (!pq.empty()) {
            Node curr = pq.top();
            pq.pop();
            if (curr.cw >= bestw)continue;
            if (curr.level == n) {
                if (curr.cw < bestw) {
                    bestw = curr.cw;
                    best_path = curr.path;
                }
                continue;
            }
            for (int i = 0; i < m; i++) {
                int nextcw = curr.cw + w[curr.level][i];
                int nextcp = curr.cp + c[curr.level][i];
                if (nextcw < bestw && nextcp <= d) {
                    Node nextnode;
                    nextnode.level = curr.level + 1;
                    nextnode.cp = nextcp;
                    nextnode.cw = nextcw;
                    nextnode.path = curr.path;
                    nextnode.path.push_back(i + 1);
                    pq.push(nextnode);
                }
            }
        }
    }
};

int main() {
    MachineDesignSolver solver;
    solver.inputData();   
    solver.solve();        
    solver.printOutput();  
    return 0;
}