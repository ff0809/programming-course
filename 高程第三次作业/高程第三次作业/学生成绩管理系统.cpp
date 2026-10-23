//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//#include<cstring>
//#include<fstream>
//using namespace std;
//
//struct student {
//    int no;                // 学号
//    char name[20];         // 姓名
//    int score;             // 成绩
//    struct student* next;  // 下一结点
//    /*! 不允许修改上述结构 !*/
//};
//
//student* read(const char* filename)
//{
//    ifstream in;
//    in.open(filename, ios::in);
//    if (in.is_open() == 0)
//    {
//        cout << "文件打开失败！" << endl;
//        exit(0);
//    }
//    int num;
//    int no;
//    char name[20];
//    int score;
//    student* head = NULL;
//    student* rear = NULL;
//    in >> num;
//    while (in >> no >> name >> score)
//    {
//        student* newnode = new(nothrow)student;
//        if (!newnode)return NULL;
//        strcpy(newnode->name, name);
//        newnode->no = no;
//        newnode->score = score;
//        newnode->next = NULL;
//        if (head == NULL)
//        {
//            head = rear = newnode;
//        }
//        else
//        {
//            rear->next = newnode;
//            rear = newnode;
//        }
//    }
//    in.close();
//    return head;
//}
//
//int getlength(student* head)
//{
//    student* p = head;
//    int count = 0;
//    while (p)
//    {
//        p = p->next;
//        count++;
//    }
//    return count;
//}
//
//void count(student* head)
//{
//    int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0;
//    student* p = head;
//    while (p)
//    {
//        if (p->score >= 90)count1++;
//        else if (p->score >= 80 && p->score < 90)count2++;
//        else if (p->score >= 70 && p->score < 80)count3++;
//        else if (p->score >= 60 && p->score < 70)count4++;
//        else count5++;
//        p = p->next;
//    }
//    cout << "统计信息如下：" << "优: " << count1 << "人  良: " << count2 << "人  中: " << count3 << "人  及格: " << count4 << "人  不及格: " << count5 << "人" << endl;
//}
//
//void sort(student* head)
//{
//    for (int i = 0; i < getlength(head); i++)
//    {
//        student* p = head;
//        for (int j = 0; j < getlength(head) - i - 1; j++)
//        {
//            if (p->score<p->next->score || p->score == p->next->score && p->no>p->next->no)
//            {
//                int temp = p->no;
//                p->no = p->next->no;
//                p->next->no = temp;
//                char tempname[20];
//                strcpy(tempname, p->name);
//                strcpy(p->name, p->next->name);
//                strcpy(p->next->name, tempname);
//                int tempscore = p->score;
//                p->score = p->next->score;
//                p->next->score = tempscore;
//            }
//            p = p->next;
//        }
//    }
//}
//
//student* insertlist(student* head, int no, const char* name, int score)
//{
//    student* p = new(nothrow)student;
//    if (!p)return head;
//    p->no = no;
//    p->score = score;
//    strcpy(p->name, name);
//    p->next = NULL;
//    if (!head)head = p;
//    else
//    {
//        p->next = head;
//        head = p;
//    }
//    return head;
//}
//
//void disp(student* head)
//{
//    student* p = head;
//    while (p)
//    {
//        cout << "学号:" << p->no << " 姓名:" << p->name << " 成绩:" << p->score << endl;
//        p = p->next;
//    }
//}
//
//void sortlist(student* head)
//{
//    for (int i = 0; i < getlength(head); i++)
//    {
//        student* p = head;
//        for (int j = 0; j < getlength(head) - i - 1; j++)
//        {
//            if (p->score<p->next->score || p->score == p->next->score && p->no>p->next->no)
//            {
//                int temp = p->no;
//                p->no = p->next->no;
//                p->next->no = temp;
//                char tempname[20];
//                strcpy(tempname, p->name);
//                strcpy(p->name, p->next->name);
//                strcpy(p->next->name, tempname);
//                int tempscore = p->score;
//                p->score = p->next->score;
//                p->next->score = tempscore;
//            }
//            p = p->next;
//        }
//    }
//}
//
//bool isContinue()
//{
//    char tmp;
//    cin >> tmp;
//    if (tmp == 'y' || tmp == 'Y')
//    {
//        return true;
//    }
//    return false;
//}
//
//student* find(student* head, int no)
//{
//    student* p = head;
//    bool flag = false;
//    while (p)
//    {
//        if (p->no == no)
//        {
//            return p;
//        }
//        p = p->next;
//    }
//    return NULL;
//}
//
//void searchbyID(student* head)
//{
//    while (1)
//    {
//        student* p = head;
//        int query;
//        cin >> query;
//        student* person = find(head, query);
//        if (isContinue())
//        {
//            if (person)
//            {
//                cout << "学号:" << person->no << " 姓名:" << person->name << " 成绩:" << person->score << endl;
//            }
//            else
//            {
//                cout << "不存在" << endl;
//            }
//        }
//        else
//        {
//            if (!person)cout << "不存在" << endl;
//            break;
//        }
//    }
//}
//
//void poplist(student*& head, student* p)
//{
//    student* q = head;
//    if (q == p)
//    {
//        head = head->next;
//        delete q;
//    }
//    else
//    {
//        while (q->next != p)
//        {
//            q = q->next;
//        }
//        q->next = p->next;
//        delete p;
//    }
//}
//
//void delbyID(student*&head)
//{
//    while (1)
//    {
//        int query;
//        cin >> query;
//        student* person = find(head, query);
//        if (isContinue())
//        {
//            if (!person)cout << "不存在" << endl;
//            else
//            {
//                poplist(head, person);
//            }
//        }
//        else
//        {
//            if (!person)cout << "不存在" << endl;
//            break;
//        }
//    }
//}
//
//void modibyID(student*&head)
//{
//    while (1)
//    {
//        int query;
//        cin >> query;
//        student* person = find(head, query);
//        if (person)
//        {
//            int newscore;
//            cin >> newscore;
//            person->score = newscore;
//        }
//        if (isContinue())
//        {
//            if (!person)cout << "不存在" << endl;
//        }
//        else
//        {
//            if (!person)cout << "不存在" << endl;
//            break;
//        }
//    }
//}
//
//void addbyID(student*& head)
//{
//    while (1)
//    {
//        int query;
//        cin >> query;
//        student* person = find(head, query);
//        if (person)
//        {
//            cout << "已存在" << endl;
//            if (!isContinue())
//            {
//                sortlist(head);
//                break;
//            }
//        }
//        else
//        {
//            char name[20];
//            cin >> name;
//            int score;
//            cin >> score;
//            head = insertlist(head, query, name, score);
//            sortlist(head);
//            if (!isContinue())
//            {
//                break;
//            }
//        }
//    }
//}
//
//void quit(student* head)
//{
//    student* p = head;
//    while (p)
//    {
//        student* q = p;
//        p = p->next;
//        delete q;
//    }
//}
//
//void menu()
//{
//    int i;
//    cout << endl;
//    for (i = 0; i < 57; i++)
//    {
//        cout << '*';
//    }
//    cout << endl;
//    cout << "*\t1 显示记录\t2 统计记录\t3 排序记录\t*\n";
//    cout << "*\t4 查找记录\t5 删除记录\t6 修改记录\t*\n";
//    cout << "*\t7 添加记录\t0 退出系统\t\t\t*\n";
//    for (i = 0; i < 57; i++)
//    {
//        cout << '*';
//    }
//}
//
//int main()
//{
//    const char* filename = "C:\\Users\\LENOVO\\Desktop\\student.txt";
//    student* head = read(filename);
//    int choice; // 保证输入的为正整数数字
//    char ch;
//    menu();  // 调用菜单显示函数，为防止输出超出限度，请将此项放在循环外部
//
//    while (true) // 注意该循环退出的条件
//    {
//        cout << "选择菜单项(0~7):";
//        cin >> choice;
//        if (choice == 0) // 选择退出
//        {
//            cout << "\n 确定退出吗?(y/n)" << std::endl;
//            cin >> ch;
//            if (ch == 'y' || ch == 'Y')
//            {
//                quit(head);
//                break;
//            }
//            else
//                continue;
//        }
//        switch (choice)
//        {
//        case 1:
//            disp(head); 
//            break;
//        case 2:
//            count(head); 
//            break;
//        case 3:
//            sort(head); 
//            break;
//        case 4:
//            searchbyID(head); 
//            break;
//        case 5:
//            delbyID(head); 
//            break;
//        case 6:
//            modibyID(head); 
//            break;
//        case 7:
//            addbyID(head); 
//            break;
//        default:
//            cout << "\n输入错误，请重新输入" << endl;
//        }
//    }
//    return 0;
//}