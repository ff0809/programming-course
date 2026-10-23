//#include<iostream>
//using namespace std;
//
//class SemesterGrad
//{
//public:
//	int cscore;
//	int mscore;
//	int escore;
//};
//
//class student
//{
//public:
//	string name;
//	int no;
//	SemesterGrad semesterGrad[4];
//	void printinfo()
//	{
//		cout << "==学生信息==" << endl;
//		cout << "姓名：" << name << endl;
//		cout << "学号：" << no << endl;
//		cout << "==学期成绩==" << endl;
//		for (int i = 0; i < 4; i++)
//		{
//			cout << "=学期" << i + 1 << "=" << endl;
//			cout << "语文成绩：" << semesterGrad[i].cscore << endl;
//			cout << "数学成绩：" << semesterGrad[i].mscore << endl;
//			cout << "英语成绩：" << semesterGrad[i].escore << endl;
//			cout << "平均成绩：" << (semesterGrad[i].cscore + semesterGrad[i].mscore + semesterGrad[i].escore) / 3.0 << endl;
//		}
//	}
//};
//
//int main()
//{
//	student stu;
//	cout << "请输入学生的姓名和学号：" << endl;
//	cin >> stu.name >> stu.no;
//	for (int i = 0; i < 4; i++)
//	{
//		cout << "请输入学生第" << i + 1 << "学期的语文，数学，英语成绩：" << endl;
//		cin >> stu.semesterGrad[i].cscore >> stu.semesterGrad[i].mscore >> stu.semesterGrad[i].escore;
//	}
//	stu.printinfo();
//	return 0;
//}