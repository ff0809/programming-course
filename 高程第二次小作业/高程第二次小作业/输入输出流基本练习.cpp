//#include<iostream>
//using namespace std;
//
//istream& f(istream& in) {
//    /* 复读整数，并拒绝错误输入 */
//    auto in_state = in.rdstate(); // 保存流入函数的状态
//
//    int num;
//    while (true)
//    {
//        if (cin >> num)
//        {
//            if (num == -1)
//            {
//                cout << "------程序结束------" << endl;
//                break;
//            }
//            cout << "你说了:" << num << endl;
//        }
//        else if (cin.eof())
//        {
//            cout << "------程序结束------" << endl;
//            break;
//        }
//        else
//        {
//            cout << "Illegal" << endl;
//            cin.clear();
//            while (!isspace(cin.get()))
//            {
//                continue;
//            }
//        }
//    }
//
//    in.setstate(in_state);        // 复位流           
//    return in;
//}
//
//int main() {
//    cout << "请输入一些整数，以-1或Ctrl+Z结束。" << endl;
//    f(cin);
//    return 0;
//}
//
///*
//注：采用复位方式1更好，两种代码都用于复位流状态，但是方案1保存并恢复初始状态，完全不改变流的原始状态；
//    而方案2仅清除错误标志，会破坏流的原始状态，因此方案1更好，它能够严谨保证流状态的一致，避免隐藏bug
//    而对后续开发产生不必要的影响。
//*/