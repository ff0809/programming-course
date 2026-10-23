//#include<iostream>
//#include<cstdlib>
//using namespace std;
//
//typedef struct node
//{
//	int data;
//	struct node* next;
//}node,*linklist;
//
//node* initlist()
//{
//	node* head = (node*)malloc(sizeof(node));
//	if (!head)return NULL;
//	head->next = NULL;
//	return head;
//}
//
//void insertlist(linklist la, linklist lb, linklist& lc)
//{
//	lc = initlist();
//	node* rear = lc;
//	node* p = la->next;
//	node* q = lb->next;
//	while (p && q)
//	{
//		if (p->data <= q->data)
//		{
//			node* newnode = (node*)malloc(sizeof(node));
//			newnode->data = p->data;
//			newnode->next = NULL;
//			rear->next = newnode;
//			rear = newnode;
//			p = p->next;
//		}
//		else
//		{
//			node* newnode = (node*)malloc(sizeof(node));
//			newnode->data = q->data;
//			newnode->next = NULL;
//			rear->next = newnode;
//			rear = newnode;
//			q = q->next;
//		}
//	}
//	while (p)
//	{
//		node* newnode = (node*)malloc(sizeof(node));
//		newnode->data = p->data;
//		newnode->next = NULL;
//		rear->next = newnode;
//		rear = newnode;
//		p = p->next;
//	}
//	while (q)
//	{
//		node* newnode = (node*)malloc(sizeof(node));
//		newnode->data = q->data;
//		newnode->next = NULL;
//		rear->next = newnode;
//		rear = newnode;
//		q = q->next;
//	}
//}
//
//void printlist(linklist l)
//{
//	node* p = l->next;
//	while(p)
//	{
//		cout << p->data << " ";
//		p = p->next;
//	}
//	cout << endl;
//}
//
//int main()
//{
//	linklist la = initlist();
//	linklist lb = initlist();
//	int m, n;
//	node* reara = la;
//	node* rearb = lb;
//	while (true)
//	{
//		cin >> m;
//		if (m == -1)break;
//		node* newnode = (node*)malloc(sizeof(node));
//		newnode->data = m;
//		newnode->next = NULL;
//		reara->next = newnode;
//		reara = newnode;
//	}
//	while (true)
//	{
//		cin >> n;
//		if (n == -1)break;
//		node* newnode = (node*)malloc(sizeof(node));
//		newnode->data = n;
//		newnode->next = NULL;
//		rearb->next = newnode;
//		rearb = newnode;
//	}
//	linklist lc;
//	insertlist(la, lb, lc);
//	printlist(lc);
//	return 0;
//}