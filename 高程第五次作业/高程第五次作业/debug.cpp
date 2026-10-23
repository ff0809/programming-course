#define _CRT_SECURE_NO_WARNINGS //ÐÞ¸Ä1
#include <iostream>
#include <cstring>
using namespace std;

class Person {
private:
    char name[20];
    int age;
public:
    Person(const char* n, int a) {
        strcpy(name, n);
        age = a;
    }
    void display() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

class Student : public Person {
private:
    int studentID;
    char major[20];
    Person teacher;
public:
    Student(const char* n, int a, int id, const char* m, const char* tName, int tAge):Person(n,a),teacher(tName,tAge) { //ÐÞ¸Ä2
        studentID = id;
        strcpy(major, m);
    }

    void showInfo() {
        display();
        cout << "Student ID: " << studentID << ", Major: " << major << endl;
        teacher.display();
    }

    void changeMajor(const char* newMajor) {
        strcpy(major, newMajor);//ÐÞ¸Ä3
    }
};

class GraduateStudent : private Student {
private:
    char researchArea[30];
public:
    GraduateStudent(const char* n, int a, int id, const char* m, const char* tName, int tAge, const char* area)
        : Student(n, a, id, m, tName, tAge) {
        strcpy(researchArea, area);
    }

    void showResearch() {
        showInfo();
        cout << "Research Area: " << researchArea << endl;
    }
};

int main() {
    Person p("Dr. Wang", 40);
    p.display();

    Student s("Zhang San", 20, 1001, "Computer Science", "Dr. Wang", 40);
    s.showInfo();

    GraduateStudent gs("Li Si", 25, 2001, "Mathematics", "Dr. Li", 45, "Algebra");
    gs.showResearch();

    return 0;
}