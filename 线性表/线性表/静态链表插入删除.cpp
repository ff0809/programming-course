//#include <iostream>
//#include <cstring>
//#define MAXSIZE 10
//using namespace std;
//
//typedef struct {
//    char name[20];
//    int cur;
//} slinknode, slinklist[MAXSIZE];
//
//// 假设题目给定如下静态链表数据
//void init_given_list(slinklist& s) {
//    // 主链表头结点
//    s[0].cur = 1; // 指向第一个有效节点
//
//    // 有效数据节点
//    strcpy_s(s[1].name, "赵"); s[1].cur = 2;
//    strcpy_s(s[2].name, "钱"); s[2].cur = 3;
//    strcpy_s(s[3].name, "孙"); s[3].cur = 4;
//    strcpy_s(s[4].name, "李"); s[4].cur = 0; // 最后一个节点
//
//    // 备用链表（假设5~8为备用节点）
//    for (int i = 5; i < MAXSIZE - 1; ++i) {
//        s[i].name[0] = '\0';
//        s[i].cur = i + 1;
//    }
//    s[MAXSIZE - 2].cur = 0; // 最后一个备用节点
//    s[MAXSIZE - 1].cur = 5; // 备用链表头指向第一个备用节点
//}
//
//// 显示链表内容
//void displist(slinklist& s) {
//    int i = s[0].cur;
//    while (i != 0) {
//        cout << s[i].name << " ";
//        i = s[i].cur;
//    }
//    cout << endl;
//}
//
//// 插入节点到第pos个位置（1开始），插入内容为name
//bool insertlist(slinklist& s, const char* name, int pos) {
//    int freeIdx = s[MAXSIZE - 1].cur;
//    if (freeIdx == 0) {
//        cout << "链表已满，无法插入！" << endl;
//        return false;
//    }
//    strcpy_s(s[freeIdx].name, name);
//
//    // 找到插入位置的前一个节点
//    int p = 0;
//    for (int j = 1; j < pos && s[p].cur != 0; ++j) {
//        p = s[p].cur;
//    }
//
//    // 备用链表头后移
//    s[MAXSIZE - 1].cur = s[freeIdx].cur;
//    // 插入新节点
//    s[freeIdx].cur = s[p].cur;
//    s[p].cur = freeIdx;
//    return true;
//}
//
//// 删除第pos个节点（1开始）
//bool deletelist(slinklist& s, int pos) {
//    int p = 0;
//    for (int j = 1; j < pos && s[p].cur != 0; ++j) {
//        p = s[p].cur;
//    }
//    int delIdx = s[p].cur;
//    if (delIdx == 0) {
//        cout << "删除位置不存在！" << endl;
//        return false;
//    }
//
//    // 从主链表断开
//    s[p].cur = s[delIdx].cur;
//    s[delIdx].name[0] = '\0';
//
//    // 加入备用链表
//    s[delIdx].cur = s[MAXSIZE - 1].cur;
//    s[MAXSIZE - 1].cur = delIdx;
//    return true;
//}
//
//int main() {
//    slinklist s;
//    init_given_list(s);
//
//    cout << "初始链表: ";
//    displist(s);
//
//    insertlist(s, "周", 3); // 在第3个位置插入"周"
//    cout << "插入'周'到第3个位置后: ";
//    displist(s);
//
//    deletelist(s, 2); // 删除第2个位置
//    cout << "删除第2个位置后: ";
//    displist(s);
//
//    return 0;
//}