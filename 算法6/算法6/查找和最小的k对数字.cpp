#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
struct Element {
    int sum; 
    int i;   
    int j;  

    bool operator<(const Element& other) const {
        return sum > other.sum;
    }
};

class KSmallestPairsSolver {
private:
    int n, m, k;                
    vector<int> nums1;
    vector<int> nums2;
    vector<vector<int>> ans;  

public:
    KSmallestPairsSolver() : n(0), m(0), k(0) {}

    void inputData() {
        if (!(cin >> n >> m >> k)) return;

        nums1.resize(n);
        nums2.resize(m);

        for (int i = 0; i < n; ++i) cin >> nums1[i];
        for (int i = 0; i < m; ++i) cin >> nums2[i];
    }
    void printOutput() {
        for (size_t i = 0; i < ans.size(); ++i) {
            cout << ans[i][0] << " " << ans[i][1] << endl;
        }
    }
    void solve() {
        priority_queue<Element>pq;
        for (int i = 0; i < min(n, k); i++) {
            pq.push({ nums1[i]+nums2[0],i,0 });
        }
        while (k > 0 && !pq.empty()) {
            Element curr = pq.top();
            pq.pop();
            ans.push_back({ nums1[curr.i],nums2[curr.j] });
            if (curr.j + 1 < m) {
                pq.push({ nums1[curr.i] + nums2[curr.j + 1],curr.i,curr.j + 1 });
            }
            k--;
        }
    }
};

int main() {
    KSmallestPairsSolver solver;

    solver.inputData();   
    solver.solve();       
    solver.printOutput(); 

    return 0;
}