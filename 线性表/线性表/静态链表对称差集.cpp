#define MAXSIZE 100
#include<iostream>
using namespace std;

typedef struct
{
	int data;
	int cur;
}component,slinklist[MAXSIZE];

void initlist(slinklist& s)
{
	for (int i = 0; i < MAXSIZE - 1; i++)
	{
		s[i].cur = i + 1;
	}
	s[MAXSIZE - 1].cur = 0;
}

int alloc(slinklist& s)
{
	int i=s[0].cur;
	if (i!=0)s[0].cur = s[i].cur;
	return i;
}

void freec(slinklist& s,int i)
{
	s[i].cur = s[0].cur;
	s[0].cur = i;
}

void diff(slinklist& s)
{
	initlist(s);
	int a = alloc(s);
	int r = a;//r指向当前链表的最后一个结点
	int m, n;
	cin >> m >> n;
	for (int j = 1; j <= m; j++)
	{
		int i = alloc(s);
		cin >> s[i].data;
		s[r].cur = i;
		r = i;
		s[r].cur = 0;
	}
	for (int j = 1; j <= n; j++)
	{
		int e;
		cin >> e;
		int p = s[a].cur;
		int pre = a;
		while (p != 0 && s[p].data != e)
		{
			pre = p;
			p = s[p].cur;
		}
		if (p != 0)
		{
			s[pre].cur = s[p].cur;
			freec(s, p);
			if (r == p)
			{
				r = pre;
			}
		}
		else
		{
			int i = alloc(s);
			s[i].data = e;
			s[i].cur = s[r].cur;
			s[r].cur = i;
			r = i;
		}
	}
}

int main()
{
	slinklist s;
	diff(s);
	return 0;
}