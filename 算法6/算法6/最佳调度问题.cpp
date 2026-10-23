#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <algorithm>
#include <climits>

using namespace std;

struct Node {
    int level;             
    vector<int> m_times;     
    int max_time;           

    // 结构体比较：最慢时间越短的节点，优先级越高（小顶堆）
    bool operator<(const Node& other) const {
        return max_time > other.max_time;
    }
};

class BestSchedulingSolver {
private:
    int n;                   
    int k;                  
    vector<int> t;          
    int best_time;          

public:
    BestSchedulingSolver() : n(0), k(0), best_time(INT_MAX) {}

    void inputData() {
        cin >> n >> k;
        t.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> t[i];
        }
        sort(t.begin(), t.end(), greater<int>());//时间长的任务排在前面，加速后续剪枝
    }
    void printOutput() {
        cout << best_time << endl;
    }
    void solve() {
        priority_queue<Node>pq;
        best_time = INT_MAX;
        Node root = { 0,vector<int>(k,0),0 };
        pq.push(root);
        while (!pq.empty()) {
            Node curr = pq.top();
            pq.pop();
            if (curr.max_time >= best_time)continue;
            if (curr.level == n) {
                if (curr.max_time < best_time)best_time = curr.max_time;
                continue;
            }
            for (int i = 0; i < k; i++) {
                Node newnode = curr;
                newnode.m_times[i] += t[curr.level];
                newnode.level = curr.level + 1;
                newnode.max_time = 0;
                for (int time : newnode.m_times) {
                    newnode.max_time = max(newnode.max_time, time);
                }
                if (newnode.max_time < best_time)pq.push(newnode);
            }
        }
    }
};

int main() {
    BestSchedulingSolver solver;

    solver.inputData();   
    solver.solve();     
    solver.printOutput();

    return 0;
}