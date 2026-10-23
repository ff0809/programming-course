//#define maxsize 2000010
//#define maxnode 10010
//#include<iostream>
//using namespace std;
//
//typedef struct node
//{
//	node** children;
//	int ccount;
//	node* left;
//	node* right;
//}node;
//
//node* createnode()
//{
//	node* newnode = (node*)malloc(sizeof(node));
//	newnode->ccount = 0;
//	newnode->children = NULL;
//	newnode->left = newnode->right = NULL;
//	return newnode;
//}
//
//node* buildtree(const char*op)
//{
//	node* root = createnode();
//	node* stack[maxnode] = {};
//	int top = 0;
//	stack[top] = root;
//	for (int i = 0; op[i] != '\0'; i++)
//	{
//		if (op[i] == 'd')
//		{
//			node* newnode = createnode();
//			node* parent = stack[top];
//			parent->ccount++;
//			parent->children = (node**)realloc(parent->children, parent->ccount * sizeof(node*));
//			parent->children[parent->ccount - 1] = newnode;
//			stack[++top] = newnode;
//		}
//		else
//		{
//			top--;
//		}
//	}
//	return root;
//}
//
//void change(node*root)
//{
//	if (root == NULL)
//	{
//		return;
//	}
//	int pos = root->ccount;
//	if (pos == 0)
//	{
//		root->left = NULL;
//	}
//	else
//	{
//		root->left = root->children[0];
//		for (int i = 0; i < pos - 1; i++)
//		{
//			root->children[i]->right = root->children[i + 1];
//		}
//		root->children[pos - 1]->right = NULL;
//	}
//	for (int i = 0; i < pos; i++)
//	{
//		change(root->children[i]);
//	}
//}
//
//int odepth(node* root)
//{
//	if (root == NULL)return -1;
//	if (root->ccount == 0)return 0;
//	int maxdepth = 0;
//	for (int i = 0; i < root->ccount; i++)
//	{
//		int depth = odepth(root->children[i]);
//		if (depth > maxdepth)
//		{
//			maxdepth = depth;
//		}
//	}
//	return 1 + maxdepth;
//}
//
//int ndepth(node* root)
//{
//	if (root == NULL)return -1;
//	if (root->left == NULL && root->right == NULL)return 0;
//	int d1 = ndepth(root->left);
//	int d2 = ndepth(root->right);
//	return((d1>d2) ? (1 + d1) : (1 + d2));
//}
//
//void free_tree(node* root) {
//	if (root == NULL) return;
//	for (int i = 0; i < root->ccount; i++) {
//		free_tree(root->children[i]);
//	}
//	if (root->children != NULL) {
//		free(root->children);
//	}
//	free(root);
//}
//
//int main()
//{
//	int n = 1;
//	while (true)
//	{
//		char op[maxsize];
//		cin >> op;
//		if (op[0]=='#')break;
//		node*root=buildtree(op);
//		change(root);
//		cout << "Tree " << n << ": " << odepth(root) << " => " << ndepth(root) << endl;
//		n++;
//		free_tree(root);
//	}
//	return 0;
//}