//#include<iostream>
//#include<vector>
//using namespace std;
//
//int maxseries(vector<int>nums)
//{
//	int n = nums.size();
//	vector<int>dp(n, 1);
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < i; j++)
//		{
//			if (nums[j] < nums[i])
//			{
//				dp[i] = max(dp[i], dp[j] + 1);
//			}
//		}
//	}
//	int maxm = 0;
//	for (int i = 0; i < n; i++)
//	{
//		if (dp[i] > maxm)
//		{
//			maxm = dp[i];
//		}
//	}
//	return maxm;
//}
//
//int main()
//{
//	int n;
//	vector<int>nums;
//	cout << "请输入长度：" << endl;
//	cin >> n;
//	int num;
//	cout << "请依次输入：" << endl;
//	for (int i = 0; i < n; i++)
//	{
//		cin >> num;
//		nums.push_back(num);
//	}
//	int res = maxseries(nums);
//	cout << res << endl;
//	return 0;
//}