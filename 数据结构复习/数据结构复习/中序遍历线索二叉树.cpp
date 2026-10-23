#include<iostream>
using namespace std;

typedef struct binode
{
	int data;
	struct binode* lchild, * rchild;
	int ltag, rtag;
}binode,*bitree;

binode* pre = NULL;

void inthread(bitree p)
{
	if (p)
	{
		inthread(p->lchild);
		if (!p->lchild)
		{
			p->ltag = 1;
			p->lchild = pre;
		}
		if (pre && !pre->rchild)
		{
			pre->rtag = 1;
			pre->rchild = p;
		}
		pre = p;
		inthread(p->rchild);
	}
}

void createtree(bitree t)
{
	pre = NULL;
	if (t)
	{
		inthread(t);
		pre->rtag = 1;
		pre->rchild = NULL;
	}
}

void inorder(bitree t)
{
	binode* p = t;
	while (p->ltag==0)
	{
		p = p->lchild;
	}
	while (p->rchild)
	{
		if (p->rchild == 0)
		{
			p = p->rchild;
			while (p->ltag == 0)
			{
				p = p->lchild;
			}
		}
		else
		{
			p = p->rchild;
		}
		cout << p->data << endl;
	}
}

int main()
{

	return 0;
}