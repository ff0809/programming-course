//#include<iostream>
//#include<vector>
//using namespace std;
//
//int maxsquare(int n)
//{
//	vector<int>dp(n + 1, INT_MAX);
//	dp[0] = 0;
//	for (int i = 1; i <= n; i++)
//	{
//		for (int j = 1; j * j <= i; j++)
//		{
//			dp[i] = min(dp[i], dp[i - j * j] + 1);
//		}
//	}
//	return dp[n];
//}
//
//int main()
//{ 
//	int n;
//	vector<int>nums;
//	cout << "请输入一个整数：" << endl;
//	cin >> n;
//	int num;
//	cout << "可以用最少数目表示出该整数，最小值为：";
//	int res = maxsquare(n);
//	cout << res << endl;
//	return 0;
//}