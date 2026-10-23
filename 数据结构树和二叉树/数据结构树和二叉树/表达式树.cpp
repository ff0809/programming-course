#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
using namespace std;

typedef struct Node {
    char data;           // 变量或运算符
    struct Node* left;   // 左子树
    struct Node* right;  // 右子树
    int depth;           // 节点深度（可视化用）
    int x;               // 节点横坐标（可视化用）
} Node;

typedef struct VarMap {
    char c;
    int val;
} VarMap;

typedef struct DepthNodes {
    Node* nodes[50];  
    int count;
} DepthNodes;

Node* createNode(char c) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = c;
    node->left = NULL;
    node->right = NULL;
    node->depth = 0;
    node->x = 0;
    return node;
}

// 运算符优先级：*、/为2，+、-为1，其他0
int getPriority(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// 中缀转逆波兰式（用char数组存储结果）
void infixToPostfix(const char* infix, char* postfix) {
    stack<char> opStack;
    int len = strlen(infix);
    int pos = 0;  // 逆波兰式当前位置

    for (int i = 0; i < len; i++) {
        char c = infix[i];
        if (c >= 'a' && c <= 'z') {  // 变量直接加入
            postfix[pos++] = c;
        }
        else if (c == '(') {       // 左括号入栈
            opStack.push(c);
        }
        else if (c == ')') {       // 右括号：弹出到左括号
            while (!opStack.empty() && opStack.top() != '(') {
                postfix[pos++] = opStack.top();
                opStack.pop();
            }
            opStack.pop();  // 弹出左括号
        }
        else {                     // 运算符：按优先级处理
            while (!opStack.empty() && opStack.top() != '('
                && getPriority(opStack.top()) >= getPriority(c)) {
                postfix[pos++] = opStack.top();
                opStack.pop();
            }
            opStack.push(c);
        }
    }

    // 弹出剩余运算符
    while (!opStack.empty()) {
        postfix[pos++] = opStack.top();
        opStack.pop();
    }
    postfix[pos] = '\0';  // 字符串结束符
}

// 逆波兰式构建表达式树
Node* buildTree(const char* postfix) {
    stack<Node*> nodeStack;
    int len = strlen(postfix);

    for (int i = 0; i < len; i++) {
        char c = postfix[i];
        if (c >= 'a' && c <= 'z') {  // 变量：叶子节点
            Node* leaf = createNode(c);
            nodeStack.push(leaf);
        }
        else {                      // 运算符：父节点（连接左右子树）
            Node* parent = createNode(c);
            parent->right = nodeStack.top();  // 先弹右子树
            nodeStack.pop();
            parent->left = nodeStack.top();   // 再弹左子树
            nodeStack.pop();
            nodeStack.push(parent);
        }
    }

    return nodeStack.empty() ? NULL : nodeStack.top();
}

// 计算树的高度（递归）
int getTreeHeight(Node* root) {
    if (root == NULL) return 0;
    int leftH = getTreeHeight(root->left);
    int rightH = getTreeHeight(root->right);
    return 1 + (leftH > rightH ? leftH : rightH);
}

// 交换两个Node*指针（排序用）
void swapNode(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

// 对某一深度的节点按x坐标升序排序（选择排序，替代sort）
void sortNodes(DepthNodes* depthNodes) {
    for (int i = 0; i < depthNodes->count - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < depthNodes->count; j++) {
            if (depthNodes->nodes[j]->x < depthNodes->nodes[minIdx]->x) {
                minIdx = j;
            }
        }
        swapNode(&depthNodes->nodes[i], &depthNodes->nodes[minIdx]);
    }
}

// 层次遍历获取所有节点的深度和坐标（可视化用）
void getNodePositions(Node* root, int height, DepthNodes* depthMap) {
    if (root == NULL) return;

    // 初始化深度映射数组（清空所有节点）
    for (int i = 0; i <= height; i++) {
        depthMap[i].count = 0;
    }

    Node* q[100];
    int front = 0, rear = 0;

    root->depth = 1;
    root->x = (1 << (height - 1));  // 根节点横坐标：2^(height-1)
    q[rear++] = root;
    depthMap[1].nodes[depthMap[1].count++] = root;

    while (front < rear) {
        Node* cur = q[front++];
        int curDepth = cur->depth;
        int curX = cur->x;

        // 左子树坐标：父x - 2^(height - curDepth - 1)
        if (cur->left != NULL) {
            cur->left->depth = curDepth + 1;
            cur->left->x = curX - (1 << (height - curDepth - 1));
            q[rear++] = cur->left;
            depthMap[curDepth + 1].nodes[depthMap[curDepth + 1].count++] = cur->left;
        }

        // 右子树坐标：父x + 2^(height - curDepth - 1)
        if (cur->right != NULL) {
            cur->right->depth = curDepth + 1;
            cur->right->x = curX + (1 << (height - curDepth - 1));
            q[rear++] = cur->right;
            depthMap[curDepth + 1].nodes[depthMap[curDepth + 1].count++] = cur->right;
        }
    }

    // 对每个深度的节点按x坐标排序
    for (int i = 1; i <= height; i++) {
        sortNodes(&depthMap[i]);
    }
}

// 可视化表达式树
void printTree(Node* root) {
    if (root == NULL) return;

    int height = getTreeHeight(root);
    int totalLines = 2 * height - 1;  // 总输出行数
    DepthNodes depthMap[50];  // 存储每个深度的节点（深度最大50）
    getNodePositions(root, height, depthMap);

    for (int line = 1; line <= totalLines; line++) {
        if (line % 2 == 1) {  // 奇数行：输出节点
            int depth = (line + 1) / 2;
            DepthNodes* nodes = &depthMap[depth];
            if (nodes->count == 0) {
                printf("\n");
                continue;
            }

            // 计算最大x坐标，确定行长度
            int maxX = 0;
            for (int i = 0; i < nodes->count; i++) {
                if (nodes->nodes[i]->x > maxX) {
                    maxX = nodes->nodes[i]->x;
                }
            }

            // 初始化行（全空格）
            char* lineStr = (char*)malloc(maxX + 1);
            memset(lineStr, ' ', maxX);
            lineStr[maxX] = '\0';

            // 填充节点
            for (int i = 0; i < nodes->count; i++) {
                int x = nodes->nodes[i]->x;
                if (x <= maxX) {
                    lineStr[x - 1] = nodes->nodes[i]->data;  // x从1开始，索引-1
                }
            }

            // 去除行末空格
            int last = maxX - 1;
            while (last >= 0 && lineStr[last] == ' ') last--;
            if (last >= 0) lineStr[last + 1] = '\0';
            printf("%s\n", lineStr);
            free(lineStr);
        }
        else {  // 偶数行：输出连接线 
            int depth = line / 2;
            DepthNodes* parentNodes = &depthMap[depth];
            if (parentNodes->count == 0) {
                printf("\n");
                continue;
            }

            // 计算最大连接线位置
            int maxX = 0;
            for (int i = 0; i < parentNodes->count; i++) {
                Node* p = parentNodes->nodes[i];
                if (p->left != NULL && p->x - 1 > maxX) {
                    maxX = p->x - 1;  // /的位置：父x-1
                }
                if (p->right != NULL && p->x + 1 > maxX) {
                    maxX = p->x + 1;  // \的位置：父x+1
                }
            }

            // 初始化行（全空格）
            char* lineStr = (char*)malloc(maxX + 1);
            memset(lineStr, ' ', maxX);
            lineStr[maxX] = '\0';

            // 填充连接线
            for (int i = 0; i < parentNodes->count; i++) {
                Node* p = parentNodes->nodes[i];
                if (p->left != NULL) {  // 左子树连接线 /
                    int pos = p->x - 1;
                    if (pos <= maxX) {
                        lineStr[pos - 1] = '/';  // pos从1开始，索引-1
                    }
                }
                if (p->right != NULL) {  // 右子树连接线 
                    int pos = p->x + 1;
                    if (pos <= maxX) {
                        lineStr[pos - 1] = '\\';  // 转义字符
                    }
                }
            }

            // 去除行末空格
            int last = maxX - 1;
            while (last >= 0 && lineStr[last] == ' ') last--;
            if (last >= 0) lineStr[last + 1] = '\0';
            printf("%s\n", lineStr);
            free(lineStr);
        }
    }
}

int getVarValue(VarMap* vars, int n, char c) {
    for (int i = 0; i < n; i++) {
        if (vars[i].c == c) {
            return vars[i].val;
        }
    }
    return 0;
}

// 计算表达式结果（后缀表达式求值）
int calculate(const char* postfix, VarMap* vars, int n) {
    stack<int> valStack;
    int len = strlen(postfix);

    for (int i = 0; i < len; i++) {
        char c = postfix[i];
        if (c >= 'a' && c <= 'z') {  // 变量：取对应值
            valStack.push(getVarValue(vars, n, c));
        }
        else {                      // 运算符：计算
            int right = valStack.top(); valStack.pop();
            int left = valStack.top(); valStack.pop();
            int res;
            switch (c) {
            case '+': res = left + right; break;
            case '-': res = left - right; break;
            case '*': res = left * right; break;
            case '/': res = left / right; break;
            default: res = 0;
            }
            valStack.push(res);
        }
    }

    return valStack.top();
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    char infix[51];
    char postfix[101];
    int n;
    VarMap vars[10];

    cin >> infix;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> vars[i].c >> vars[i].val;
    }

    // 1. 输出逆波兰式
    infixToPostfix(infix, postfix);
    cout << postfix << endl;

    // 2. 构建表达式树并输出
    Node* root = buildTree(postfix);
    printTree(root);

    // 3. 输出计算结果
    int result = calculate(postfix, vars, n);
    cout << result << endl;

    freeTree(root);
    return 0;
}

