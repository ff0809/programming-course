#include<iostream>
#include<vector>
using namespace std;

int coinchange(vector<int>nums, int n)
{
	vector<int>dp(n + 1, INT_MAX-1);
	dp[0] = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		for (int j = nums[i]; j <= n; j++)
		{
			dp[j] = min(dp[j], dp[j - nums[i]] + 1);
		}
	}
	return dp[n] == INT_MAX - 1 ? -1 : dp[n];
}

int main()
{
	int n,amount;
	vector<int>nums;
	cout << "请输入长度：" << endl;
	cin >> n;
	cout << "请输入总金额：" << endl;
	cin >> amount;
	int num;
	cout << "请依次输入：" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> num;
		nums.push_back(num);
	}
	int res = coinchange(nums,amount);
	cout << res << endl;
	return 0;
}