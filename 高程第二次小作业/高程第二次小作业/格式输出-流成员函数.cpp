//#include<iostream>
//using namespace std;
//
//int main()
//{
//    cout << "请输入一些浮点数，以q结束:" << endl;
//    double arr[10000];
//    int intLen[10000];
//    int pos = 0;
//
//    while (true)
//    {
//        double num;
//        if (cin >> num)
//        {
//            long long temp = static_cast<long long>(num * 1000);
//            num = temp / 1000.0;
//            arr[pos++] = num;
//        }
//        else
//        {
//            cin.clear();
//            char ch;
//            cin >> ch;
//            if (ch != 'q')
//                continue;
//
//            int maxLen = 0;
//            for (int i = 0; i < pos; i++)
//            {
//                int count = 0;
//                long long temp = static_cast<long long>(abs(arr[i]));
//
//                if (temp == 0)
//                {
//                    count = 1;
//                }
//                else
//                {
//                    do {
//                        temp /= 10;
//                        count++;
//                    } while (temp > 0);
//                }
//
//                if (arr[i] < 0)
//                    count++;
//
//                intLen[i] = count;
//                if (count > maxLen)
//                    maxLen = count;
//            }
//
//            for (int i = 0; i < pos; i++)
//            {
//                int spaces = maxLen - intLen[i];
//                for (int j = 0; j < spaces; j++)
//                {
//                    cout <<" ";
//                }
//
//                cout.precision(3);
//                cout.setf(ios::fixed);
//                cout << arr[i] << endl;
//                cout.unsetf(ios::fixed);
//            }
//
//            cout << "------程序结束------" << endl;
//            break;
//        }
//    }
//
//    return 0;
//}
