//#include<iostream>
//using namespace std;
//
//// 大数节点结构体（逆序存储：如123存储为3→2→1）
//typedef struct node
//{
//	int digit;         // 存储大数的一位（0-9）
//	struct node* next; // 指向下一位（高位方向）
//} node;
//
//node* createnode(int digit)
//{
//	node* newnode = (node*)malloc(sizeof(node));
//	newnode->digit = digit;
//	newnode->next = NULL;
//	return newnode;
//}
//
//node* add(node* a, node* b)
//{
//	node* sumhead = NULL;
//	node* sumtail = NULL;
//	int carry = 0;
//	while (a || b || carry)
//	{
//		int digita = a ? a->digit : 0;
//		int digitb = b ? b->digit : 0;
//		int total = digita + digitb + carry;
//		int cur = total % 10;
//		carry = total/10;
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
//		if (a)a = a->next;
//		if (b)b = b->next;
//	}
//	return sumhead;
//}
//
//node* multibydigit(node* num, int n)
//{
//	if (num == NULL || n == 0)return createnode(0);
//	node* prohead = NULL;
//	node* protail = NULL;
//	int carry = 0;
//	node* cur = num;
//	while (cur || carry)
//	{
//		int digit = cur ? cur->digit : 0;
//		int total = digit * n + carry;
//		int curdigit = total % 10;
//		carry = total / 10;
//		node* newnode = createnode(curdigit);
//		if (prohead == NULL)
//		{
//			prohead = newnode;
//			protail = newnode;
//		}
//		else
//		{
//			protail->next = newnode;
//			protail = newnode;
//		}
//		if (cur)cur = cur->next;
//	}
//	return prohead;
//}
//
//node* calculate(int base, int exp)
//{
//	node* result = createnode(1);
//	for (int i = 0; i < exp; i++)
//	{
//		result = multibydigit(result, base);
//	}
//	return result;
//}
//
//void printnum(node* head)
//{
//	// 1. 反转链表
//	node* prev = NULL;
//	node* cur = head;
//	while (cur)
//	{
//		node* next = cur->next;
//		cur->next = prev;
//		prev = cur;
//		cur = next;
//	}
//	// 2. 跳过高位前导0（保留最后一个0）
//	cur = prev;
//	while (cur && cur->digit == 0 && cur->next)
//		cur = cur->next;
//	// 3. 输出
//	if (!cur)
//		cout << 0;
//	else 
//	{
//		while (cur) 
//		{
//			cout << cur->digit;
//			node* del = cur;
//			cur = cur->next;
//			free(del);
//		}
//	}
//	cout << endl;
//}
//
//int main()
//{
//	int n, a;
//	while (cin>>n>>a)
//	{
//		node* sum=createnode(0);
//		for (int i = 1; i <= n; i++)
//		{
//			node* result1 = calculate(a, i);
//			node* result2 = multibydigit(result1, i);
//			sum = add(sum, result2);
//		}
//		printnum(sum);
//	}
//	return 0;
//}