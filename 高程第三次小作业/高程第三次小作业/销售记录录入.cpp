//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//#include<cstring>
//#include<iomanip>
//using namespace std;
//
//class Book_Sale
//{
//private:
//    char* isbn; // 指向书籍编号的指针
//    // 存放书籍编号的空间需动态申请
//    // 书籍编号由 5 段 13 位数字组成，如 978-7-121-15535-2
//    int    sales_volume;   // 销售量
//    double original_price; // 原始价格
//    double real_price;     // 实售价格
//    double discount;       // 折扣
//    double gross_sales;    // 销售总额
//
//public:
//    Book_Sale(istream&);
//    Book_Sale() {};
//    ~Book_Sale();
//    void set(char*isbn,int volume,double oriprice,double dis);
//    void compute();
//	void display();
//    const char cal();
//};
//
//Book_Sale::Book_Sale(istream& in)
//{
//    char temp[20] = {};
//    char num[6] = {};
//    in >> num;
//    strcpy(temp, "978-7-121-");
//	strcat(temp, num);
//	strcat(temp, "-");
//    isbn = new char[20];
//    strcpy(isbn, temp);
//	char checkdigit[2] = {cal(),'\0'};
//	strcat(isbn, checkdigit);
//	in >> sales_volume >> original_price >> discount;
//}
//
//Book_Sale::~Book_Sale()
//{
//    delete[]isbn;
//}
//
//const char Book_Sale::cal()
//{
//    int result=0, mid;
//    int count = 0;
//    for (int i = 0; i < 15; i++)
//    {
//        if (isbn[i] != '-')
//        {
//            mid = isbn[i] - '0';
//            if (count % 2 == 0)
//            {
//                result += mid;
//            }
//            else
//            {
//                result += mid * 3;
//            }
//            count++;
//		}
//    }
//	result = 10 - (result % 10);
//	return (result == 10 ? '0' : (char)(result + '0'));
//}
//
//void Book_Sale::set(char* num, int volume, double oriprice, double dis)
//{
//    char temp[20] = {};
//    strcpy(temp, "978-7-121-");
//    strcat(temp, num);
//    strcat(temp, "-");
//    isbn = new char[20];
//    strcpy(isbn, temp);
//    char checkdigit[2] = { cal(),'\0' };
//    strcat(isbn, checkdigit);
//	sales_volume = volume;
//	original_price = oriprice;
//	discount = dis;
//}
//
//void Book_Sale::compute()
//{
//    real_price = original_price * discount;
//    gross_sales = (long long)(real_price * sales_volume*1000)/1000.0;
//	real_price = (long long)(real_price * 1000) / 1000.0;
//	original_price = (long long)(original_price * 1000) / 1000.0;
//	discount = (int)(discount * 1000) / 1000.0;
//}
//
//void Book_Sale::display()
//{
//	cout << "该书的ISBN号为:" << isbn << endl;
//    cout << fixed << setprecision(3);
//	cout << "销量为:" << sales_volume << "本 原价为:" << original_price << "元 折扣为:" << discount << " 现价为:" << real_price << "元 总销售额为:" << gross_sales << "元" << endl;
//}
//
//int main()
//{
//    Book_Sale bs1(cin);
//	bs1.compute();
//	bs1.display();
//    while(true)
//    {
//		Book_Sale bs2;
//		char num[6];
//        int    sales_volume;   
//        double original_price; 
//        double discount;
//        cin >> num;
//		if (strcmp(num, "-1") == 0)break;
//		cin >> sales_volume >> original_price >> discount;
//		bs2.set(num,sales_volume,original_price,discount);
//		bs2.compute();
//		bs2.display();
//    }
//    return 0;
//}