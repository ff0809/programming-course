//#include <iostream>
//using namespace std;
//
//class Date
//{
//private:
//	int year, month, day;
//
//public:
//	Date(int y, int m, int d);
//	Date(int days); // 从公元元年（0001年）1月1日开始的天数，仅考虑公元元年之后的日期
//
//	// 注意输出格式，格式为"yyyy-mm-dd"，如"2000-01-01"，位数不足的要补0
//	/****************** TODO ******************/
//	friend ostream& operator<<(ostream& os, const Date& d);
//	friend int operator-(const Date& a, const Date& b);
//	operator int()const;
//	int leap(int y)const;
//	int getday(int y, int m)const;
//	void calculate1(int days);
//	int calculate2()const;
//	/**************** TODO-END ****************/
//};
//
///****************** TODO ******************/
//Date::Date(int y, int m, int d)
//{
//	year = y;
//	month = m;
//	day = d;
//}
//Date::Date(int days)
//{
//	calculate1(days);
//}
//ostream& operator<<(ostream& os, const Date& d)
//{
//	int y = d.year;
//	if (y < 1000) os << '0';
//	if (y < 100)  os << '0';
//	if (y < 10)   os << '0';
//	os << y << '-';
//	if (d.month < 10) os << '0';
//	os << d.month << '-';
//	if (d.day < 10) os << '0';
//	os << d.day;
//
//	return os;
//}
//int operator-(const Date& a, const Date& b)
//{
//	return a.calculate2() - b.calculate2();
//}
//Date::operator int()const
//{
//	return calculate2();
//}
//int Date::leap(int y)const
//{
//	if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
//	{
//		return 366;
//	}
//	return 365;
//}
//int Date::getday(int y, int m)const
//{
//	const int day[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
//	if (leap(y)==366)return m == 2 ? 29 : day[m - 1];
//	else return day[m - 1];
//}
//void Date::calculate1(int days)
//{
//	int count = 0, y = 1, m = 1, d = 1;
//	while (true)
//	{
//		if (count + leap(y) < days)
//		{
//			count += leap(y);
//			y++;
//		}
//		else
//		{
//			break;
//		}
//	}
//	while (true)
//	{
//		if (count + getday(y, m) < days)
//		{
//			count += getday(y, m);
//			m++;
//		}
//		else
//		{
//			break;
//		}
//	}
//	d = days - count;
//	year = y;
//	month = m;
//	day = d;
//}
//int Date::calculate2()const
//{
//	int count = 0;
//	for (int i = 1; i < year; i++)
//	{
//		count += leap(i);
//	}
//	for (int i = 1; i < month; i++)
//	{
//		count += getday(year, i);
//	}
//	count += day;
//	return count;
//}
///**************** TODO-END ****************/
//
//int main()
//{
//	// 测试构造函数
//	int year, month, day;
//	cout << "请输入d1年月日：" << endl;
//	cin >> year >> month >> day;
//	Date d1(year, month, day);
//
//	int days;
//	cout << "请输入d2天数：" << endl;
//	cin >> days;
//	Date d2(days);
//
//	cout << "d1日期为：" << endl;
//	cout << d1 << endl;
//	cout << "d2日期为：" << endl;
//	cout << d2 << endl;
//
//	// 测试类型转换运算符重载
//	cout << "d1转换为天数为：" << endl;
//	cout << int(d1) << endl;
//	cout << "d2转换为天数为：" << endl;
//	cout << int(d2) << endl;
//
//	// 测试减法运算符重载
//	cout << "d1和d2相差天数为：" << endl;
//	cout << d1 - d2 << endl;
//
//	return 0;
//}