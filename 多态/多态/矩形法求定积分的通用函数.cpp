#include <iostream>
#include <cmath>


using namespace std;

class integral
{
public:
    double a, b;
    virtual double value() = 0;
};

class integral_sin :public integral
{
private:
    
public:
    double value()
    {
        double sum = 0.0;
        for (int i = 0; i <= 10000; i++)
        {
            sum += sin(a + (b - a) / 10000 * i) * (b - a) / 10000.0;
        }
        return sum;
    }
};

class integral_cos :public integral
{
public:
    double value()
    {
        double sum = 0.0;
        for (int i = 0; i <= 10000; i++)
        {
            sum += cos(a + (b - a) / 10000 * i) * (b - a) / 10000;
        }
        return sum;
    }
};

class integral_exp :public integral
{
public:
    double value()
    {
        double sum = 0.0;
        for (int i = 0; i <= 10000; i++)
        {
            sum += exp(a + (b - a) / 10000 * i) * (b - a) / 10000;
        }
        return sum;
    }
};

istream& operator>>(istream& is, integral&p)
{
    is >> p.a >> p.b;
    return is;
}

int main()
{
    integral_sin s1;
    integral_cos s2;
    integral_exp s3;
    integral* p;


    cout << "请输入上下限：";
    cin >> s1;
    p = &s1;
    cout << "∫sinxdx的计算结果为：" << (p->value()) << endl;


    cout << "请输入上下限：";
    cin >> s2;
    p = &s2;
    cout << "∫cosxdx的计算结果为：" << (p->value()) << endl;


    cout << "请输入上下限：";
    cin >> s3;
    p = &s3;
    cout << "∫expxdx的计算结果为：" << (p->value()) << endl;


    return 0;
}