//#include<iostream>
//using namespace std;
//
//class dateToDay
//{
//public:
//    dateToDay(int y, int m, int d);
//    dateToDay() {};
//    void setDate(int y,int m,int d);
//    // 合法性检查应该在构建/设置时完成
//    void display();    // 将计算结果输出(即本年内第几天)
//private:
//    bool checkLeap(int y);  // 该函数用于检查闰年
//    bool checkValid(int y,int m,int d); // 该函数用于检查合法
//    int computeDay();  // 该函数用于计算日期
//    int year;
//    int month;
//    int day;
//};
//
//dateToDay::dateToDay(int y, int m, int d)
//{
//    year = y;
//    month = m;
//    day = d;
//    if (!(checkValid(year, month, day)))
//    {
//        cout << "Illegal" << endl;
//        exit(0);
//    }
//}
//
//void dateToDay::setDate(int y,int m,int d)
//{
//    year = y;
//    month = m;
//    day = d;
//    if (!(checkValid(year, month, day)))
//    {
//        cout << "Illegal" << endl;
//        exit(0);
//    }
//}
//
//void dateToDay::display()
//{
//    cout << year << "-" << month << "-" << day << "是" << year << "年的第" << computeDay() << "天" << endl;
//}
//
//bool dateToDay::checkLeap(int year)
//{
//    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
//}
//
//bool dateToDay::checkValid(int year,int month,int day)
//{
//    if (month <= 0 || month > 12 || day <= 0)
//    {
//        return false;
//    }
//    if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
//    {
//        if(day>31)
//        {
//            return false;
//        }
//    }
//    else if(month==4||month==6||month==9||month==11)
//    {
//        if(day>30)
//        {
//            return false;
//        }
//    }
//    else if(month==2)
//    {
//        if(checkLeap(year))
//        {
//            if(day>29)
//            {
//                return false;
//            }
//        }
//        else
//        {
//            if(day>28)
//            {
//                return false;
//            }
//        }
//	}
//    return true;
//}
//
//int dateToDay::computeDay()
//{
//    int total=0;
//    for (int i = 1; i < month; i++)
//    {
//        if (i == 1 || i== 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
//        {
//            total += 31;
//        }
//        else if (i == 4 || i== 6 || i == 9 || i == 11)
//        {
//            total += 30;
//        }
//        else if (i == 2)
//        {
//            if (checkLeap(year))
//            {
//                total += 29;
//            }
//            else
//            {
//                total += 28;
//            }
//        }
//    }
//    total += day;
//    return total;
//}
//
//int main()
//{
//    int y, m, d;
//    cout << "请输入一个日期:" << endl;
//    if (!(cin >> y && cin >> m && cin >> d))
//    {
//        cout << "Illegal" << endl;
//        exit(0);
//    }
//    dateToDay d1(y,m,d);
//    d1.display();
//    cout << "请输入一个日期:" << endl;
//    if (!(cin >> y && cin >> m && cin >> d))
//    {
//        cout << "Illegal" << endl;
//        exit(0);
//    }
//    dateToDay d2;
//    d2.setDate(y, m, d);
//    d2.display();
//    return 0;
//}