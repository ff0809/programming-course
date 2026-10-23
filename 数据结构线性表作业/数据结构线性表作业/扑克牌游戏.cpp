//#include<iostream>
//#include<string>
//using namespace std;
//
//typedef struct node
//{
//    string suit;  // 仍用string，方便操作
//    string rank;
//    struct node* next;
//}node, * linklist;
//
//node* head = NULL;  // 保留全局头尾指针，简化操作
//node* tail = NULL;
//
//// 用new创建节点，自动调用string构造函数
//node* createnode(string suit, string rank)
//{
//    node* p = new node;  // new会自动初始化成员（包括string）
//    p->suit = suit;
//    p->rank = rank;
//    p->next = NULL;
//    return p;
//}
//
//void appendlist(linklist& l, string suit, string rank)
//{
//    node* p = createnode(suit, rank);
//    if (head == NULL)
//    {
//        head = p;
//        tail = p;
//    }
//    else
//    {
//        tail->next = p;
//        tail = p;
//    }
//    l = head;
//}
//
//void appendnewlist(node*& nhead, node*& ntail, string suit, string rank)
//{
//    node* p = createnode(suit, rank);
//    if (nhead == NULL)
//    {
//        nhead = p;
//        ntail = p;
//    }
//    else
//    {
//        ntail->next = p;
//        ntail = p;
//    }
//}
//
//// 直接用string比较，无需strcmp
//int getvalue(string s)
//{
//    if (s == "A") return 1;
//    else if (s == "J") return 11;
//    else if (s == "Q") return 12;
//    else if (s == "K") return 13;
//    else
//    {
//        return stoi(s);
//    }
//}
//
//int getlength(linklist l)
//{
//    node* p = l;
//    int length = 0;
//    while (p)
//    {
//        p = p->next;
//        length++;
//    }
//    return length;
//}
//
//void extractlist(linklist& l, string suit)
//{
//    if (l == NULL) return;
//    linklist l2 = NULL;
//    node* ntail = NULL;
//    node* prev = NULL;
//    node* p = l;
//    while (p)
//    {
//        if (p->suit == suit)  // 直接用==比较string，简洁
//        {
//            appendnewlist(l2, ntail, p->suit, p->rank);
//            // 从原链表移除节点
//            if (prev == NULL)
//            {
//                l = p->next;
//                if (l == NULL) tail = NULL;
//            }
//            else
//            {
//                prev->next = p->next;
//                if (p == tail) tail = prev;
//            }
//            // 用delete释放节点，自动调用string析构
//            node* temp = p;
//            p = p->next;
//            delete temp;  // 关键：delete会先析构string，再释放内存
//        }
//        else
//        {
//            prev = p;
//            p = p->next;
//        }
//    }
//    // 排序（直接用string赋值，无需strcpy）
//    for (int i = 0; i < getlength(l2); i++)
//    {
//        node* q = l2;
//        for (int j = 0; j < getlength(l2) - i - 1; j++)
//        {
//            if (q->next == NULL) break;
//            if (getvalue(q->rank) > getvalue(q->next->rank))
//            {
//                // 直接交换string，无需字符数组操作
//                swap(q->rank, q->next->rank);
//            }
//            q = q->next;
//        }
//    }
//    if (l2)
//    {
//        ntail->next = l;
//        l = l2;
//        head = l2;
//    }
//    // 更新尾指针
//    tail = l;
//    while (tail && tail->next != NULL)
//    {
//        tail = tail->next;
//    }
//}
//
//void revertlist(linklist& l)
//{
//    node* prev = NULL;
//    node* cur = head;
//    node* next = NULL;
//    while (cur)
//    {
//        next = cur->next;
//        cur->next = prev;
//        prev = cur;
//        cur = next;
//    }
//    swap(head, tail);  // 直接交换头尾指针
//    l = head;
//}
//
//void poplist(linklist& l)
//{
//    if (head == NULL)
//    {
//        cout << "NULL" << endl;
//        return;
//    }
//    node* temp = head;
//    head = head->next;
//    l = head;
//    cout << temp->suit << " " << temp->rank << endl;
//    if (head == NULL)
//    {
//        tail = NULL;
//    }
//    delete temp;  // 自动析构string
//}
//
//int main()
//{
//    linklist l = NULL;
//    int line;
//    cin >> line;
//    for (int i = 0; i < line; i++)
//    {
//        string order;
//        cin >> order;
//        if (order == "Append")
//        {
//            string suit, rank;
//            cin >> suit >> rank;
//            appendlist(l, suit, rank);
//        }
//        else if (order == "Extract")
//        {
//            string suit;
//            cin >> suit;
//            extractlist(l, suit);
//        }
//        else if (order == "Revert")
//        {
//            revertlist(l);
//        }
//        else if (order == "Pop")
//        {
//            poplist(l);
//        }
//    }
//    node* p = l;
//    if (p == NULL)
//    {
//        cout << "NULL" << endl;
//    }
//    while (p)
//    {
//        cout << p->suit << " " << p->rank << endl;
//        p = p->next;
//    }
//    return 0;
//}