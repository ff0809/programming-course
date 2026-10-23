#define maxsize 101
#include<iostream>
using namespace std;

int ti[maxsize] = {};
int pre[maxsize][maxsize] = {};
int nex[maxsize][maxsize] = {};
int indegree[maxsize] = {};
int ee[maxsize] = { 0 };
int le[maxsize] = { 0 };
int toporder[maxsize] = {};

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> ti[i] >> pre[i][0];
		indegree[i] = pre[i][0];
		for (int j = 1; j <= indegree[i]; j++)
		{
			cin >> pre[i][j];
			int p = pre[i][j];
			nex[p][++nex[p][0]] = i;
		}
	}

	int queue[maxsize] = {};
	int front = 0, rear = 0;
	int count = 0;
	for (int i = 1; i <= n; i++)
	{
		if (indegree[i] == 0)
		{
			queue[rear++] = i;
		}
	}
	while (front < rear)
	{
		int u = queue[front++];
		toporder[count++] = u;
		for (int i = 1; i <= nex[u][0]; i++)
		{
			int v = nex[u][i];
			if (--indegree[v] == 0)
			{
				queue[rear++] = v;
			}
		}
	}
	for (int i = 0; i < count; i++)
	{
		int u = toporder[i];
		if (pre[u][0] == 0)
		{
			ee[u] = ti[u];
		}
		else
		{
			int maxtime = 0;
			for (int j = 1; j <= pre[u][0]; j++)
			{
				int v = pre[u][j];
				if (ee[v] > maxtime)maxtime = ee[v];
			}
			ee[u] = maxtime + ti[u];
		}
	}
	int t = 0;
	for (int i = 1; i <= n; i++)
	{
		if (ee[i] > t)
		{
			t = ee[i];
		}
	}
	for (int i = 1; i <= n; i++)
	{
		le[i] = t;
	}
	for (int i = count - 1; i >= 0; i--)
	{
		int u = toporder[i];
		for (int j = 1; j <= nex[u][0]; j++)
		{
			int v = nex[u][j];
			int temp = le[v] - ti[v];
			if (temp < le[u])
			{
				le[u] = temp;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		cout << ee[i] << " " << (ee[i] == le[i] ? 1 : 0) << endl;
	}
	return 0;
}

/**
 * @brief 程序入口
 * 1. 输入数据，建立前后驱关系
 * 2. 拓扑排序得到拓扑序
 * 3. 计算最早完成时间
 * 4. 计算最晚完成时间
 * 5. 判断关键活动并输出
 */
int main() {
	int n;
	cin >> n;

	// 输入数据并建立关系
	for (int i = 1; i <= n; i++) {
		cin >> ti[i] >> pre[i][0];
		indegree[i] = pre[i][0];
		for (int j = 1; j <= indegree[i]; j++) {
			cin >> pre[i][j];
			int p = pre[i][j];
			nex[p][++nex[p][0]] = i; // 建立后继关系
		}
	}

	// 拓扑排序
	int queue[maxsize] = {};
	int front = 0, rear = 0;
	int count = 0;
	for (int i = 1; i <= n; i++) {
		if (indegree[i] == 0) {
			queue[rear++] = i;
		}
	}

	while (front < rear) {
		int u = queue[front++];
		toporder[count++] = u;
		for (int i = 1; i <= nex[u][0]; i++) {
			int v = nex[u][i];
			if (--indegree[v] == 0) {
				queue[rear++] = v;
			}
		}
	}

	// 计算最早完成时间
	for (int i = 0; i < count; i++) {
		int u = toporder[i];
		if (pre[u][0] == 0) {
			ee[u] = ti[u];
		}
		else {
			int maxtime = 0;
			for (int j = 1; j <= pre[u][0]; j++) {
				int v = pre[u][j];
				if (ee[v] > maxtime) maxtime = ee[v];
			}
			ee[u] = maxtime + ti[u];
		}
	}

	// 计算总时间
	int t = 0;
	for (int i = 1; i <= n; i++) {
		if (ee[i] > t) {
			t = ee[i];
		}
	}

	// 初始化最晚完成时间
	for (int i = 1; i <= n; i++) {
		le[i] = t;
	}

	// 计算最晚完成时间（逆拓扑序）
	for (int i = count - 1; i >= 0; i--) {
		int u = toporder[i];
		for (int j = 1; j <= nex[u][0]; j++) {
			int v = nex[u][j];
			int temp = le[v] - ti[v];
			if (temp < le[u]) {
				le[u] = temp;
			}
		}
	}

	// 输出结果
	for (int i = 1; i <= n; i++) {
		cout << ee[i] << " " << (ee[i] == le[i] ? 1 : 0) << endl;
	}

	return 0;
}