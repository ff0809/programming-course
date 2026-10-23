//#include<iostream>
//using namespace std;
//#define Max 101
//#define Maxedge 5050
//
//typedef struct edge
//{
//	int start;
//	int end;
//	int length;
//}edge;
//
//int find(int parent[], int i)
//{
//	while (parent[i] != 0)
//	{
//		i = parent[i];
//	}
//	return i;
//}
//
//int main()
//{
//	int n;
//	cin >> n;
//	int parent[Max] = { 0 };
//	int len[Max][Max] = { 0 };
//	for (int i = 1; i <= n; i++) {
//		for (int j = 1; j <= n; j++) {
//			cin >> len[i][j];
//		}
//	}
//	int m;
//	cin >> m;
//	for (int i = 0; i < m; i++)
//	{
//		int a, b;
//		cin >> a >> b;
//		int r1 = find(parent, a);
//		int r2 = find(parent, b);
//		if (r1 != r2)
//		{
//			parent[r1] = r2;
//		}
//	}
//	edge edges[Maxedge] = {};
//	int edgecount = 0;
//	for (int i = 1; i <= n; i++)
//	{
//		for (int j = i + 1; j <= n; j++)
//		{
//			edges[edgecount].start = i;
//			edges[edgecount].end = j;
//			edges[edgecount].length = len[i][j];
//			edgecount++;
//		}
//	}
//	for (int i = 0; i < edgecount; i++)
//	{
//		for (int j = 0; j < edgecount - i - 1; j++)
//		{
//			if (edges[j].length > edges[j+1].length)
//			{
//				edge temp = edges[j];
//				edges[j] = edges[j + 1];
//				edges[j + 1] = temp;
//			}
//		}
//	}
//	int total = 0;
//	for (int i = 0; i < edgecount; i++)
//	{
//		int r1 = find(parent, edges[i].start);
//		int r2 = find(parent, edges[i].end);
//		if (r1 != r2)
//		{
//			parent[r1] = r2;
//			total += edges[i].length;
//		}
//	}
//	cout << total << endl;
//	return 0;
//}