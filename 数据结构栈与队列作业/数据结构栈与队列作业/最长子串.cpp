#define maxsize 100000
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<string>
using namespace std;

typedef struct
{
	int data[maxsize];
	int top;
}stack;

void init(stack& s)
{
	s.top = 0;
	s.data[0] = -1;
}

void push(stack& s,int val)
{
	s.data[++s.top] = val;
}

void pop(stack& s)
{
	s.top--;
}

int gettop(stack& s)
{
	return s.data[s.top];
}

int main()
{
	char str[maxsize];
	cin.getline(str, maxsize);
	stack s;
	init(s);
	int maxlen = 0;
	int startpos = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == '(')
		{
			push(s, i);
		}
		else
		{
			if (s.top > 0)
			{
				pop(s);
				int len = i - gettop(s);
				if (len > maxlen)
				{
					maxlen = len;
					startpos = gettop(s) + 1;
				}
			}
			else
			{
				s.data[0] = i;
			}
		}
	}
	cout << maxlen << " " << startpos << endl;
}