#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
using namespace std;

typedef struct
{
	char* base;
	char* top;
	int size;
}stack;

void initstack(stack&s,int size)
{
	s.size = size;
	s.base = (char*)malloc(s.size * sizeof(char));
	s.top = s.base;
}

void push(stack& s, char c)
{
	*s.top++ = c;
}

void pop(stack& s)
{
	--s.top;
}

char gettop(stack& s)
{
	return *(s.top-1);
}

bool isempty(stack& s)
{
	return s.top == s.base;
}

bool judge(stack& s, char* str1, char* str2)
{
	// 重新初始化栈，准备模拟本次出栈过程
	initstack(s, s.size);
	int j = 0; // 出栈序列指针
	// 遍历入栈序列
	for (int i = 0; i < s.size; i++)
	{
		// 当前入栈元素入栈
		push(s, str1[i]);
		// 尽可能多地进行出栈操作
		// 只要栈顶等于当前出栈序列字符，就出栈
		while (!isempty(s) && gettop(s) == str2[j])
		{
			pop(s);
			j++;
		}
	}
	// 如果栈空，说明出栈序列合法
	bool result = isempty(s);
	return result;
}

int main()
{
	stack s;
	char str1[1000];
	cin >> str1;
	s.size = strlen(str1);
	char str2[1000];
	while (cin >> str2)
	{
		bool result=judge(s,str1,str2);
		if (result)
		{
			cout << "yes" << endl;
		}
		else
		{
			cout << "no" << endl;
		}
	}
	return 0;
}