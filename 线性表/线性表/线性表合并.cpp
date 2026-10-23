//#include<iostream>
//#define initsize 10
//using namespace std;
//
//typedef struct
//{
//	int* elem;
//	int length;
//	int size;
//}sqlist;
//
//void initlist(sqlist& l)
//{
//	l.elem = (int*)malloc(sizeof(int) * initsize);
//	if (!l.elem)exit(OVERFLOW);
//	l.length = 0;
//	l.size = initsize;
//}
//
//void mergelist(sqlist la, sqlist lb, sqlist& lc)
//{
//	int* pa = la.elem;
//	int* pb = lb.elem;
//	lc.elem = (int*)malloc(sizeof(int) * (la.length + lb.length));
//	int* pc = lc.elem;
//	if (!lc.elem)exit(OVERFLOW);
//	lc.length = la.length + lb.length;
//	lc.size = la.length + lb.length;
//	int* p,*q;
//	p = &(la.elem[la.length - 1]);
//	q = &(lb.elem[lb.length - 1]);
//	while (pa<=p && pb<=q)
//	{
//		if (*pa < *pb)
//		{
//			*pc++ = *pa++;
//		}
//		else
//		{
//			*pc++ = *pb++;
//		}
//	}
//	while (pa <= p)*pc++ = *pa++;
//	while (pb <= q)*pc++ = *pb++;
//}
//
//void printlist(sqlist& l)
//{
//	for (int i = 0; i < l.length; i++)
//	{
//		cout << l.elem[i] << " ";
//	}
//	cout << endl;
//}
//
//int main()
//{
//	sqlist la, lb, lc;
//	initlist(la);
//	initlist(lb);
//
//	// 填充有序数据
//	for (int i = 0; i < 5; ++i)
//	{
//		la.elem[i] = i * 2; // 0,2,4,6,8
//		lb.elem[i] = i * 2 + 1; // 1,3,5,7,9
//	}
//	la.length = 5;
//	lb.length = 5;
//
//	cout << "线性表A: ";
//	printlist(la);
//	cout << "线性表B: ";
//	printlist(lb);
//
//	mergelist(la, lb, lc);
//
//	cout << "合并后的线性表C: ";
//	printlist(lc);
//
//	// 释放内存
//	free(la.elem);
//	free(lb.elem);
//	free(lc.elem);
//
//	return 0;
//
//}