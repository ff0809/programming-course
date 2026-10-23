//#include <iostream> 
//using namespace std;
//class A {
//public:
//    int a;
//    void f1() { return; }
//};
//class B :public A {
//public:
//    int b;
//};
//class C {
//public:
//    long a;
//    int f1() { return 0; }
//};
//class D :public B, public C {
//public:
//    int a;
//    char f1() { return 'A'; }
//    void fun();
//};
//void D::fun() {
//    a = 10;
//    f1();
//    A::a = 15; // B::a = 15;  
//    A::f1();   // B::f1();  
//    C::a = 20;
//    C::f1();
//    int* p = (int*)this;
//    cout << sizeof(*this) << endl;
//    cout << *p << endl;
//    cout << *(p + 1) << endl;
//    cout << *(p + 2) << endl;
//    cout << *(p + 3) << endl;
//}
//int main() {
//    D d1;
//    d1.fun();
//    return 0;
//}
