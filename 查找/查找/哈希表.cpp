//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//#include<cstring>
//using namespace std;
//
//bool prime(int n)
//{
//    if (n < 2) return false;
//    for (int i = 2; i * i <= n; i++)
//    {
//        if (n % i == 0) return false;
//    }
//    return true;
//}
//
//int getprime(int n)
//{
//    while (!prime(n))
//    {
//        n++;
//    }
//    return n;
//}
//
//int main()
//{
//    int n, p;
//    cin >> n >> p;
//    int m = getprime(p);
//    int* hash = new int[m];
//    for (int i = 0; i < m; i++)
//    {
//        hash[i] = 0;
//    }
//
//    for (int i = 0; i < n; i++)
//    {
//        char name[101] = {};
//        cin >> name;
//        int l = strlen(name);
//
//        unsigned long long int val = 0;
//        for (int j = 0; j < l; j++)
//        {
//            val = val * 37 + (unsigned long long int)(name[j]);
//        }
//
//        int pos = val % m;
//        bool found = false;
//        int insert_pos = -1;
//        for (int k = 0; k <= m; k++)
//        {
//            int offset;
//            if (k == 0)
//            {
//                offset = 0;
//            }
//            else if (k % 2 == 1)
//            {
//                int t = (k + 1) / 2;
//                offset = t * t;
//            }
//            else
//            {
//                int t = k / 2;
//                offset = -t * t;
//            }
//            int repos = (pos + offset) % m;
//            if (repos < 0) repos += m;
//
//            if (hash[repos] == 0)
//            {
//                hash[repos] = 1;
//                insert_pos = repos;
//                found = true;
//                break;
//            }
//        }
//
//        if (found)
//        {
//            cout << insert_pos << " ";
//        }
//        else
//        {
//            cout << "-" << " ";
//        }
//    }
//
//    cout << endl;
//    delete[] hash;
//    return 0;
//}