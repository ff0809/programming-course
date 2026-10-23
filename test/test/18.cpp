//#include <iostream>  
//using namespace std;
//class A {
//private:
//    char* s;
//public:
//    int a;
//    A()
//    {
//        s = new char[20];
//    }
//    ~A()
//    {
//        cout << "A析构" << endl;
//        delete s;
//    }
//};
//class B :public A {
//public:
//    int b;
//    ~B() { cout << "B析构" << endl; }
//};
//int main()
//{
//    B b1;
//    b1.a = 15;
//    A a1(b1); //复制构造
//}
