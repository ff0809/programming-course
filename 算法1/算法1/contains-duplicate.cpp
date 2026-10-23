#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool containsDuplicate(vector<int>& nums)
{
	sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size()-1; i++)
	{
		if (nums[i] == nums[i + 1])
		{
			return true;
		}
	}
	return false;
}

int main()
{
	int length;
	cout << "请输入数组元素个数：" << endl;
	cin >> length;
	vector<int>nums;
	int num;
	cout << "请依次输入数组元素：" << endl;
	for (int i = 0; i < length; i++)
	{
		cin >> num;
		nums.push_back(num);
	}
    cout << (containsDuplicate(nums) ? "true" : "false") << endl;
	return 0;
}