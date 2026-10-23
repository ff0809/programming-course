#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

bool valid(string& str, string& num)
{
	if (str.size() == 11 && str.substr(0, 3) == num && stoi(str.substr(0, 2)) >= 13 && stoi(str.substr(0, 2)) <= 19)
	{
		for (int i = 3; i < 11; i++)
		{
			if (!isdigit(str[i]))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

int main()
{
	ifstream in;
	in.open("messy.content", ios::in);
	if (!in.is_open())
	{
		cerr << "文件打开失败！" << endl;
		return -1;
	}
	cout << "请输入需要查找的电话号码的前三位数字：" << endl;
	string num, line;
	if (cin >> num)
	{
		long long number_arr[10000];
		int pos = 0;
		while (getline(in, line))
		{
			if (line.find(num) != string::npos)
			{
				stringstream ss(line);
				string token;
				while (ss >> token)
				{
					if (valid(token, num))
					{
						number_arr[pos++] = stoll(token);
					}
				}
			}
		}
		long long max = 0;
		for (int i = 0; i < pos; i++)
		{
			if (number_arr[i] > max)
			{
				max = number_arr[i];
			}
		}
		if (pos > 0)
		{
			cout << max << endl;
		}
	}
	in.close();
	return 0;
}