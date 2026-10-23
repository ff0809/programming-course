//#include <iostream>
//using namespace std;
//
//class Matrix
//{
//private:
//    int** data; // 二维数组指针
//    int row, col; // 行数和列数
//
//public:
//    Matrix(int r, int c); // 构造函数
//    ~Matrix(); // 析构函数
//
//    /****************** TODO ******************/
//    friend Matrix operator+(const Matrix& a, const Matrix& b);
//    friend Matrix operator-(const Matrix& a, const Matrix& b);
//    friend Matrix operator*(int a, const Matrix& b);
//    friend Matrix operator*(const Matrix& a, int b);
//    friend istream& operator>>(istream& is, Matrix& a);
//    friend ostream& operator<<(ostream& os, Matrix& a);
//    /**************** TODO-END ****************/
//};
//
///****************** TODO ******************/
//Matrix::Matrix(int r, int c)
//{
//    row = r;
//    col = c;
//    data = new int* [row];
//    for (int i = 0; i < row; i++)
//    {
//        data[i] = new int[col];
//        for (int j = 0; j < col; j++)
//        {
//            data[i][j] = 0;
//        }
//    }
//}
//Matrix::~Matrix()
//{
//    for (int i = 0; i < row; i++)
//    {
//        delete[]data[i];
//    }
//    delete[]data;
//}
//Matrix operator+(const Matrix& a, const Matrix& b)
//{
//    Matrix c(a.row,a.col);
//    for (int i = 0; i < a.row; i++)
//    {
//        for (int j = 0; j < a.col; j++)
//        {
//            c.data[i][j] = a.data[i][j] + b.data[i][j];
//        }
//    }
//    return c;
//}
//Matrix operator-(const Matrix& a, const Matrix& b)
//{
//    Matrix c(a.row, a.col);
//    for (int i = 0; i < a.row; i++)
//    {
//        for (int j = 0; j < a.col; j++)
//        {
//            c.data[i][j] = a.data[i][j] - b.data[i][j];
//        }
//    }
//    return c;
//}
//Matrix operator*(int a, const Matrix& b)
//{
//    Matrix c(b.row, b.col);
//    for (int i = 0; i < b.row; i++)
//    {
//        for (int j = 0; j < b.col; j++)
//        {
//            c.data[i][j] = a * b.data[i][j];
//        }
//    }
//    return c;
//}
//Matrix operator*(const Matrix& a, int b)
//{
//    Matrix c(a.row, a.col);
//    for (int i = 0; i < a.row; i++)
//    {
//        for (int j = 0; j < a.col; j++)
//        {
//            c.data[i][j] = a.data[i][j] * b;;
//        }
//    }
//    return c;
//}
//istream& operator>>(istream& is, Matrix& a)
//{
//    for (int i = 0; i < a.row; i++)
//    {
//        for (int j = 0; j < a.col; j++)
//        {
//            is >> a.data[i][j];
//        }
//    }
//    return is;
//}
//ostream& operator<<(ostream& os, Matrix& a)
//{
//    for (int i = 0; i < a.row; i++)
//    {
//        for (int j = 0; j < a.col; j++)
//        {
//            os << a.data[i][j] << " ";
//        }
//        os << endl;
//    }
//    return os;
//}
///**************** TODO-END ****************/
//
//int main()
//{
//    // 输入矩阵的行数和列数
//    int r, c;
//    cout << "请输入矩阵的行数和列数：" << endl;
//    cin >> r >> c;
//    // 创建三个矩阵对象
//    Matrix A(r, c), B(r, c), C(r, c);
//    // 输入三个矩阵的元素
//    cout << "请输入矩阵A的元素：" << endl;
//    cin >> A;
//    cout << "请输入矩阵B的元素：" << endl;
//    cin >> B;
//    cout << "请输入矩阵C的元素：" << endl;
//    cin >> C;
//    // 输入三个矩阵的组合系数
//    int ka, kb, kc;
//    cout << "请依次输入矩阵A、B、C的组合系数ka，kb，kc：" << endl;
//    cin >> ka >> kb >> kc;
//
//    /********** 测试矩阵简单线性组合 **********/
//    Matrix D1 = ka * A + kb * B + kc * C;
//    cout << "D1 = " << ka << " * A + " << kb << " * B + " << kc << " * C = " << endl;
//    cout << D1 << endl;
//    Matrix D2 = A * ka + B * kb + C * kc;
//    cout << "D2 = A * " << ka << " + B * " << kb << " + C * " << kc << " = " << endl;
//    cout << D2 << endl;
//
//    /********** 测试矩阵复杂线性组合 **********/
//    Matrix D3 = A * kb * kc + B * ka * kc + C * ka * kb;
//    cout << "D3 = A * " << kb << " * " << kc << " + B * " << ka << " * " << kc << " + C * " << ka << " * " << kb << " = " << endl;
//    cout << D3 << endl;
//    Matrix D4 = ka * (kb * (A + B + C)) * kc;
//    cout << "D4 = " << ka << " * (" << kb << " * (A + B + C)) * " << kc << " = " << endl;
//    cout << D4 << endl;
//    Matrix D5 = ka * (kb * (kc * A) + B) + C;
//    cout << "D5 = " << ka << " * (" << kb << " * (" << kc << " * A) + B) + C = " << endl;
//    cout << D5 << endl;
//
//    return 0;
//}