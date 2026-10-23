//#include<iostream>
//#include<fstream>
//using namespace std;
//
//int main()
//{
//	ifstream in;
//	in.open("foo.bar", ios::in);
//	if (!in.is_open())
//	{
//		cerr << "打开文件失败！" << endl;
//		return -1;
//	}
//	char ch;
//	int line=0;
//	int num = 0;
//	int arr[10000];
//	int pos = 2;
//	while (in.get(ch))
//	{
//		if ((unsigned char)ch <= 0x7F)
//		{
//			num += 1;
//		}
//		else
//		{
//			num += 2;
//		}
//		if (ch == '\n')
//		{
//			line++;
//			arr[pos++] = num;
//		}
//	}
//	if (num > arr[pos - 1])
//	{
//		arr[pos++] = num+1;
//		line++;
//	}
//	arr[0] = line;
//	arr[1] = 0;
//	for (int i = 0; i < pos; i++)
//	{
//		cout << arr[i] << " ";
//	}
//	cout << endl;
//	return 0;
//}