//#include<iostream>
//using namespace std;
//
//typedef struct node
//{
//	int digit;
//	struct node* next;
//}node,*linklist;
//
//node* createnode(int digit)
//{
//	node* newnode = (node*)malloc(sizeof(node));
//	newnode->digit = digit;
//	newnode->next = NULL;
//	return newnode;
//}
//
//node* add(linklist a, linklist b)
//{
//	node* sumhead = NULL;
//	node* sumtail = NULL;
//	node* p = a;
//	node* q = b;
//	int carry = 0;
//	while (p || q || carry)
//	{
//		int total = (p?p->digit:0) + (q?q->digit:0) + carry;
//		int cur = total % 10;
//		carry = total / 10;
//		node* newnode = createnode(cur);
//		if (!sumhead)
//		{
//			sumhead = newnode;
//			sumtail = newnode;
//		}
//		else
//		{
//			sumtail->next = newnode;
//			sumtail = newnode;
//		}
//		if(p)p = p->next;
//		if(q)q = q->next;
//	}
//	return sumhead;
//}
//
//node* multi(linklist num, int n)
//{
//	node* multihead = NULL;
//	node* multitail = NULL;
//	node* p = num;
//	int carry = 0;
//	while (p || carry)
//	{
//		int sum = (p?p->digit:0) * n + carry;
//		int cur = sum % 10;
//		carry = sum / 10;
//		node* newnode = createnode(cur);
//		if (!multihead)
//		{
//			multihead = newnode;
//			multitail = newnode;
//		}
//		else
//		{
//			multitail->next = newnode;
//			multitail = newnode;
//		}
//		if (p)p = p->next;
//	}
//	return multihead;
//}
//
//node* calculate(int a,int n)
//{
//	node* result2 = createnode(0);
//	for (int i = 1; i <= n; i++)
//	{
//		node* p = createnode(1);
//		for (int j = 0; j < i; j++)
//		{
//			p = multi(p, a);
//		}
//		node* result1 = multi(p, i);
//		result2 = add(result2, result1);
//	}
//	return result2;
//}
//
//void printlist(node*head)
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
//	cur = prev;
//	while (cur && cur->digit == 0 && cur->next)
//	{
//		cur = cur->next;
//	}
//	if (cur == NULL)
//	{
//		cout << 0;
//	}
//	
//	while (cur)
//	{
//		node* temp = cur;
//		cout << cur->digit;
//		cur = cur->next;
//		free(temp);
//	}
//	cout << endl;
//}
//
//int main()
//{
//	int a, n;
//	while (cin >> a >> n)
//	{
//		node* result = calculate(a, n);
//		printlist(result);
//	}
//}