#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool compare(vector<int>& a, vector<int>& b)
{
	return a[1] < b[1];
}


int eraseOverlapIntervals(vector<vector<int>>& intervals)
{
	if (intervals.empty())return 0;
	sort(intervals.begin(), intervals.end(), compare);
	int lastend = intervals[0][1];
	int count = 1;
	for (int i = 1; i < intervals.size(); i++)
	{
		if (intervals[i][0] >= lastend)
		{
			count++;
			lastend = intervals[i][1];
		}
	}
	return intervals.size() - count;
}

int main()
{
	int n;
	cout << "请输入区间个数：";
	cin >> n;

	vector<vector<int>> intervals(n, vector<int>(2));
	cout << "请逐行输入每个区间的start和end值：" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> intervals[i][0] >> intervals[i][1];
	}

	int ans = eraseOverlapIntervals(intervals);
	cout << "需要移除的最小区间数量：" << ans << endl;
	return 0;
}