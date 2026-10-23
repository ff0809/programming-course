//#include<iostream>
//using namespace std;
//
//class student
//{
//public:
//	int num;
//	int score;
//};
//
//int main()
//{
//	student arr[5];
//	for (int i = 0; i < 5; i++)
//	{
//		cout << "请输入第" << i+1 << "个学生的学号和成绩:" << endl;
//		int mnum, mscore;
//		cin >> mnum >> mscore;
//		arr[i].num = mnum;
//		arr[i].score = mscore;
//	}
//	student* p = arr;
//	for (int i = 1; i < 6; i += 2)
//	{
//		cout << "第" << i << "个学生的学号是 " << (*p).num << ", 成绩为 " << (*p).score << endl;
//		p=p+2;
//	}
//	return 0;
//}