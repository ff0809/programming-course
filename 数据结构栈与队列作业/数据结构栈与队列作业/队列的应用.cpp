#define maxsize 1000
#define maxlen 1000000
#include<iostream>
using namespace std;

int arr[maxsize][maxsize];
int visit[maxsize][maxsize] = { 0 };

typedef struct
{
    int x;
    int y;
}pos;

typedef struct
{
    pos data[maxlen];
    int front;
    int rear;
}queue;

void init(queue& q)
{
    q.front = q.rear = 0;
}

void push(queue& q, int x, int y)
{
    q.data[q.rear].x = x;
    q.data[q.rear].y = y;
    q.rear = (q.rear + 1) % maxlen;
}

void pop(queue& q, int& x, int& y)
{
    x = q.data[q.front].x;
    y = q.data[q.front].y;
    q.front = (q.front + 1) % maxlen;
}

bool isempty(queue& q)
{
    return q.front == q.rear;
}

queue q;
bool search(int n, int m, int startx, int starty)
{
    bool flag = false;
    int way[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
    init(q);
    push(q, startx, starty);
    visit[startx][starty] = 1;

    while (!isempty(q))
    {
        int x, y;
        pop(q, x, y);
        // 只要区域内有1不在边缘，flag为true
        if (!(x == 0 || x == n - 1 || y == 0 || y == m - 1))
        {
            flag = true;
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = x + way[i][0];
            int ny = y + way[i][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m)
            {
                if (arr[nx][ny] == 1 && visit[nx][ny] == 0)
                {
                    visit[nx][ny] = 1;
                    push(q, nx, ny);
                }
            }
        }
    }
    return flag;
}

int main()
{
    int n, m;
    cin >> n >> m;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> arr[i][j];
            visit[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (arr[i][j] == 1 && visit[i][j] == 0)
            {
                bool flag = search(n, m, i, j);
                if (flag) count++;
            }
        }
    }
    cout << count << endl;
    return 0;
}
