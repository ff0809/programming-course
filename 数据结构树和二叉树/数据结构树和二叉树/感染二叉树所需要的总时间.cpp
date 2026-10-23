//#define maxsize 100010
//#include<iostream>
//using namespace std;
//
//int main()
//{
//	int n, start;
//	cin >> n >> start;
//	int parent[maxsize] = {};
//	int left[maxsize] = {};
//	int right[maxsize] = {};
//	for (int i = 0; i < n; i++)
//	{
//		parent[i] = -1;
//		left[i] = -1;
//		right[i] = -1;
//	}
//	for (int i = 0; i < n; i++)
//	{
//		int l, r;
//		cin >> l >> r;
//		left[i] = l;
//		right[i] = r;
//		if (l != -1)
//		{
//			parent[l] = i;
//		}
//		if (r != -1)
//		{
//			parent[r] = i;
//		}
//	}
//	int queue[maxsize] = {};
//	int visit[maxsize] = {};
//	int front = 0, rear = 0;
//	int time = 0;
//	queue[rear++] = start;
//	visit[start] = 1;
//	while (front < rear)
//	{
//		int current = rear - front;
//		for (int i = 0; i < current; i++)
//		{
//			int node = queue[front++];
//			if (parent[node] != -1 && visit[parent[node]] == 0)
//			{
//				visit[parent[node]] = 1;
//				queue[rear++] = parent[node];
//			}
//			if(left[node] != -1 && visit[left[node]] == 0)
//			{
//				visit[left[node]] = 1;
//				queue[rear++] = left[node];
//			}	
//			if (right[node] != -1 && visit[right[node]] == 0)
//			{
//				visit[right[node]] = 1;
//				queue[rear++] = right[node];
//			}
//		}
//		if (front < rear)
//		{
//			time++;
//		}
//	}
//	cout << time << endl;
//	return 0;
//}
