//#include<iostream>
//#include<cstring>
//using namespace std;
//
//char* get(char pre[], int prestart, int prelen,char in[], int instart, int inlen)
//{
//	if (prelen != inlen)
//	{
//		return NULL;
//	}
//	if (prelen == 0)
//	{
//		char* c = (char*)malloc(1);
//		c[0] = '\0';
//		return c;
//	}
//	char root = pre[prestart];
//	int inrootpos=-1;
//	for (int i = 0; i < inlen; i++)
//	{
//		if (in[instart+i] == root)
//		{
//			inrootpos = i;
//			break;
//		}
//	}
//	if (inrootpos == -1)return NULL;
//	int leftlen = inrootpos;
//	int rightlen = inlen - leftlen - 1;
//	char* left = NULL;
//	char* right = NULL;
//	if (leftlen > 0)
//	{
//		left = get(pre, prestart + 1, leftlen, in, instart, leftlen);
//		if (!left)return NULL;
//	}
//	if (rightlen > 0)
//	{
//		right = get(pre, prestart + leftlen + 1, rightlen, in, instart + leftlen+1, rightlen);
//		if (!right)return NULL;
//	}
//	char* result = (char*)malloc((prelen+1)*sizeof(char));
//	int pos = 0;
//	if (leftlen > 0)
//	{
//		for (int i = 0; i < leftlen; i++)
//		{
//			result[pos++] = left[i];
//		}
//	}
//	if (rightlen > 0)
//	{
//		for (int i = 0; i < rightlen; i++)
//		{
//			result[pos++] = right[i];
//		}
//	}
//	result[pos++] = root;
//	result[pos] = '\0';
//	return result;
//}
//
//int main()
//{
//	char pre[100], in[100];
//	while (cin >> pre >> in)
//	{
//		char* result = get(pre, 0, strlen(pre), in, 0, strlen(in));
//		if (result == NULL)
//		{
//			cout << "Error" << endl;
//		}
//		else
//		{
//			cout << result << endl;
//		}
//	}
//}