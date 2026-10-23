#include<iostream>
using namespace std;

typedef struct node
{
	char c;
	struct node* next;
	struct node* prior;
}node,*dlinklist;

node* createlist()
{
	node* head, * s;
	char c = 'A';
	head = (node*)malloc(sizeof(node));
	s = head;
	s->c = c;
	s->next = s;
	s->prior = s;
	for (int i = 1; i < 26; i++)
	{
		c = c + 1;
		node* newnode = (node*)malloc(sizeof(node));
		s->next = newnode;
		newnode->prior = s;
		newnode->next = head;
		head->prior = newnode;
		s = s->next;
		s->c = c;
	}
	return head;
}

int main()
{
	dlinklist l=createlist();
	node* p = l;
	int num;
	cin >> num;
	if (num > 0)
	{
		for (int i = 0; i < num; i++)
		{
			p = p->next;
		}
		for (int i = 0; i < 26; i++)
		{
			cout << p->c << " ";
			p = p->next;
		}
		cout << endl;
	}
	else
	{
		for (int i = 0; i < -num; i++)
		{
			p = p->prior;
		}
		for (int i = 0; i < 26; i++)
		{
			cout << p->c << " ";
			p = p->next;
		}
		cout << endl;
	}
}