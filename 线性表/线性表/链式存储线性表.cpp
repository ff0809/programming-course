//#include<iostream>
//#include<cstdlib>
//using namespace std;
//
//typedef struct lnode
//{
//	int data;
//	struct lnode* next;
//
//}lnode,*linklist;
//
//void createlist(linklist& l,int a[],int n)
//{
//	lnode* s, *r;
//	l = (lnode*)malloc(sizeof(lnode));
//	r = l;
//	for (int i = 0; i < n; i++)
//	{
//		s = (lnode*)malloc(sizeof(lnode));
//		s->data = a[i];
//		r->next = s;
//		r = s;
//	}
//	r->next = NULL;
//}
//
//bool getelem(linklist& l, int& e,int j)
//{
//	lnode* p;
//	p = l->next;
//	int i = 1;
//	while (p&&i<j)
//	{
//		p = p->next;
//		i++;
//	}
//	if (!p || i > j)return false;
//	e = p->data;
//	return true;
//}
//
//bool insertlist(linklist& l, int i, int e)
//{
//	lnode* p = l->next;
//	int j = 1;
//	while (p && j < i)
//	{
//		p = p->next;
//		j++;
//	}
//	if (!p || j > i)return false;
//	lnode* q = (lnode*)malloc(sizeof(lnode));
//	q->data = e;
//	q->next = p->next;
//	p->next = q;
//	return true;
//}
//
//bool deletelist(linklist& l, int i)
//{
//	lnode* p = l->next;
//	int j = 1;
//	while (p && j < i-1)
//	{
//		p = p->next;
//		j++;
//	}
//	if (!p || j > i-1)return false;
//	lnode* q = p->next;
//	p->next = q->next;
//	free(q);
//	return true;
//}
//
//void displist(linklist& l)
//{
//	lnode*p = l->next;
//	while (p)
//	{
//		cout << p->data << " ";
//		p = p->next;
//	}
//	cout << endl;
//}
//
//void mergelist(linklist& la, linklist& lb, linklist& lc)
//{
//	lnode* pa, * pb, * pc;
//	pa = la->next;
//	pb = lb->next;
//	pc = lc = la;
//	while (pa && pb)
//	{
//		if (pa->data <= pb->data)
//		{
//			pc->next = pa;
//			pc = pa;
//			pa = pa->next;
//		}
//		else
//		{
//			pc->next = pb;
//			pc = pb;
//			pb = pb->next;
//		}
//	}
//	pc->next = pa ? pa : pb;
//	free(lb);
//}
//
//void unionlist(linklist& la, linklist& lb)
//{
//	int x;
//	lnode* pb = lb->next;
//	while (pb)
//	{
//		lnode* pa = la->next;
//		bool flag = false;
//		x = pb->data;
//		while (pa)
//		{
//			if (pa->data == x)
//			{
//				flag = true;
//				break;
//			}
//			pa = pa->next;
//		}
//		if (flag == false)
//		{
//			lnode*p = (lnode*)malloc(sizeof(lnode));
//			p->data = x;
//			p->next = la->next;
//			la->next = p;
//		}
//		pb = pb->next;
//	}
//}
//
//void reverselist(linklist& H)
//{
//	lnode* p = H->next;
//	H->next = NULL;
//	while (p)
//	{
//		lnode* temp = p->next;
//		p->next = H->next;
//		H->next = p;
//		p = temp;
//	}
//}
//
//int main()
//{
//    linklist l;
//    int arr[] = {1, 2, 3, 4, 5};
//    int n = sizeof(arr) / sizeof(arr[0]);
//
//    // 创建链表
//    createlist(l, arr, n);
//    cout << "初始链表: ";
//    displist(l);
//
//    // 插入元素
//    insertlist(l, 3, 99); // 在第3个位置后插入99
//    cout << "插入99后: ";
//    displist(l);
//
//    // 删除元素
//    deletelist(l, 2); // 删除第2个位置后的元素
//    cout << "删除第2个位置后元素后: ";
//    displist(l);
//
//    // 查找元素
//    int e;
//    if (getelem(l, e, 4)) {
//        cout << "第4个元素为: " << e << endl;
//    } else {
//        cout << "查找失败" << endl;
//    }
//
//	//逆序链表
//	reverselist(l);
//	cout << "逆序后，链表为：";
//	displist(l);
//
//    return 0;
//}