//#define _CRT_SECURE_NO_WARNINGS
//#define maxsize 100
//#include<iostream>
//#include<cstdlib>
//#include<cstring>
//using namespace std;
//
//typedef struct treenode
//{
//	char c;
//	struct treenode* left;
//	struct treenode* right;
//}treenode;
//
//typedef struct
//{
//	treenode* data[maxsize];
//	int top;
//}sqstack;
//
//void initstack(sqstack& s)
//{
//	s.top = -1;
//}
//
//bool isempty(sqstack& s)
//{
//	return(s.top == -1);
//}
//
//void pushstack(sqstack& s,treenode*t)
//{
//	s.data[++s.top] = t;
//}
//
//treenode* popstack(sqstack& s)
//{
//	if (isempty(s))return NULL;
//	return s.data[s.top--];
//}
//
///**
// * @brief 根据栈操作序列构建二叉树
// * @return treenode* 构建完成的二叉树根节点
// * 核心逻辑：用lastpop记录上一个出栈节点，控制右子树赋值；栈顶节点控制左子树赋值
// */
//treenode* buildtree()
//{
//    sqstack s;
//    initstack(s);
//    treenode* root = NULL;
//    treenode* lastpop = NULL; // 记录上一个出栈节点（用于赋值右子树）
//    int num;
//    cin >> num;
//    for (int i = 0; i < 2 * num; i++)
//    {
//        char op[10];
//        cin >> op;
//        if (strcmp(op, "push") == 0)
//        {
//            // 创建新节点并初始化
//            treenode* newnode = (treenode*)malloc(sizeof(treenode));
//            char mc;
//            cin >> mc;
//            newnode->c = mc;
//            newnode->left = newnode->right = NULL;
//
//            if (root == NULL) root = newnode; // 第一个节点为根节点
//            else
//            {
//                if (lastpop == NULL) s.data[s.top]->left = newnode; // 左子树赋值
//                else lastpop->right = newnode; // 右子树赋值
//            }
//            pushstack(s, newnode);
//            lastpop = NULL;
//        }
//        else lastpop = popstack(s); // 出栈时更新lastpop
//    }
//    return root;
//}
//
///**
// * @brief 递归实现后序遍历（左→右→根）
// * @param root 二叉树根节点
// */
//void postorder(treenode* root)
//{
//    if (root == NULL) return;
//    postorder(root->left);
//    postorder(root->right);
//    cout << root->c;
//}
//
//int main()
//{
//	treenode* t=buildtree();
//	postorder(t);
//	return 0;
//}