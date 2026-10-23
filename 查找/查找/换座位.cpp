///**
// * @file    template.cpp
// * @name    p138模板程序
// * @date    2022-11-20
//*/
//
//#include <iostream>
//#include <algorithm>
//#include <cstdio>
//#include <cstdlib>
//#include <ctime>
//#include <cmath>
//#include <string>
//#include <vector>
//#include <queue>
//#include <stack>
//#include <map>
//#include <set>
//using namespace std;
//
//
///********************************/
///*     以下是你需要提交的代码     */
///********************************/
//class solution {
//public:
//    int solve(std::vector<vector<std::string>>& old_chart, std::vector<std::vector<std::string>>& new_chart) {
//        int n = old_chart.size();
//        int m = old_chart[0].size();
//        int total = n * m;
//
//        map<string, int> name2pos;
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < m; j++) {
//                int idx = i * m + j;
//                name2pos[new_chart[i][j]] = idx;
//            }
//        }
//
//        vector<int> perm(total);
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < m; j++) {
//                int idx = i * m + j;
//                string name = old_chart[i][j];
//                perm[idx] = name2pos[name];
//            }
//        }
//
//        vector<bool> visited(total, false);
//        int ring_count = 0;
//        for (int i = 0; i < total; i++) {
//            if (!visited[i]) {
//                ring_count++;
//                int j = i;
//                while (!visited[j]) {
//                    visited[j] = true;
//                    j = perm[j];
//                }
//            }
//        }
//        return total - ring_count;
//    }
//};
///********************************/
///*     以上是你需要提交的代码     */
///********************************/
//
//int main() {
//    int n, m;
//    std::cin >> n >> m;
//    std::vector<std::vector<std::string>> old_chart(n, std::vector<std::string>(m));
//    std::vector<std::vector<std::string>> new_chart(n, std::vector<std::string>(m));
//
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            std::cin >> old_chart[i][j];
//        }
//    }
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            std::cin >> new_chart[i][j];
//        }
//    }
//
//    solution s;
//    std::cout << s.solve(old_chart, new_chart) << std::endl;
//    return true;
//}