//#define _crt_secure_no_warnings
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
//student* find(student*head,int no)
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
//bool iscontinue()
//{
//    char tmp;
//    cin >> tmp;
//    if (tmp == 'y' || tmp == 'y')
//    {
//        return true;
//    }
//    return false;
//}
//
//int main()
//{
//    const char* filename = "c:\\users\\lenovo\\desktop\\student.txt";
//    student* head = read(filename);
//    while (1)
//    {
//        int query;
//        cin >> query;
//        student* person = find(head, query);
//        if (iscontinue())
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
//    deletelist(head);
//}