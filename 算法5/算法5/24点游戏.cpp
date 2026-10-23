//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//bool backtrack(vector<double>nums) {
//	if (nums.size() == 1) {
//		if (fabs(nums[0] - 24) < 1e-6) return true;
//	}
//	int n = nums.size();
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++) {
//			if (i == j)continue;
//			double a = nums[i];
//			double b = nums[j];
//			vector<double>restnum;
//			for (int k = 0; k < n; k++) {
//				if (k != i && k != j)restnum.push_back(nums[k]);
//			}
//			restnum.push_back(a + b);
//			if (backtrack(restnum))return true;
//			restnum.pop_back();
//
//			restnum.push_back(a - b);
//			if (backtrack(restnum))return true;
//			restnum.pop_back();
//
//			restnum.push_back(b - a);
//			if (backtrack(restnum))return true;
//			restnum.pop_back();
//
//			restnum.push_back(a * b);
//			if (backtrack(restnum))return true;
//			restnum.pop_back();
//
//			if (fabs(b) > 1e-6) {
//				restnum.push_back(a / b);
//				if (backtrack(restnum))return true;
//				restnum.pop_back();
//			}
//			if (fabs(a) > 1e-6) {
//				restnum.push_back(b / a);
//				if (backtrack(restnum))return true;
//				restnum.pop_back();
//			}
//		}
//	}
//	return false;
//}
//
//bool judge(vector<int>& cards) {
//	vector<double>nums;
//	for (int x : cards) {
//		nums.push_back(double(x));
//	}
//	return backtrack(nums);
//}
//
//int main()
//{
//	vector<int> cards1 = { 4, 1, 8, 7 };
//	vector<int> cards2 = { 1, 2, 1, 2 };
//
//	cout << boolalpha;
//	cout << "[4,1,8,7] 能否算出24：" << judge(cards1) << endl;
//	cout << "[1,2,1,2] 能否算出24：" << judge(cards2) << endl;
//	return 0;
//}