/**
 * @brief 中缀表达式转逆波兰式，处理运算符优先级和括号
 * @param infix 中缀表达式，postfix 输出的逆波兰式
 */
void infixToPostfix(const char* infix, char* postfix)
{
    stack<char> opStack;
    int len = strlen(infix), pos = 0;
    for (int i = 0; i < len; i++)
    {
        char c = infix[i];
        if (c >= 'a' && c <= 'z') postfix[pos++] = c; // 变量直接加入
        else if (c == '(') opStack.push(c); // 左括号入栈
        else if (c == ')') // 右括号：弹出到左括号
        {
            while (!opStack.empty() && opStack.top() != '(')
            {
                postfix[pos++] = opStack.top();
                opStack.pop();
            }
            opStack.pop(); // 弹出左括号
        }
        else // 运算符：按优先级处理
        {
            while (!opStack.empty() && opStack.top() != '(' && getPriority(opStack.top()) >= getPriority(c))
            {
                postfix[pos++] = opStack.top();
                opStack.pop();
            }
            opStack.push(c);
        }
    }
    // 弹出剩余运算符
    while (!opStack.empty())
    {
        postfix[pos++] = opStack.top();
        opStack.pop();
    }
    postfix[pos] = '\0';
}

// 运算符优先级：*、/为2，+、-为1，其他为0
int getPriority(char op) { return (op == '*' || op == '/') ? 2 : (op == '+' || op == '-') ? 1 : 0; }

