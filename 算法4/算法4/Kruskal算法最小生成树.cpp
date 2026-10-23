#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Edge {
	int u, v, w;
	bool operator<(const Edge& other)
	{
		return w < other.w;
	}
};

vector<int>fa;
int find(int x)
{
	if (fa[x] != x)
	{
		fa[x] = find(fa[x]);
	}
	return fa[x];
}

void unite(int x, int y)
{
	x = find(x);
	y = find(y);
	if (x != y)
	{
		fa[y] = x;
	}
}

void kruskal(vector<Edge>& edge, int n)
{
	fa.resize(n);
	for (int i = 0; i < n; i++)
	{
		fa[i] = i;
	}
	sort(edge.begin(), edge.end());

	int sum = 0;
	int count = 0;
	for (auto& e : edge)
	{
		int u = e.u;
		int v = e.v;
		int w = e.w;
		if (find(u) != find(v))
		{
			unite(u, v);
			sum += w;
			count++;
		}
		if (count == n - 1)
		{
			break;
		}
	}
	cout << "最小生成树总权重为" << sum << endl;
}

int main()
{
	int n, m;
	cout << "请依次输入顶点数和边数：";
	cin >> n >> m;
	vector<Edge> edges(m);
	cout << "请依次输入 " << m << " 条边（两个顶点+一个边权重值）：" << endl;
	for (int i = 0; i < m; i++) {
		cin >> edges[i].u >> edges[i].v >> edges[i].w;
	}

	kruskal(edges, n);
	return 0;
}