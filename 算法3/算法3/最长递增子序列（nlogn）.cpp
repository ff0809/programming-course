//#include<iostream>
//#include<vector>
//using namespace std;
//
//int maxseries(vector<int>nums)
//{
//	int n = nums.size();
//	vector<int>tail;
//	for (int i = 0; i < n; i++)
//	{
//		int num = nums[i];
//		int left = 0;
//		int right = tail.size();
//		int pos = tail.size();
//		while (left < right)
//		{
//			int mid = (left + right) / 2;
//			if (tail[mid] >= num)
//			{
//				right = mid;
//				pos = mid;
//			}
//			else
//			{
//				left = mid + 1;
//			}
//		}
//		if (pos == tail.size())
//		{
//			tail.push_back(num);
//		}
//		else
//		{
//			tail[pos] = num;
//		}
//	}
//	return tail.size();
//}
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