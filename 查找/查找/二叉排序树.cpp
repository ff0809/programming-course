//#include<iostream>
//using namespace std;
//
//typedef struct node
//{
//	int data;
//	int count;
//	struct node* left, *right;
//}node,*tree;
//
//tree search(tree t, int key)
//{
//	if (!t)return NULL;
//	if (t->data == key)return t;
//	if (key < t->data)return search(t->left, key);
//	if (key > t->data)return search(t->right, key);
//	return NULL;
//}
//
//tree insert(tree&t, int key)
//{
//	if (!t)
//	{
//		node* p = (node*)malloc(sizeof(node));
//		p->left = p->right = NULL;
//		p->data = key;
//		p->count = 1;
//		t = p;
//		return t;
//	}
//	else
//	{
//		if (t->data == key)
//		{
//			t->count++;
//			return t;
//		}
//		if (key < t->data)t->left = insert(t->left, key);
//		if (key > t->data)t->right = insert(t->right, key);
//	}
//	return t;
//}
//
//tree findmin(tree t)
//{
//	if (!t)return NULL;
//	while (t->left)t = t->left;
//	return t;
//}
//
//tree deln(node* p)
//{
//	if (!p->right)
//	{
//		node* q = p->left;
//		free(p);
//		return q;
//	}
//	else if (!p->left)
//	{
//		node* q = p->right;
//		free(p);
//		return q;
//	}
//	else
//	{
//		node* parent = p;
//		node* r = p->left;
//		while (r->right)
//		{
//			parent = r;
//			r = r->right;
//		}
//		p->data = r->data;
//		p->count = r->count;
//		if (parent == p)
//		{
//			parent->left = r->left;
//		}
//		else
//		{
//			parent->right = r->left;
//		}
//		free(r);
//		return p;
//	}
//}
//
//tree del(tree& t, int key)
//{
//	if (!t)return NULL;
//	if (key < t->data)t->left = del(t->left, key);
//	if (key > t->data)t->right = del(t->right, key);
//	if (key == t->data)
//	{
//		if (t->count > 1)
//		{
//			t->count--;
//		}
//		else
//		{
//			t = deln(t);
//		}
//	}
//	return t;
//}
//
//int countnum(tree t, int key)
//{
//	node* result = search(t, key);
//	if (result == NULL)return 0;
//	else
//	{
//		return result->count;
//	}
//}
//
//tree frontnum(tree t, int key)
//{
//	node* pre = NULL;
//	node* cur = t;
//	while (cur)
//	{
//		if (cur->data < key)
//		{
//			pre = cur;
//			cur = cur->right;
//		}
//		else
//		{
//			cur = cur->left;
//		}
//	}
//	return pre;
//}
//
//int main()
//{
//	int n;
//	cin >> n;
//	tree root = NULL;
//	for (int i = 0; i < n; i++)
//	{
//		int op;
//		cin >> op;
//		if (op == 1)
//		{
//			int x;
//			cin >> x;
//			insert(root, x);
//		}
//		else if (op == 2)
//		{
//			int x;
//			cin >> x;
//			node* result = search(root,x);
//			if (result == NULL)
//			{
//				cout << "None" << endl;
//			}
//			else
//			{
//				del(root, x);
//			}
//		}
//		else if (op == 3)
//		{
//			int x;
//			cin >> x;
//			cout << countnum(root, x) << endl;
//		}
//		else if (op == 4)
//		{
//			node* result = findmin(root);
//			cout << result->data << endl;
//		}
//		else if (op == 5)
//		{
//			int x;
//			cin >> x;
//			node* result = frontnum(root, x);
//			if (result == NULL)cout << "None" << endl;
//			else cout << result->data << endl;
//		}
//	}
//	return 0;
//}