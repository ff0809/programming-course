#define maxsize 10001
#include<iostream>
using namespace std;

typedef struct
{
	int data[maxsize];
	int front;
	int rear;
	int size;//存储当前队列长度
	int capacity;//存储队列最大容量，即用户输入的第一行--n
}queue;

void init(queue& q, int n)
{
	q.front = 0;
	q.rear = 0;
	q.size = 0;
	q.capacity = n + 1;
}

void enqueue(queue& a, queue& b, int e)
{
	if ((a.rear + 1) % a.capacity != a.front)
	{
		a.data[a.rear] = e;
		a.rear = (a.rear + 1) % a.capacity;
		a.size++;
		while (b.size > 0 && b.data[(b.rear - 1 + b.capacity) % b.capacity] <= e)
		{
			b.rear = (b.rear - 1 + b.capacity) % b.capacity;
			b.size--;
		}
		b.data[b.rear] = e;
		b.rear = (b.rear + 1) % b.capacity;
		b.size++;
	}
	else
	{
		cout << "Queue is Full" << endl;
	}
}

void dequeue(queue& a, queue& b)
{
	if (a.rear != a.front)
	{
		int e = a.data[a.front];
		a.front = (a.front + 1) % a.capacity;
		a.size--;
		cout << e << endl;
		if (b.data[b.front] == e)
		{
			b.front = (b.front + 1) % b.capacity;
			b.size--;
		}
	}
	else
	{
		cout << "Queue is Empty" << endl;
	}
}

void getmax(queue& q)
{
	if (q.size > 0)
	{
		cout << q.data[q.front] << endl;
	}
	else
	{
		cout << "Queue is Empty" << endl;
	}
}

int main()
{
	int n;
	cin >> n;
	queue a, b;
	init(a,n);
	init(b,n);
	while (true)
	{
		string order;
		cin >> order;
		if (order == "quit")
		{
			break;
		}
		else if (order == "enqueue")
		{
			int num;
			cin >> num;
			enqueue(a, b, num);
		}
		else if (order == "dequeue")
		{
			dequeue(a, b);
		}
		else if (order == "max")
		{
			getmax(b);
		}
	}
	if (a.size == 0)
	{
		cout << "Queue is Empty" << endl;
	}
	else
	{
		int i=a.front;
		while (i != a.rear)
		{
			cout << a.data[i] << " ";
			i = (i + 1) % a.capacity;
		}
		cout << endl;
	}
	return 0;
}