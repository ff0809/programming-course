//#define Maxsize 100000
//#include<iostream>
//using namespace std;
//
//typedef struct
//{
//	int nums[Maxsize];
//	int length;
//}sqlist;
//
//void reverselist(sqlist& l, int begin, int end)
//{
//	while (begin < end)
//	{
//		int temp = l.nums[begin];
//		l.nums[begin] = l.nums[end];
//		l.nums[end] = temp;
//		begin++;
//		end--;
//	}
//}
//
//void removelist(sqlist& l)
//{
//	l.length = 0;
//	int n, k;
//	cin >> n >> k;
//	for (int i = 0; i < n; i++)
//	{
//		cin >> l.nums[i];
//		l.length++;
//	}
//	reverselist(l, 0, n - 1);
//	reverselist(l, 0, k%n-1);
//	reverselist(l, k%n, n - 1);
//}
//
//void printlist(sqlist& l)
//{
//	for (int i = 0; i < l.length; i++)
//	{
//		cout << l.nums[i] << " ";
//	}
//	cout << endl;
//}
//
//int main()
//{
//	sqlist l;
//	removelist(l);
//	printlist(l);
//	return 0;
//}