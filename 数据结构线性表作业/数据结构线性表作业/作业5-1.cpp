//#include<iostream>
//#include<string>
//using namespace std;
//
//typedef struct node
//{
//	string suit;
//	string rank;
//	struct node* next;
//}node,*linklist;
//
//node* head = NULL;
//node* tail = NULL;
//
//node* createnode(string suit, string rank)
//{
//	node* p = new node;
//	p->suit = suit; 
//	p->rank = rank;
//	p->next = NULL;
//	return p;
//}
//
//void appendlist(string suit, string rank)
//{
//	node* p = createnode(suit, rank);
//	if (head == NULL)
//	{
//		head = p;
//		tail = p;
//	}
//	else
//	{
//		tail->next = p;
//		tail = p;
//	}
//}
//
//void appendnewlist(node* &nhead, node* &ntail, string suit, string rank)
//{
//	node* p = createnode(suit, rank);
//	if (nhead == NULL)
//	{
//		nhead = p;
//		ntail = p;
//	}
//	else
//	{
//		ntail->next = p;
//		ntail = p;
//	}
//}
//
//int getvalue(string s)
//{
//	if (s == "A")return 1;
//	else if (s == "J")return 11;
//	else if (s == "Q")return 12;
//	else if (s == "K")return 13;
//	else return stoi(s);
//}
//
//int getlength(node*head)
//{
//	int length = 0;
//	node* p = head;
//	while (p)
//	{
//		p = p->next;
//		length++;
//	}
//	return length;
//}
//
//void extractlist(string suit)
//{
//	linklist l=NULL;
//	node* p = head;
//	node* prev = NULL;
//	node* ntail = NULL;
//	while (p)
//	{
//		if (p->suit == suit)
//		{
//			appendnewlist(l, ntail, p->suit, p->rank);
//			if (prev == NULL)
//			{
//				head = p->next;
//				if (head == NULL)tail = NULL;
//			}
//			else
//			{
//				prev->next = p->next;
//				if (p == tail)tail = prev;
//			}
//			node* temp = p;
//			p = p->next;
//			delete temp;
//		}
//		else
//		{
//			prev = p;
//			p = p->next;
//		}
//	}
//	for (int i = 0; i < getlength(l); i++)
//	{
//		node* q = l;
//		for (int j = 0; j < getlength(l) - i - 1; j++)
//		{
//			if (getvalue(q->rank) > getvalue(q->next->rank))
//			{
//				swap(q->rank, q->next->rank);
//			}
//			q = q->next;
//		}
//	}
//	if (l)
//	{
//		ntail->next =head;
//		head = l;
//	}
//	tail = head;
//	while (tail && tail->next)
//	{
//		tail = tail->next;
//	}
//}
//
//void revertlist()
//{
//	node* prev = NULL;
//	node* cur = head;
//	node* next = NULL;
//	while (cur)
//	{
//		next = cur->next;
//		cur->next = prev;
//		prev = cur;
//		cur = next;
//	}
//	swap(head, tail);
//}
//
//void poplist()
//{
//	if (head == NULL)cout << "NULL" << endl;
//	else
//	{
//		node* p = head;
//		cout << p->suit << " " << p->rank << endl;
//		node* temp = head;
//		head = head->next;
//		delete temp;
//	}
//}
//
//int main()
//{
//	int line;
//	cin >> line;
//	for (int i = 0; i < line; i++)
//	{
//		string order;
//		cin >> order;
//		if (order == "Append")
//		{
//			string suit, rank;
//			cin >> suit >> rank;
//			appendlist(suit, rank);
//		}
//		else if (order == "Extract")
//		{
//			string suit;
//			cin >> suit;
//			extractlist(suit);
//		}
//		else if (order == "Revert")
//		{
//			revertlist();
//		}
//		else if (order == "Pop")
//		{
//			poplist();
//		}
//	}
//	node* p = head;
//	if (p == NULL)
//	{
//		cout << "NULL" << endl;
//	}
//	while (p)
//	{
//		cout << p->suit << " " << p->rank << endl;
//		p = p->next;
//	}
//	return 0;
//}
//
