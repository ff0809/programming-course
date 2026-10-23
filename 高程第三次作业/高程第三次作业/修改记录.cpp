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
//void printresult(student* head)
//{
//    student* p = head;
//    while (p)
//    {
//        cout << "学号:" << p->no << " 姓名:" << p->name << " 成绩:" << p->score << endl;
//        p = p->next;
//    }
//}
//
//student* searchbyID(student* head, int no)
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
//void deletelist(student* head)
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
//bool isContinue()
//{
//    char tmp;
//    cin >> tmp;
//    if (tmp == 'Y' || tmp == 'y')
//    {
//        return true;
//    }
//    return false;
//}
//
//int main()
//{
//    const char* filename = "C:\\Users\\LENOVO\\Desktop\\student.txt";
//    student* head = read(filename);
//    while (1)
//    {
//        int query;
//        cin >> query;
//        student* person = searchbyID(head, query);
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
//            printresult(head);
//            break;
//        }
//    }
//    deletelist(head);
//}