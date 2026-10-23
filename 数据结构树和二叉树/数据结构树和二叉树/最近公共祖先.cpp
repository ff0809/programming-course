//#include<iostream>
//using namespace std;
//
//int* getanc(int* parent,int node,int &count)
//{
//	int* anc = NULL;
//	count = 0;
//	int current = node;
//	while (current != 0)
//	{
//		count++;
//		anc = (int*)realloc(anc, count * sizeof(int));
//		anc[count - 1] = current;
//		current = parent[current];
//	}
//	return anc;
//}
//
//int cor(int x,int y,int*parent)
//{
//	int count;
//	int current = y;
//	int*anc = getanc(parent, x, count);
//	while (current!=0)
//	{
//		for (int i = 0; i < count; i++)
//		{
//			if (anc[i] == current)return current;
//		}
//		current = parent[current];
//	}
//	return -1;
//}
//
//int main()
//{
//	int t;
//	cin >> t;
//	for (int i = 0; i < t; i++)
//	{
//		int n, m;
//		cin >> n >> m;
//		int* parent = (int*)malloc((n + 1) * sizeof(int));
//		for (int i = 1; i <= n; i++)
//		{
//			parent[i] = 0;
//		}
//		for (int i = 0; i < n - 1; i++)
//		{
//			int a, b;
//			cin >> a >> b;
//			parent[b] = a;
//		}
//		for (int i = 0; i < m ; i++)
//		{
//			int x, y;
//			cin >> x >> y;
//			int result=cor(x, y, parent);
//			cout << result << endl;
//		}
//	}
//	return 0;
//}
//
///**
// * @brief 获取节点node的所有祖先，存储在动态数组中
// * @param parent 父节点数组，node 目标节点，count 输出参数（祖先个数）
// * @return int* 祖先数组（从node到根节点）
// */
//int* getanc(int* parent, int node, int& count)
//{
//    int* anc = NULL;
//    count = 0;
//    int current = node;
//    while (current != 0) // 根节点的父节点为0，循环终止
//    {
//        count++;
//        anc = (int*)realloc(anc, count * sizeof(int));
//        anc[count - 1] = current;
//        current = parent[current];
//    }
//    return anc;
//}
//
///**
// * @brief 查找x和y的最近公共祖先
// * @param x,y 目标节点，parent 父节点数组
// * @return int 最近公共祖先编号（未找到返回-1）
// */
//int cor(int x, int y, int* parent)
//{
//	int count;
//	int* anc = getanc(parent, x, count); // 获取x的所有祖先
//	int current = y;
//	while (current != 0)
//	{
//		// 遍历x的祖先，找到第一个与current匹配的节点
//		for (int i = 0; i < count; i++)
//			if (anc[i] == current)
//			{
//				free(anc); // 释放动态数组，避免泄漏
//				return current;
//			}
//		current = parent[current];
//	}
//	free(anc);
//	return -1;
//}