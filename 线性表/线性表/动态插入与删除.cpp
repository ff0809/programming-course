//#include<iostream>
//#include<cstdlib>
//#define increasesize 10
//#define initsize 10
//#define OVERFLOW -2
//using namespace std;
//
//typedef struct
//{
//	int* elem;
//	int length;
//	int size;
//
//}sqlist;
//
//void initlist(sqlist& l)
//{
//	l.elem = (int*)malloc(sizeof(int) * initsize);
//	if (!l.elem)exit(OVERFLOW);
//	l.length = 0;
//	l.size = initsize;
//}
//bool insertlist(sqlist& l,int i,int e)
//{
//	int *p, *q;
//	if (i<1 || i>l.length+1)return false;
//	if (l.length >= l.size)
//	{
//		int*newbase = (int*)realloc(l.elem, sizeof(int) * (l.size + increasesize));\
//		if (!newbase)exit(OVERFLOW);
//		l.elem = newbase;
//		l.size += increasesize;
//	}
//	q = &(l.elem[i - 1]);
//	for (p = &(l.elem[l.length - 1]); p >= q; p--)
//	{
//		*(p+1)=*p;
//	}
//	*q = e;
//	l.length++;
//	return true;
//}
//
//bool deletelist(sqlist& l, int i)
//{
//	int* p, * q;
//	if (i<1 || i>l.length)return false;
//	q = &(l.elem[i - 1]);
//	for (p = q; p < &(l.elem[l.length - 1]); p++)
//	{
//		*p = *(p + 1);
//	}
//	l.length--;
//	return true;
//}
//
//int main()
//{
//	sqlist l;
//	initlist(l);
//
//}