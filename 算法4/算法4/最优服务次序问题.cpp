#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	int n;
	cout << "请输入顾客人数：" << endl;
	cin >> n;
	vector<int>time(n);
	cout << "请依次输入服务时间：" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> time[i];
	}
	int total = 0;
	int wait = 0;
	sort(time.begin(), time.end());
	for (int i = 1; i < n; i++)
	{
		wait += time[i - 1];
		total += wait;
	}
	double avg = total*1.0 / n;
	cout << "最短平均等待时间为" << avg << endl;
	return 0;
}