#include<iostream>
#include<vector>
using namespace std;

int partition(vector<int>&arr, int a, int b)
{
	int i = a, j = b + 1;
	int x = arr[a];
	while (true)
	{
		while (arr[++i] < x && i < b);
		while (arr[--j] > x);
		if (i >= j)break;
		swap(arr[i], arr[j]);
	}
	arr[a] = arr[j];
	arr[j] = x;
	return j;
}

void quicksort(vector<int>&arr, int a, int b)
{
	if (a >= b)return;
	int c = partition(arr, a, b);
	quicksort(arr, a, c - 1);
	quicksort(arr, c + 1, b);
}

int findfirst(vector<int>arr, int x, int l, int r)
{
	if (l > r)return -1;
	int mid = (l + r) / 2;
	if (arr[mid] == x)
	{
		int pos = findfirst(arr, x, l, mid - 1);
		if (pos == -1)return mid;
		return pos;
	}
	else if (arr[mid] < x)
	{
		return findfirst(arr, x, mid + 1, r);
	}
	else
	{
		return findfirst(arr, x, l, mid - 1);
	}
}

int findlast(vector<int>arr, int x, int l, int r)
{
	if (l > r)return -1;
	int mid = (l + r) / 2;
	if (arr[mid] == x)
	{
		int pos = findlast(arr, x, mid+1, r);
		if (pos == -1)return mid;
		return pos;
	}
	else if (arr[mid] < x)
	{
		return findlast(arr, x, mid + 1, r);
	}
	else
	{
		return findlast(arr, x, l, mid - 1);
	}
}

bool hasmajor(vector<int>arr)
{
	int n = arr.size();
	int choice = arr[n / 2];
	int start = findfirst(arr, choice, 0, n - 1);
	int end = findlast(arr, choice, 0, n - 1);
	int length = end - start + 1;
	return(length > n / 2);
}

bool hasmajor2(vector<int>arr)
{
	int n = arr.size();
	quicksort(arr, 0, n - 1);
	int choice = arr[n / 2];
	int start = findfirst(arr, choice, 0, n - 1);
	int end = findlast(arr, choice, 0, n - 1);
	int length = end - start + 1;
	return(length > n / 2);
}

bool hasmajor3(vector<int>&arr)
{
	int n = arr.size();
	if (n == 0)return false;
	int count = 0, count2 = 0;
	int candidate = 0;
	for (int i = 0; i < n; i++)
	{
		if (count == 0)
		{
			candidate = arr[i];
		}
		if (candidate == arr[i])
		{
			count++;
		}
		else count--;
	}
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == candidate)
		{
			count2++;
		}
	}
	return count2 > n / 2;
}

int main() 
{
	cout << "请依次输入数组元素（有序），-1结束：" << endl;
	vector<int>arr, arr2,arr3;
	while (true)
	{
		int num;
		cin >> num;
		if (num == -1)break;
		arr.push_back(num);
	}
	cout << (hasmajor(arr)?"true":"false" )<< endl;

	cout << "请依次输入数组元素（可无序），-1结束：" << endl;
	while (true)
	{
		int num;
		cin >> num;
		if (num == -1)break;
		arr2.push_back(num);
	}
	cout << (hasmajor2(arr2) ? "true" : "false") << endl;

	cout << "请依次输入数组元素（可无序），-1结束（时间复杂度更低）：" << endl;
	while (true)
	{
		int num;
		cin >> num;
		if (num == -1)break;
		arr3.push_back(num);
	}
	cout << (hasmajor3(arr3) ? "true" : "false") << endl;
	return 0;
}