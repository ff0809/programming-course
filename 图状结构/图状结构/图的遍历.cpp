//#include<iostream>
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
//	VNode list[1000];
//	int n, e;
//}Graph;
//
//void initgraph(Graph& g, int n)
//{
//	g.e = 0;
//	g.n = n;
//	for (int i = 0; i < n; i++)
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
//void sortlist(Graph& g)
//{
//	for (int u = 0; u < g.n; u++)
//	{
//		int temp[1000];
//		int count = 0;
//		ArcNode* p = g.list[u].firstarc;
//		while (p != NULL)
//		{
//			temp[count++] = p->adjvex;
//			ArcNode* q = p;
//			p = p->nextarc;
//			free(q);
//		}
//		g.list[u].firstarc = NULL;
//
//		for (int i = 0; i < count - 1; i++)
//		{
//			for (int j = 0; j < count - 1 - i; j++)
//			{
//				if (temp[j] > temp[j + 1])
//				{
//					int t = temp[j];
//					temp[j] = temp[j + 1];
//					temp[j + 1] = t;
//				}
//			}
//		}
//
//		ArcNode* tail = NULL;
//		for (int i = 0; i < count; i++)
//		{
//			ArcNode* newnode = (ArcNode*)malloc(sizeof(ArcNode));
//			newnode->adjvex = temp[i];
//			newnode->nextarc = NULL;
//			if (g.list[u].firstarc == NULL)
//			{
//				g.list[u].firstarc = newnode;
//				tail = newnode;
//			}
//			else
//			{
//				tail->nextarc = newnode;
//				tail = newnode;
//			}
//		}
//	}
//}
//
//int component[1000] = {};
//int idx = 0;
//
//void dfs(Graph& g, int u, bool visited[])
//{
//	visited[u] = true;
//	component[idx++] = u;
//	ArcNode* p = g.list[u].firstarc;
//	while (p != NULL)
//	{
//		int v = p->adjvex;
//		if (!visited[v])
//		{
//			dfs(g, v, visited);
//		}
//		p = p->nextarc;
//	}
//}
//
//void bfs(Graph& g, int u, bool visited[])
//{
//	visited[u] = true;
//	int front = 0, rear = 0;
//	component[idx++] = u;
//	int queue[1000] = {};
//	queue[rear++] = u;
//	while (front < rear)
//	{
//		int w = queue[front++];
//		ArcNode* p = g.list[w].firstarc;
//		while (p != NULL)
//		{
//			int v = p->adjvex;
//			if (!visited[v])
//			{
//				visited[v] = true;
//				component[idx++] = v;
//				queue[rear++] = v;
//			}
//			p = p->nextarc;
//		}
//	}
//}
//
//void printcomponent()
//{
//	cout << "{";
//	for (int i = 0; i < idx; i++) {
//		if (i > 0) cout << " ";
//		cout << component[i];
//	}
//	cout << "}";
//	idx = 0;
//}
//
//int main()
//{
//	int n, e;
//	cin >> n >> e;
//	Graph g;
//	initgraph(g, n);
//
//	for (int i = 0; i < e; i++) {
//		int u, v;
//		cin >> u >> v;
//		addedge(g, u, v);
//	}
//
//	sortlist(g);
//
//	bool visited_dfs[1000] = { false };
//	for (int i = 0; i < n; i++)
//	{
//		if (!visited_dfs[i])
//		{
//			dfs(g, i, visited_dfs);
//			printcomponent();
//		}
//	}
//	cout << endl;
//
//	bool visited_bfs[1000] = { false };
//	for (int i = 0; i < n; i++)
//	{
//		if (!visited_bfs[i])
//		{
//			bfs(g, i, visited_bfs);
//			printcomponent();
//		}
//	}
//
//	return 0;
//}