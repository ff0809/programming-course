//#include<iostream>
//#include<vector>
//#include<algorithm>
//#include <string>
//using namespace std;
//
//bool isvalid(string &s, int start, int end) {
//	if (s[start] == '0' && end > start)return false;
//	if (stoi(s.substr(start,end-start+1)) > 255)return false;
//	return true;
//}
//
//void backtrack(string s, int count, int start, vector<string>&path, vector<string>&ans) {
//	if (count == 4) {
//		if (start == s.size()) {
//			string ip = path[0] + '.' + path[1] + '.' + path[2] + '.' + path[3];
//			ans.push_back(ip);
//		}
//		return;
//	}
//	for (int i = start; i < s.size()&&i<start+3; i++) {
//		if (isvalid(s, start, i)) {
//			path.push_back(s.substr(start, i - start + 1));
//			backtrack(s, count + 1, i + 1, path, ans);
//			path.pop_back();
//		}
//	}
//}
//
//vector<string> restoreIPaddresses(string s) {
//	vector<string>path;
//	vector<string>ans;
//	backtrack(s, 0, 0, path, ans);
//	return ans;
//}
//
//int main()
//{
//	string s = "25525511135"; 
//	vector<string> res = restoreIPaddresses(s);
//
//	cout << "ºÏ·¨IPµØÖ·£º" << endl;
//	for (auto& ip : res) {
//		cout << ip << endl;
//	}
//	return 0;
//}