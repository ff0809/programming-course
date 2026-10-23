//#include <iostream>  
//using namespace std;
//static int x = 0;
//class A {
//public:
//    int a;
//    A() {
//        a = ++x;
//        cout << "A()" << endl;
//    }
//};
//class B :public A {
//public:
//    int b;
//    B() {
//        b = 20;
//        cout << "B()" << endl;
//    }
//};
//class C :public A {
//public:
//    int c;
//    C() {
//        c = 30;
//        cout << "C()" << endl;
//    }
//};
//class D :public B, public C {
//public:
//    int d;
//    D() {
//        d = 40;
//        cout << "D()" << endl;
//    }
//};
//int main() {
//    D d1;
//    cout << sizeof(d1) << endl;
//    int* p = (int*)&d1;
//    cout << *p << endl;
//    cout << *(p + 1) << endl;
//    cout << *(p + 2) << endl;
//    cout << *(p + 3) << endl;
//    cout << *(p + 4) << endl;
//    return 0;
//}
