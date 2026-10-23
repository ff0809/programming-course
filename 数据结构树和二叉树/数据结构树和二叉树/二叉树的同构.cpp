//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//#include<cstdlib>
//#include<cstring>
//using namespace std;
//
//typedef struct node
//{
//	char c;
//	node* left;
//	node* right;
//}node;
//
///**
// * @brief 根据输入构建二叉树，返回根节点
// * @param n 输出参数，存储节点数
// * @return node* 二叉树根节点（空树返回NULL）
// */
//node* tree(int& n)
//{
//    cin >> n;
//    if (n == 0) return NULL;
//    node* nodes[10200] = {};       // 存储所有节点（支持n≤10100）
//    int leftval[10200] = {};       // 左孩子编号（-1表示空）
//    int rightval[10200] = {};      // 右孩子编号（-1表示空）
//    bool ischild[10200] = { false };// 标记是否为子节点（用于找根）
//
//    // 初始化节点及父子关系
//    for (int i = 0; i < n; i++)
//    {
//        char m, n[10], o[10];
//        cin >> m >> n >> o;
//        node* newnode = (node*)malloc(sizeof(node));
//        newnode->c = m;
//        newnode->left = newnode->right = NULL;
//        leftval[i] = strcmp(n, "-") == 0 ? -1 : atoi(n);
//        rightval[i] = strcmp(o, "-") == 0 ? -1 : atoi(o);
//        if (leftval[i] != -1) ischild[leftval[i]] = true;
//        if (rightval[i] != -1) ischild[rightval[i]] = true;
//        nodes[i] = newnode;
//    }
//
//    // 建立左右子树关联
//    for (int i = 0; i < n; i++)
//    {
//        if (leftval[i] != -1) nodes[i]->left = nodes[leftval[i]];
//        if (rightval[i] != -1) nodes[i]->right = nodes[rightval[i]];
//    }
//
//    // 查找根节点（非子节点的节点）
//    for (int i = 0; i < n; i++)
//        if (!ischild[i]) return nodes[i];
//    return NULL;
//}
//
///**
// * @brief 递归计算树的深度（根节点深度为1）
// * @param root 二叉树根节点
// * @return int 树的深度（空树返回0）
// */
//int getdepth(node* root)
//{
//    if (!root) return 0;
//    int leftD = getdepth(root->left);
//    int rightD = getdepth(root->right);
//    return 1 + (leftD > rightD ? leftD : rightD);
//}
//
///**
// * @brief 判断两棵树是否同构
// * @param r1 树1的根节点，r2 树2的根节点
// * @return bool 同构返回true，否则返回false
// * 核心逻辑：两种情况满足其一即同构：①左右子树均同构；②左右子树互换后同构
// */
//bool isisomorphic(node* r1, node* r2)
//{
//    if (!r1 && !r2) return true;    // 均为空树
//    if (!r1 || !r2) return false;   // 一为空一不为空
//    if (r1->c != r2->c) return false;// 节点字符不同
//    // 两种同构情况：不交换左右子树 或 交换左右子树
//    return (isisomorphic(r1->left, r2->left) && isisomorphic(r1->right, r2->right))
//        || (isisomorphic(r1->left, r2->right) && isisomorphic(r1->right, r2->left));
//}
//int main()
//{
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//
//	int n1, n2;
//	node* r1 = tree(n1);
//	node* r2 = tree(n2);
//
//	if (n1 != n2)
//		cout << "No\n";
//	else
//		cout << (isisomorphic(r1, r2) ? "Yes\n" : "No\n");
//
//	cout << getdepth(r1) << '\n';
//	cout << getdepth(r2) << '\n';
//
//	return 0;
//}