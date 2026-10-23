#define stacksize 100
#define maxsize 1000
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
using namespace std;

typedef struct
{
	char data[maxsize];
	int top;
}stack;

void init(stack& s)
{
	s.top = 0;
	s.data[0] = '#';
}

void push(stack& s, char c)
{
	s.data[++s.top] = c;
}

char pop(stack& s)
{
	return s.data[s.top--];
}

char gettop(stack& s)
{
	return s.data[s.top];
}

char* delspace(char* stro, char* strn)
{
	int j = 0;
	for (int i = 0; i < strlen(stro); i++)
	{
		if (stro[i] != ' ')
		{
			strn[j++] = stro[i];
		}
	}
	strn[j] = '\0';
	return strn;
}

int prior(char c)
{
	switch (c)
	{
	case '#':return 0;
	case '(':return 1;
	case '|':return 2;
	case '&':return 3;
	case '!':return 4;
	default:return -1;
	}
}

char calculate(char op, char a, char b)
{
	if (op == '|')
	{
		return(a == 'V' || b == 'V') ? 'V' : 'F';
	}
	else if (op == '&')
	{
		return(a == 'V' && b == 'V') ? 'V' : 'F';
	}
	else if (op =='!')
	{
		return(a == 'V') ? 'F' : 'V';
	}
	return 'F';
}

char evaculate(char* str)
{
	stack op;
	stack num;
	init(op);
	init(num);
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'V' || str[i] == 'F')
		{
			push(num, str[i]);
			while (gettop(op) == '!')
			{
				char popop = pop(op);
				char a = pop(num);
				push(num,calculate(popop, a, ' '));
			}
			i++;
		}
		else if (str[i] == '(')
		{
			push(op, str[i]);
			i++;
		}
		else if (str[i] ==')')
		{
			while (gettop(op) != '(')
			{
				char popop = pop(op);
				if (popop == '!')
				{
					char a = pop(num);
					push(num,calculate(popop, a, ' '));
				}
				else if (popop == '&'||popop== '|')
				{
					char b = pop(num);
					char a = pop(num);
					push(num, calculate(popop, a, b));
				}
			}
			pop(op);
			while (gettop(op) == '!')
			{
				char popop = pop(op);
				char a = pop(num);
				push(num, calculate(popop, a, ' '));
			}
			i++;
		}
		else
		{
			while ((prior(str[i]) < prior(gettop(op)) || (prior(str[i]) == prior(gettop(op)) && gettop(op) != '!')) && gettop(op) != '(')
			{
				char popop = pop(op);
				if (popop == '!')
				{
					char a = pop(num);
					push(num, calculate(popop, a, ' '));
				}
				else if (popop == '&' || popop == '|')
				{
					char b = pop(num);
					char a = pop(num);
					push(num, calculate(popop, a, b));
				}
			}
			push(op, str[i]);
			i++;
		}
	}
	while (gettop(op) != '#')
	{
		char popop = pop(op);
		if (popop == '!')
		{
			char a = pop(num);
			push(num, calculate(popop, a, ' '));
		}
		else if (popop == '&' ||popop== '|')
		{
			char b = pop(num);
			char a = pop(num);
			push(num, calculate(popop, a, b));
		}
	}
	return gettop(num);
}

int main()
{
	char stro[maxsize];
	int i=1;
	while (cin.getline(stro, maxsize))
	{
		char strn[stacksize];
		delspace(stro, strn);
		char* str = strn;
		char result=evaculate(str);
		cout << "Expression " << i << ": " << result << endl;
		i++;
	}
	return 0;
}