Node* buildTree(const char* postfix)
{
    stack<Node*> nodeStack;
    int len = strlen(postfix);
    for (int i = 0; i < len; i++)
    {
        char c = postfix[i];
        if (c >= 'a' && c <= 'z') // 变量：叶子节点
            nodeStack.push(createNode(c));
        else // 运算符：父节点（右子树先弹，左子树后弹）
        {
            Node* parent = createNode(c);
            parent->right = nodeStack.top(); nodeStack.pop();
            parent->left = nodeStack.top(); nodeStack.pop();
            nodeStack.push(parent);
        }
    }
    return nodeStack.empty() ? NULL : nodeStack.top();
}

// 创建节点
Node* createNode(char c)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = c;
    node->left = node->right = NULL;
    node->depth = 0;
    node->x = 0;
    return node;
}

/**
 * @brief 可视化表达式树，奇数行输出节点，偶数行输出连接线
 * @param root 表达式树根节点
 */
void printTree(Node* root)
{
    if (!root) return;
    int height = getTreeHeight(root);
    int totalLines = 2 * height - 1;
    DepthNodes depthMap[50];
    getNodePositions(root, height, depthMap); // 获取节点深度和横坐标

    for (int line = 1; line <= totalLines; line++)
    {
        if (line % 2 == 1) // 奇数行：输出节点
        {
            int depth = (line + 1) / 2;
            DepthNodes* nodes = &depthMap[depth];
            if (nodes->count == 0) { printf("\n"); continue; }
            // 构建节点行，去除行末空格
            int maxX = nodes->nodes[nodes->count - 1]->x;
            char* lineStr = (char*)malloc(maxX + 1);
            memset(lineStr, ' ', maxX);
            for (int i = 0; i < nodes->count; i++)
                lineStr[nodes->nodes[i]->x - 1] = nodes->nodes[i]->data;
            int last = maxX - 1;
            while (last >= 0 && lineStr[last] == ' ') last--;
            if (last >= 0) lineStr[last + 1] = '\0';
            printf("%s\n", lineStr);
            free(lineStr);
        }
        else // 偶数行：输出连接线
        {
            int depth = line / 2;
            DepthNodes* parentNodes = &depthMap[depth];
            if (parentNodes->count == 0) { printf("\n"); continue; }
            int maxX = 0;
            for (int i = 0; i < parentNodes->count; i++)
            {
                Node* p = parentNodes->nodes[i];
                if (p->left) maxX = max(maxX, p->x - 1);
                if (p->right) maxX = max(maxX, p->x + 1);
            }
            char* lineStr = (char*)malloc(maxX + 1);
            memset(lineStr, ' ', maxX);
            for (int i = 0; i < parentNodes->count; i++)
            {
                Node* p = parentNodes->nodes[i];
                if (p->left) lineStr[p->x - 2] = '/'; // 左子树连接线
                if (p->right) lineStr[p->x] = '\\'; // 右子树连接线
            }
            int last = maxX - 1;
            while (last >= 0 && lineStr[last] == ' ') last--;
            if (last >= 0) lineStr[last + 1] = '\0';
            printf("%s\n", lineStr);
            free(lineStr);
        }
    }
}

