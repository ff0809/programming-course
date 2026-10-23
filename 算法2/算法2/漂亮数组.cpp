#include<iostream>
#include<vector>
using namespace std;

vector<int> beautifulArray(int n) {
    if (n == 1)return{ 1 };
    vector<int>num;
    vector<int>left = beautifulArray((n + 1) / 2);
    vector<int>right = beautifulArray(n / 2);
    for (int i = 0; i < left.size(); i++)
    {
        num.push_back(2 * left[i] - 1);
    }
    for (int i = 0; i < right.size(); i++)
    {
        num.push_back(2 * right[i]);
    }
    return num;
}

int main()
{
    cout << "请输入元素数量：" << endl;
    int n;
    cin >> n;
    vector<int>v = beautifulArray(n);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << ",";
    }
    cout << endl;
	return 0;
}