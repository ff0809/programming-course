//#include<iostream>
//using namespace std;
//
//class student
//{
//private:
//	string name;
//	int no;
//	int cscore;
//	int mscore;
//	int escore;
//public:
//	student(string mname, int mno, int mcscore, int mmsore, int mescore)
//	{
//		name = mname;
//		no = mno;
//		cscore = mcscore;
//		mscore = mmsore;
//		escore = mescore;
//	}
//
//	void printscore()
//	{
//		cout << "==学生信息==" << endl;
//		cout << "姓名：" << name << endl;
//		cout << "学号：" << no << endl;
//		cout << "====成绩====" << endl;
//		cout << "语文成绩：" << cscore << endl;
//		cout << "高数成绩：" << mscore << endl;
//		cout << "英语成绩：" << escore << endl;
//		cout << "平均成绩：" << double((cscore + mscore + escore)) / 3 << endl;
//		cout << endl;
//	}
//};
//
//int main()
//{
//	int m;
//	cout << "请输入学生个数：" << endl;
//	cin >> m;
//	for (int i = 0; i < m; i++)
//	{
//		string name;
//		cin >> name;
//		int no, cs, ms, es;
//		cin >> no >> cs >> ms >> es;
//		class student stu(name, no, cs, ms, es);
//		stu.printscore();
//	}
//}