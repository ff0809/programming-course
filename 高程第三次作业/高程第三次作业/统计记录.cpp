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
//void printresult(student* head)
//{
//    int count1=0, count2=0, count3=0, count4=0, count5=0;
//    student* p = head;
//    while (p)
//    {
//        if (p->score >= 90)count1++;
//        else if(p->score>=80&&p->score<90)count2++;
//        else if(p->score>=70&&p->score<80)count3++;
//        else if(p->score>=60&&p->score<70)count4++;
//		else count5++;
//        p = p->next;
//    }
//	cout << "统计信息如下：" << "优: " << count1 << "人  良: " << count2 << "人  中: " << count3 << "人  及格: " << count4 << "人  不及格: " << count5 << "人" << endl;
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
//    printresult(head);
//    deletelist(head);
//}