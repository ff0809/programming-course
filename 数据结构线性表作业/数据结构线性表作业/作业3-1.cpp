//#include<iostream>
//using namespace std;
//
//typedef struct node
//{
//	int coef;
//	int exp;
//	struct node* next;
//}node,*linklist;
//
//node* createlist()
//{
//	node*head = (node*)malloc(sizeof(node));
//	head->next = NULL;
//	node* rear = head;
//	int n;
//	cin >> n;
//	for (int i = 0; i < n; i++)
//	{
//		node*p= (node*)malloc(sizeof(node));
//		cin >> p->coef >> p->exp;
//		p->next = NULL;
//		rear->next = p;
//		rear = p;
//	}
//	rear->next = NULL;
//	return head;
//}
//
//
//node* add(linklist& a, linklist& b)
//{
//	linklist result = (node*)malloc(sizeof(node));
//	result->next = NULL;
//	node* rear = result;
//	node* p = a->next;
//	node* q = b->next;
//	while (p && q)
//	{
//		if (p->exp < q->exp)
//		{
//			node* newnode = (node*)malloc(sizeof(node));
//			newnode->coef = p->coef;
//			newnode->exp = p->exp;
//			newnode->next = NULL;
//			rear->next = newnode;
//			rear = newnode;
//			p = p->next;
//		}
//		else if (p->exp > q->exp)
//		{
//			node* newnode = (node*)malloc(sizeof(node));
//			newnode->coef = q->coef;
//			newnode->exp = q->exp;
//			newnode->next = NULL;
//			rear->next = newnode;
//			rear = newnode;
//			q = q->next;
//		}
//		else
//		{
//			int sumcoef = p->coef + q->coef;
//			if (!sumcoef)
//			{
//				p = p->next;
//				q = q->next;
//			}
//			else
//			{
//				node* newnode = (node*)malloc(sizeof(node));
//				newnode->coef = sumcoef;
//				newnode->exp = q->exp;
//				newnode->next = NULL;
//				rear->next = newnode;
//				rear = newnode;
//				p = p->next;
//				q = q->next;
//			}
//		}
//	}
//	while (p)
//	{
//		node* newnode = (node*)malloc(sizeof(node));
//		newnode->coef = p->coef;
//		newnode->exp = p->exp;
//		newnode->next = NULL;
//		rear->next = newnode;
//		rear = newnode;
//		p = p->next;
//	}
//	while (q)
//	{
//		node* newnode = (node*)malloc(sizeof(node));
//		newnode->coef = q->coef;
//		newnode->exp = q->exp;
//		newnode->next = NULL;
//		rear->next = newnode;
//		rear = newnode;
//		q = q->next;
//	}
//	return result;
//}
//
//node* multi(linklist& a, linklist& b)
//{
//	node* result = (node*)malloc(sizeof(node));
//	result->next = NULL;
//	node* p = a->next;
//	while (p)
//	{
//		node* q = b->next;
//		node* last = result;
//		while (q)
//		{
//			int sumcoef = p->coef * q->coef;
//			int sumexp = p->exp + q->exp;
//			node* r = last;
//			while (r->next && r->next->exp < sumexp)
//			{
//				r = r->next;
//			}
//			last = r;
//			if (r->next&&r->next->exp == sumexp)
//			{
//				r->next->coef += sumcoef;
//				if (r->next->coef == 0)
//				{
//					node* temp = r->next;
//					r->next = temp->next;
//					free(temp);
//				}
//			}
//			else
//			{
//				node* newnode = (node*)malloc(sizeof(node));
//				newnode->coef = sumcoef;
//				newnode->exp = sumexp;
//				newnode->next = r->next;
//				r->next = newnode;
//			}
//			q = q->next;
//		}
//		p = p->next;
//	}
//	return result;
//}
//
//void printlist(linklist& l)
//{
//	node* p = l->next;
//	bool flag = false;
//	while (p)
//	{
//		if (flag)
//		{
//			cout << " ";
//		}
//		cout << p->coef << " " << p->exp;
//		flag = true;
//		p = p->next;
//	}
//	if (flag)
//	{
//		cout << endl;
//	}
//}
//
//int main() 
//{
//	node* a, *b;
//	a = createlist();
//	b = createlist();
//	int op;
//	cin >> op;
//	if (op == 0 || op == 2)
//	{
//		node*result=add(a, b);
//		printlist(result);
//	}
//	else if (op == 1 || op == 2)
//	{
//		node*result=multi(a, b);
//		printlist(result);
//	}
//	return 0;
//}