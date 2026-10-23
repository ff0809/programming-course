#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

void backtrack(string& s, int i, int lc, int rc, int lr, int rr, string&path, unordered_set<string>&ans) {
	if(i == s.size()){
		if (lr == 0 && rr == 0 && lc == rc) {
			ans.insert(path);
		}
		return;
	}
	char c = s[i];
	if (c != '('&&c!=')') {
		path += c;
		backtrack(s, i + 1, lc, rc, lr, rr, path, ans);
		path.pop_back();
	}
	else if (c == '(') {
		if (lr > 0)backtrack(s, i + 1, lc, rc, lr - 1, rr, path, ans);
		path += '(';
		backtrack(s, i + 1, lc + 1, rc, lr, rr, path, ans);
		path.pop_back();
	}
	else {
		if (rr > 0)backtrack(s, i + 1, lc, rc, lr, rr - 1, path, ans);
		if (lc > rc) {
			path += ')';
			backtrack(s, i + 1, lc, rc + 1, lr, rr, path, ans);
			path.pop_back();
		}
	}
}

vector<string> removeInvalidParentheses(string s) {
	int lr = 0; int rr = 0;
	for (char c : s) {
		if (c == '(')lr++;
		else if (c == ')') {
			if (lr > 0)lr--;
			else rr++;
		}
	}
	string path;
	unordered_set<string>ans;
	backtrack(s, 0, 0, 0, lr, rr, path, ans);
	return vector<string>(ans.begin(), ans.end());
}

int main()
{
	string s1 = "()())()";
	cout << "测试用例：" << s1 << endl;
	vector<string> res1 = removeInvalidParentheses(s1);
	cout << "有效结果：" << endl;
	for (string str : res1) {
		cout << str << endl;
	}
	return 0;
}