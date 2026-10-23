//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//#include<stdlib.h>
//#include<stdio.h>
//using namespace std;
//
//int main()
//{
//	int arr[20];
//	int pos = 0;
//	FILE* fp = fopen("1.txt", "r");
//	if (fp == NULL)
//	{
//		cout << "文件打开失败！" << endl;
//		exit(EXIT_FAILURE);
//	}
//	int num;
//	while (fscanf(fp, "%d", &num)==1)
//	{
//		arr[pos++] = num;
//	}
//	fclose(fp);
//	for (int i = 0; i < 10; i++)
//	{
//		cin >> num;
//		arr[pos++] = num;
//	}
//	for (int i = 0; i < 20; i++)
//	{
//		for (int j = 0; j < 19 - i; j++)
//		{
//			if (arr[j] > arr[j + 1])
//			{
//				int temp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = temp;
//			}
//		}
//	}
//	for (int i = 0; i < 20; i++)
//	{
//		cout << arr[i] << " ";
//	}
//	cout << endl;
//	return 0;
//}
