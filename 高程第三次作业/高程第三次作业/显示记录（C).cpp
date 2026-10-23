//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//#include<cstring>
//using namespace std;
//
//struct student {
//    int no;                // 学号
//    char name[10];         // 姓名
//    int score;             // 成绩
//    struct student* next;  // 下一结点
//    /*! 不允许修改上述结构 !*/
//};
//
//student* createnode(int no, const char* name, int score)
//{
//    student* newnode = (student*)malloc(sizeof(student));
//    if (newnode == NULL)
//    {
//        cout << "内存分配失败！" << endl;
//        return NULL;
//    }
//    newnode->no = no;
//    newnode->score = score;
//    strcpy(newnode->name, name);
//    newnode->next = NULL;
//    return newnode;
//}
//
//int main()
//{
//    FILE* fp;
//    if ((fp = fopen("student.txt", "r")) == NULL)
//    {
//        cout << "未找到文件！" << endl;
//        return -1;
//    }
//    cout << "所有的学生信息如下：" << endl;
//    int num;
//    int no;
//    char name[10];
//    int score;
//    num=fscanf(fp, "%d", &num);
//    student* head = NULL;
//    student* rear = NULL;
//    while (fscanf(fp, "%d %9s %d", &no, name, &score) == 3)
//    {
//        student* newnode = createnode(no, name, score);
//        if (newnode == NULL)break;
//        if (head == NULL)head = rear = newnode;
//        else
//        {
//            rear->next = newnode;
//            rear = newnode;
//        }
//    }
//    fclose(fp);
//    student* p = head;
//    while (p != NULL)
//    {
//        cout << "学号:" << p->no << " 姓名:" << p->name << " 成绩:" << p->score << endl;
//        p = p->next;
//    }
//    student* q = head;
//    while (q)
//    {
//        student* r = q;
//        q = q->next;
//        free(r);
//    }
//	return 0;
//}