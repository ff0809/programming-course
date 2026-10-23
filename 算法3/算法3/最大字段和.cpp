//#include<iostream>
//#include<vector>
//using namespace std;
//
//int maxarray(vector<int>nums)
//{
//	int sum = INT_MIN, b = INT_MIN;
//	for (int i = 0; i < nums.size(); i++)
//	{
//		if (b > 0)
//		{
//			b += nums[i];
//		}
//		else
//		{
//			b = nums[i];
//		}
//		if (sum < b)
//		{
//			sum = b;
//		}
//	}
//	return sum;
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
//	int res = maxarray(nums);
//	cout << res << endl;
//	return 0;
//}