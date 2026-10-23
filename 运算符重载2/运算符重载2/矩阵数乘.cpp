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
//    data = new int*[row];
//    for (int i = 0; i < row; i++)
//    {
//        data[i] = new int[col];
//        for (int j = 0; j < col;j++)
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
//    Matrix c(a.row,a.col);
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
//            os << a.data[i][j]<<" ";
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
//    // 创建矩阵对象
//    Matrix M(r, c);
//    // 输入矩阵的元素
//    cout << "请输入矩阵M的元素：" << endl;
//    cin >> M;
//    // 输入数乘的数
//    int k;
//    cout << "请输入数乘的数k：" << endl;
//    cin >> k;
//
//    /********** 测试矩阵左 / 右乘一个数 **********/
//    Matrix M1 = M * k;
//    cout << "M1 = M * " << k << "：" << endl;
//    cout << M1 << endl;
//    Matrix M2 = k * M;
//    cout << "M2 = " << k << " * M：" << endl;
//    cout << M2 << endl;
//
//    /************* 测试矩阵复合乘法 *************/
//    Matrix M3 = M * k * k;
//    cout << "M3 = M * " << k << " * " << k << "：" << endl;
//    cout << M3 << endl;
//    Matrix M4 = k * M * k;
//    cout << "M4 = " << k << " * M * " << k << "：" << endl;
//    cout << M4 << endl;
//    Matrix M5 = k * (k * M);
//    cout << "M5 = " << k << " * " << k << " * M：" << endl;
//    cout << M5 << endl;
//
//    return 0;
//}