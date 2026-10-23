#include<iostream>
using namespace std;

double pow(double x, long long n)
{
	if (n == 0)return 1;
	else if (n < 0)return 1.0 / pow(x, -n);
	else
	{
		double half = pow(x, n / 2);
		if (n % 2 == 0)return half * half;
		else return half * half * x;
	}
}

double mypow(double x, int n)
{
	long long N = n;
	return pow(x, N);
}

int main()
{
	cout << "请输入底数和指数：" << endl;
	double x;
	long long n;
	cin >> x >> n;
	cout << mypow(x, n);
}