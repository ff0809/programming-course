//#include<iostream>
//using namespace std;
//
//int map1[6][6] = {};
//
//// x：当前所在端点；k：已经扩展的深度（走过的边数）；s：目前的访问序列
//void dfs(int x, int depth, string s)
//{
//	// 终止条件：走过8条边（k>=8），输出路径并返回
//	if (depth >= 8)
//	{
//		cout << s << endl;
//		return;
//	}
//	for (int y = 1; y <= 5; y++)
//	{
//		// 若当前顶点x和y之间有未访问的边
//		if (map1[x][y] == 1)
//		{
//			// 标记边为已访问（无向边，双向置0）
//			map1[x][y] = map1[y][x] = 0;
//			// 递归扩展：当前端点变为y，深度+1，序列追加y
//			dfs(y, depth + 1, s + char('0' + y));
//			// 回溯：恢复边的未访问状态（双向置1）
//			map1[x][y] = map1[y][x] = 1;
//		}
//	}
//}
//
//int main()
//{
//	for (int i = 1; i <= 5; i++)
//	{
//		for (int j = 1; j <= 5; j++)
//		{
//			if (i == j)map1[i][j] = 0;
//			else map1[i][j] = 1;
//		}
//	}
//	map1[1][4] = map1[4][1] = map1[2][4] = map1[4][2] = 0;
//	// 初始调用dfs：起点是1，初始深度k=0（未走边），初始序列是"1"
//	dfs(1, 0, "1");
//	return 0;
//}