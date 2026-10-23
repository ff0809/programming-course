//#include <iostream>
//#include <cstdlib>
//using namespace std;
//
//// 多项式节点结构体：存储一元多项式的单个项
//typedef struct Node
//{
//    int coef;          // 项的系数
//    int exp;           // 项的指数
//    Node* next;        // 指向下一个项的指针：维护多项式“指数递增”的有序结构
//} Node, * Poly;        // Poly为Node*的别名，简化指针类型声明
//
///**
// * @brief 创建多项式（核心：哨兵节点+尾插法，确保多项式按指数递增存储）
// * 设计思路：用哨兵节点（head）避免空表判断，尾指针（tail）优化插入效率（O(1)尾插）
// * @return Poly 多项式的哨兵头节点（head->next指向第一个有效项）
// */
//Poly createPoly()
//{
//    // 1. 创建哨兵头节点（无实际项，仅用于简化插入/删除操作）
//    Poly head = (Node*)malloc(sizeof(Node));
//    head->next = NULL;  // 初始无有效项
//    Node* tail = head;  // 尾指针：始终指向最后一个有效项，避免遍历找尾
//
//    // 2. 核心：尾插法添加多项式项（确保输入的项按指数递增存储）
//    int n; cin >> n;  // n为多项式项数
//    for (int i = 0; i < n; i++)
//    {
//        Node* newNode = (Node*)malloc(sizeof(Node));
//        cin >> newNode->coef >> newNode->exp;  // 输入当前项的系数和指数
//        newNode->next = NULL;  // 新节点默认无后继
//        tail->next = newNode;  // 尾插：当前最后一项指向新节点
//        tail = newNode;        // 尾指针后移，保持指向最后一项
//    }
//    return head;  // 返回哨兵头节点（外部通过head->next访问有效项）
//}
//
//// 多项式加法（O(m + n)时间复杂度，利用有序性一次遍历完成）
//Poly polyAdd(Poly a, Poly b) 
//{
//    Poly result = (Node*)malloc(sizeof(Node));
//    result->next = NULL;
//    Node* rear = result;
//    Node* p = a->next;
//    Node* q = b->next;
//
//    while (p && q) 
//    {
//        if (p->exp < q->exp) 
//        {
//            Node* newnode = (Node*)malloc(sizeof(Node));
//            newnode->coef = p->coef;
//            newnode->exp = p->exp;
//            newnode->next = NULL;
//            rear->next = newnode;
//            rear = newnode;
//            p = p->next;
//        }
//        else if (p->exp > q->exp) 
//        {
//            Node* newnode = (Node*)malloc(sizeof(Node));
//            newnode->coef = q->coef;
//            newnode->exp = q->exp;
//            newnode->next = NULL;
//            rear->next = newnode;
//            rear = newnode;
//            q = q->next;
//        }
//        else 
//        {
//            int sumCoef = p->coef + q->coef;
//            if (sumCoef != 0) 
//            { 
//                Node* newnode = (Node*)malloc(sizeof(Node));
//                newnode->coef = sumCoef;
//                newnode->exp = p->exp;
//                newnode->next = NULL;
//                rear->next = newnode;
//                rear = newnode;
//            }
//            p = p->next;
//            q = q->next;
//        }
//    }
//    while (p) 
//    {
//        Node* newnode = (Node*)malloc(sizeof(Node));
//        newnode->coef = p->coef;
//        newnode->exp = p->exp;
//        newnode->next = NULL;
//        rear->next = newnode;
//        rear = newnode;
//        p = p->next;
//    }
//    while (q) 
//    {
//        Node* newnode = (Node*)malloc(sizeof(Node));
//        newnode->coef = q->coef;
//        newnode->exp = q->exp;
//        newnode->next = NULL;
//        rear->next = newnode;
//        rear = newnode;
//        q = q->next;
//    }
//    return result;
//}
//
//// 多项式乘法（利用有序性减少遍历次数，接近O(m*n)时间复杂度）
//Poly polyMulti(Poly a, Poly b) 
//{
//    Poly result = (Node*)malloc(sizeof(Node));
//    result->next = NULL;
//    Node* p = a->next; 
//
//    while (p) 
//    {
//        Node* q = b->next;  
//        Node* last = result;  // 记录当前p对应的插入起始位置（利用q的有序性优化）
//
//        while (q) 
//        {
//            int newCoef = p->coef * q->coef;
//            int newExp = p->exp + q->exp;
//
//            // 从last开始查找插入位置（因q递增，newExp递增，last无需回退）
//            Node* r = last;
//            while (r->next && r->next->exp < newExp) 
//            {
//                r = r->next;
//            }
//            last = r;  // 更新下次查找的起始位置
//
//            if (r->next && r->next->exp == newExp) 
//            {
//                r->next->coef += newCoef;
//                if (r->next->coef == 0) 
//                {
//                    Node* temp = r->next;
//                    r->next = temp->next;
//                    free(temp);
//                }
//            }
//            else 
//            {
//                Node* newNode = (Node*)malloc(sizeof(Node));
//                newNode->coef = newCoef;
//                newNode->exp = newExp;
//                newNode->next = r->next;
//                r->next = newNode;
//            }
//            q = q->next;
//        }
//        p = p->next;
//    }
//    return result;
//}
//
//void printPoly(Poly poly) 
//{
//    Node* p = poly->next;
//    bool hasOutput = false;
//    while (p) 
//    {
//        if (p->coef != 0) 
//        {
//            if (hasOutput) 
//            {
//                cout << " "; 
//            }
//            cout << p->coef << " " << p->exp;
//            hasOutput = true;
//        }
//        p = p->next;
//    }
//    if (hasOutput) 
//    {
//        cout << endl; 
//    }
//}
//
//int main() 
//{
//    Poly a = createPoly();
//    Poly b = createPoly();
//    int op;
//    cin >> op;
//
//    if (op == 0 || op == 2) 
//    {
//        Poly sum = polyAdd(a, b);
//        printPoly(sum);
//    }
//    if (op == 1 || op == 2) 
//    {
//        Poly product = polyMulti(a, b);
//        printPoly(product);
//    }
//    return 0;
//}