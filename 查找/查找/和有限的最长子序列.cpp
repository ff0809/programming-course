//#include<iostream>
//#include<algorithm>
//using namespace std;
//
//#define maxsize 1005
//
//int main()
//{
//	int n, m;
//	cin >> n >> m;
//	int num[maxsize] = {};
//	for (int i = 0; i < n; i++)
//	{
//		cin >> num[i];
//	}
//	sort(num, num + n);
//	int query[maxsize] = {};
//	for (int i = 0; i < m; i++)
//	{
//		cin >> query[i];
//		long long sum = 0;
//		int result = n;
//		for (int j = 0; j < n; j++)
//		{
//			sum += num[j];
//			if (sum > query[i])
//			{
//				result = j;
//				break;
//			}
//		}
//		cout << result << " ";
//	}
//	return 0;
//}