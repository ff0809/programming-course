//#include<iostream>
//#include<vector>
//using namespace std;
//
//bool isvalid(string s, int start, int end) {
//	while (start < end) {
//		if (s[start] != s[end])return false;
//		start++; end--;
//	}
//	return true;
//}
//
//void backtrack(string s, int start, vector<string>&path, vector<vector<string>>&ans) {
//	if (start == s.size()) {
//		ans.push_back(path);
//		return;
//	}
//	for (int i = start; i < s.size(); i++) {
//		if (isvalid(s, start, i)) {
//			path.push_back(s.substr(start, i - start + 1));
//			backtrack(s, i + 1, path, ans);
//			path.pop_back();
//		}
//	}
//}
//
//vector<vector<string>> partition(string s) {
//	vector<string>path;
//	vector<vector<string>>ans;
//	backtrack(s, 0, path, ans);
//	return ans;
//}
//
//int main() 
//{
//	string s = "aab"; 
//	vector<vector<string>> res = partition(s);
//	cout << "字符串 \"" << s << "\" 的所有回文分割方案：" << endl;
//	for (auto& vec : res) {
//		for (auto& str : vec) {
//			cout << str << " ";
//		}
//		cout << endl;
//	}
//	return 0;
//}