// 计算树的高度
int getTreeHeight(Node* root)
{
    if (!root) return 0;
    int leftH = getTreeHeight(root->left);
    int rightH = getTreeHeight(root->right);
    return 1 + max(leftH, rightH);
}

/**
 * @brief 代入变量值，计算逆波兰式结果（除法为整除）
 * @param postfix 逆波兰式，vars 变量映射数组，n 变量数
 * @return int 计算结果
 */
int calculate(const char* postfix, VarMap* vars, int n)
{
    stack<int> valStack;
    int len = strlen(postfix);
    for (int i = 0; i < len; i++)
    {
        char c = postfix[i];
        if (c >= 'a' && c <= 'z') // 变量：压入对应值
        {
            for (int j = 0; j < n; j++)
                if (vars[j].c == c)
                {
                    valStack.push(vars[j].val);
                    break;
                }
        }
        else // 运算符：计算并压入结果
        {
            int right = valStack.top(); valStack.pop();
            int left = valStack.top(); valStack.pop();
            switch (c)
            {
            case '+': valStack.push(left + right); break;
            case '-': valStack.push(left - right); break;
            case '*': valStack.push(left * right); break;
            case '/': valStack.push(left / right); break;
            default: valStack.push(0);
            }
        }
    }
    return valStack.top();
}