//#include <iostream>  
//using namespace std;
//static int x = 0;
//class A {
//public:
//    int a;
//    A() { a = ++x; }
//    void f1() { cout << a << endl; }
//};
//class B :public A {
//public:
//    int b;
//};
//class C :public A {
//public:
//    int c;
//};
//class D :public B, public C {
//public:
//    int d;
//    int fun();
//};
//int D::fun() {
//    A::a = 5; //不建议
//    A::f1();  //不建议
//    B::a = 10;
//    B::f1();
//    C::a = 15;
//    C::f1();
//    return 0;
//}
//int main() {
//    D d1;
//    cout << sizeof(d1) << endl;
//    d1.fun();
//    d1.f1();   //报错：对f1的访问不明确
//    d1.A::f1();//报错：对A的访问不明确
//    d1.B::a = 10;
//    d1.B::f1();
//    d1.C::a = 15;
//    d1.C::f1();
//    return 0;
//}