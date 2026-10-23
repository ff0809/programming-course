#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int r_cap[205][205]; 
int parent[205];   
int M, N;

bool bfs(int s, int t) {
    memset(parent, -1, sizeof(parent));
    queue<int> q;

    q.push(s);
    parent[s] = s;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 1; v <= N; v++) {
            if (parent[v] == -1 && r_cap[u][v] > 0) {
                parent[v] = u; 
                if (v == t) return true; 
                q.push(v);
            }
        }
    }
    return false; 
}

int edmonds_karp(int s, int t) {
    int max_flow = 0;

    while (bfs(s, t)) {
        int path_flow = INF;

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, r_cap[u][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            r_cap[u][v] -= path_flow; 
            r_cap[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() 
{
    while (cin >> M >> N) {
        memset(r_cap, 0, sizeof(r_cap));

        for (int i = 0; i < M; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            r_cap[u][v] += c; 
        }

        cout << edmonds_karp(1, N) << "\n";
    }
    return 0;
}