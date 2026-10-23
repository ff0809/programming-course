//#define Maxsize 10000
//#include<iostream>
//using namespace std;
//
//typedef struct
//{
//	string name;
//	string no;
//}student;
//
//typedef struct
//{
//	student s[Maxsize];
//	int length;
//}sqlist;
//
//void initlist(sqlist& l)
//{
//	int n;
//	cin >> n;
//	for (int i = 0; i < n; i++)
//	{
//		cin >> l.s[i].no >> l.s[i].name;
//	}
//	l.length = n;
//}
//
//int insertlist(sqlist& l, int i, string no, string name)
//{
//	if (i<1 || i>l.length + 1)return -1;
//	for (int j = l.length; j >= i; j--)
//	{
//		l.s[j] = l.s[j - 1];
//	}
//	l.s[i - 1].name = name;
//	l.s[i - 1].no = no;
//	l.length++;
//	return 0;
//}
//
//int removelist(sqlist& l, int i)
//{
//	if (i<1 || i>l.length)return -1;
//	for (int j = i; j < l.length; j++)
//	{
//		l.s[j - 1] = l.s[j];
//	}
//	l.length--;
//	return 0;
//}
//
//int checkname(sqlist& l, string name)
//{
//	for (int i = 0; i < l.length; i++)
//	{
//		if (l.s[i].name == name)
//		{
//			cout << i + 1 << " " << l.s[i].no << " " << l.s[i].name << endl;
//			return 0;
//		}
//	}
//	return -1;
//}
//
//int checkno(sqlist& l, string no)
//{
//	for (int i = 0; i < l.length; i++)
//	{
//		if (l.s[i].no == no)
//		{
//			cout << i + 1 << " " << l.s[i].no << " " << l.s[i].name << endl;
//			return 0;
//		}
//	}
//	return -1;
//}
//
//int main()
//{
//	sqlist l;
//	initlist(l);
//	string cmd, cmd1;
//	int pos;
//	string name, no;
//	while (cin >> cmd)
//	{
//		if (cmd == "end")
//		{
//			cout << l.length << endl;
//			break;
//		}
//		else if (cmd == "insert")
//		{
//			cin >> pos >> no >> name;
//			cout << insertlist(l, pos, no, name) << endl;
//
//		}
//		else if (cmd == "remove")
//		{
//			cin >> pos;
//			cout << removelist(l, pos) << endl;
//		}
//		else if (cmd == "check")
//		{
//			cin >> cmd1;
//			if (cmd1 == "name")
//			{
//				cin >> name;
//				if (checkname(l, name) == -1)cout << "-1" << endl;
//			}
//			else if (cmd1 == "no")
//			{
//				cin >> no;
//				if (checkno(l, no) == -1)cout << "-1" << endl;
//			}
//		}
//	}
//	return 0;
//}