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
//				p->next->no = temp;
//                char tempname[20];
//                strcpy(tempname, p->name);
//                strcpy(p->name, p->next->name);
//                strcpy(p->next->name, tempname);
//                int tempscore = p->score;
//                p->score = p->next->score;
//				p->next->score = tempscore;
//            }
//            p = p->next;
//        }
//    }
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
//int main()
//{
//    const char* filename = "C:\\Users\\LENOVO\\Desktop\\student.txt";
//    student* head = read(filename);
//    sortlist(head);
//    printresult(head);
//    deletelist(head);
//}