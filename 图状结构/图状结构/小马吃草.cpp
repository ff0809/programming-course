//#define infinite 1000000000
//#define maxn 1001
//#include<iostream>
//using namespace std;
//
//int ds[maxn][maxn] = {};
//int grass[maxn] = {};
//
//int main()
//{
//    int n, m;
//    cin >> n >> m;
//
//    for (int i = 1; i <= n; i++) {
//        for (int j = 1; j <= n; j++) {
//            ds[i][j] = infinite;
//        }
//        ds[i][i] = 0;
//    }
//
//    for (int i = 1; i <= m; i++)
//    {
//        int x, y, w;
//        cin >> x >> y >> w;
//        if (w < ds[x][y])
//        {
//            ds[x][y] = w;
//            ds[y][x] = w;
//        }
//    }
//
//    for (int k = 1; k <= n; k++)
//    {
//        for (int i = 1; i <= n; i++)
//        {
//            if (ds[i][k] == infinite) continue;
//            for (int j = i; j <= n; j++)
//            {
//                if (ds[k][j] == infinite) continue;
//
//                int new_dist = ds[i][k] + ds[k][j];
//                if (new_dist < ds[i][j])
//                {
//                    ds[i][j] = new_dist;
//                    ds[j][i] = new_dist;
//                }
//            }
//        }
//    }
//
//    int h, r;
//    cin >> h >> r;
//    for (int i = 1; i <= h; i++)
//    {
//        cin >> grass[i];
//    }
//
//    for (int i = 1; i <= r; i++)
//    {
//        int start, end;
//        cin >> start >> end;
//        int d = infinite;
//        for (int j = 1; j <= h; j++)
//        {
//            int s = grass[j];
//            if (ds[start][s] < d) 
//            { 
//                if (ds[s][end] < d - ds[start][s]) 
//                {
//                    int new_d = ds[start][s] + ds[s][end];
//                    if (new_d < d) 
//                    {
//                        d = new_d;
//                    }
//                }
//            }
//        }
//        cout << d << endl;
//    }
//    return 0;
//}