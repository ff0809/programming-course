//#include<iostream>
//#include<iomanip>
//using namespace std;
//
//typedef struct ArcNode
//{
//	int adjvex;
//	struct ArcNode* nextarc;
//}ArcNode;
//
//typedef struct VNode
//{
//	int no;
//	ArcNode* firstarc;
//}VNode;
//
//typedef struct
//{
//	VNode list[2010];
//	int n, e;
//}Graph;
//
//void initgraph(Graph& g, int n)
//{
//	g.e = 0;
//	g.n = n;
//	for (int i = 1; i <= n; i++)
//	{
//		g.list[i].no = i;
//		g.list[i].firstarc = NULL;
//	}
//}
//
//void addedge(Graph& g, int u, int v)
//{
//	ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
//	p->adjvex = v;
//	p->nextarc = NULL;
//	if (g.list[u].firstarc == NULL)
//	{
//		g.list[u].firstarc = p;
//	}
//	else
//	{
//		ArcNode* q = g.list[u].firstarc;
//		while (q->nextarc != NULL)
//		{
//			q = q->nextarc;
//		}
//		q->nextarc = p;
//	}
//	ArcNode* r = (ArcNode*)malloc(sizeof(ArcNode));
//	r->adjvex = u;
//	r->nextarc = NULL;
//	if (g.list[v].firstarc == NULL)
//	{
//		g.list[v].firstarc = r;
//	}
//	else
//	{
//		ArcNode* s = g.list[v].firstarc;
//		while (s->nextarc != NULL)
//		{
//			s = s->nextarc;
//		}
//		s->nextarc = r;
//	}
//	g.e++;
//}
//
//int bfs(Graph& g, int start)
//{
//	int visited[2010] = {0};
//	int queue[2010] = {0};
//	int front = 0, rear = 0;
//	int count = 1;
//	int level[2010] = {0};
//	queue[rear++] = start;
//	visited[start] = 1;
//	while (front < rear)
//	{
//		int cur = queue[front++];
//		if (level[cur] >= 6)continue;
//		ArcNode* p = g.list[cur].firstarc;
//		while (p != NULL)
//		{
//			if (!visited[p->adjvex])
//			{
//				queue[rear++] = p->adjvex;
//				visited[p->adjvex] = 1;
//				level[p->adjvex] = level[cur] + 1;
//				count++;
//			}
//			p = p->nextarc;
//		}
//	}
//	return count;
//}
//
//int main()
//{
//	int n, e;
//	cin >> n >> e;
//	Graph g;
//	initgraph(g, n);
//
//	for (int i = 0; i < e; i++)
//	{
//		int u, v;
//		cin >> u >> v;
//		addedge(g, u, v);
//	}
//
//	cout << fixed << setprecision(2) << endl;
//	for (int i = 1; i <= n; i++)
//	{
//		int result = bfs(g, i);
//		double ratio = double(result) /double(n) * 100.0;
//		cout << i << ": " << ratio << "%" << endl;
//	}
//	return 0;
//}