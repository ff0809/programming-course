#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

bool compare(string a, string b)
{
	return a + b > b + a;
}

int main()
{
	int n;
	cout << "请输入整数个数：" << endl;
	cin >> n;
	vector<string>nums(n);
	cout << "请依次输入整数：" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> nums[i];
	}
	sort(nums.begin(), nums.end(), compare);
	string ans = "";
	if (nums[0] == "0")
	{
		cout << "最大整数为0" << endl;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			ans += nums[i];
		}
		cout << "最大整数为" << ans << endl;
	}

	return 0;
}