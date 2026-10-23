//#include <iostream>
//#include <cmath>
//
//
//using namespace std;
//
//
//class Shape
//{
//public:
//    virtual double area() = 0;
//};
//
//class Circle :public Shape
//{
//private:
//    double radius;
//public:
//    Circle(double r) :radius(r) {}
//    double area()
//    {
//        return 3.14159 * radius * radius;
//    }
//};
//
//class Square :public Shape
//{
//private:
//    double length;
//public:
//	Square(double l) :length(l) {}
//    double area()
//    {
//        return length * length;
//	}
//};
//
//class Rectangle :public Shape
//{
//private:
//	double width, length;
//public:
//    Rectangle(double l, double w) :width(w), length(l) {}
//    double area()
//    {
//        return width * length;
//	}
//
//};
//
//class Trapezoid :public Shape
//{
//private:
//    double a, b, h;
//public:
//    Trapezoid(double sideA, double sideB, double height) :a(sideA), b(sideB), h(height) {}
//    double area()
//    {
//        return (a + b) * h / 2;
//    }
//};
//
//class Triangle :public Shape
//{
//private:
//    double a, b, c;
//public:
//    Triangle(double sideA, double sideB, double sideC) :a(sideA), b(sideB), c(sideC) {}
//    double area()
//    {
//        double s = (a + b + c) / 2;
//        return sqrt(s * (s - a) * (s - b) * (s - c));
//    }
//};
//
//int main() {
//    Circle    c1(2);
//    Square    s1(3);
//    Rectangle r1(4, 5);
//    Trapezoid t1(6, 7, 8);
//    Triangle  t2(3, 4, 5);
//
//
//    Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };
//
//
//    for (int i = 0; i < 5; i++) {
//        cout << s[i]->area() << endl;
//    }
//    return 0;
//}