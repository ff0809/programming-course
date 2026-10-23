//#define maxv 500
//#include<iostream>
//using namespace std;
//
//typedef struct ArcNode {
//	int adjvex;
//	struct ArcNode* nextarc;
//} ArcNode;
//
//typedef struct VNode {
//	int data;
//	ArcNode* firstarc;
//	int indegree;
//} VNode;
//
//typedef struct {
//	VNode vertices[maxv];
//	int vexnum;
//}graph;
//
//int* topsort(graph& g)
//{
//	int queue[maxv] = {};
//	int front = 0, rear = 0;
//	int count = 0;
//	for (int i = 1; i <= g.vexnum; i++)
//	{
//		if (g.vertices[i].indegree == 0)
//		{
//			queue[rear++] = i;
//		}
//	}
//	int* result = (int*)malloc(maxv * sizeof(int));
//	while (front < rear)
//	{
//		int u = queue[front++];
//		result[++count] = g.vertices[u].data;
//		ArcNode* p = g.vertices[u].firstarc;
//		while (p != NULL)
//		{
//			int v = p->adjvex;
//			if (--g.vertices[v].indegree == 0)
//			{
//				queue[rear++] = v;
//			}
//			p = p->nextarc;
//		}
//	}
//	if (count != g.vexnum)
//	{
//		return NULL;
//	}
//	return result;
//}
//
//void creategraph(graph& g, int k, int** array, int num)
//{
//	g.vexnum = k;
//	for (int i = 1; i <= k; i++)
//	{
//		g.vertices[i].data = i;
//		g.vertices[i].firstarc = NULL;
//		g.vertices[i].indegree = 0;
//	}
//	for (int i = 0; i < num; i++)
//	{
//		int u = array[i][0];
//		int v = array[i][1];
//		ArcNode* newarc = (ArcNode*)malloc(sizeof(ArcNode));
//		newarc->adjvex = v;
//		newarc->nextarc = g.vertices[u].firstarc;
//		g.vertices[u].firstarc = newarc;
//		g.vertices[v].indegree++;
//	}
//}
//int main()
//{
//	int k, n, m;
//	cin >> k >> n >> m;
//	int** row = (int**)malloc(n * sizeof(int*));
//	for (int i = 0; i < n; i++)
//	{
//		row[i] = (int*)malloc(2 * sizeof(int));
//		cin >> row[i][0] >> row[i][1];
//	}
//	int** col = (int**)malloc(m * sizeof(int*));
//	for (int i = 0; i < m; i++)
//	{
//		col[i] = (int*)malloc(2 * sizeof(int));
//		cin >> col[i][0] >> col[i][1];
//	}
//	graph rowg, colg;
//	creategraph(rowg, k, row, n);
//	int* rowt = topsort(rowg);
//	if (rowt == NULL)
//	{
//		cout << "-1" << endl;
//		return 0;
//	}
//	creategraph(colg, k, col, m);
//	int* colt = topsort(colg);
//	if (colt == NULL)
//	{
//		cout << "-1" << endl;
//		return 0;
//	}
//	int* rowpos = (int*)malloc((k + 1) * sizeof(int));
//	int* colpos = (int*)malloc((k + 1) * sizeof(int));
//	for (int i = 1; i <= k; i++)
//	{
//		rowpos[rowt[i]] = i - 1;
//		colpos[colt[i]] = i - 1;
//	}
//	int** matrix = (int**)malloc(k * sizeof(int*));
//	for (int i = 0; i < k; i++)
//	{
//		matrix[i] = (int*)calloc(k, sizeof(int));
//	}
//	for (int i = 1; i <= k; i++)
//	{
//		int r = rowpos[i];
//		int c = colpos[i];
//		matrix[r][c] = i;
//	}
//	for (int i = 0; i < k; i++)
//	{
//		for (int j = 0; j < k; j++)
//		{
//			cout << matrix[i][j] << " ";
//		}
//		cout << endl;
//	}
//	return 0;
//}
