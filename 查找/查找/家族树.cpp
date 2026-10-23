//#include <iostream>
//#include <string>
//#include <map>
//#include <vector>
//#include <sstream>
//#include <algorithm>
//using namespace std;
//
//struct person {
//    string name;
//    int depth;
//    person* parent;
//    vector<person*> children;
//
//    person(string n, int d) : name(n), depth(d), parent(nullptr) {}
//};
//
//bool isallspaces(const string& str) {
//    return all_of(str.begin(), str.end(), [](char c) { return c == ' '; });
//}
//
//int main() {
//    int n, m;
//    while (cin >> n >> m) {
//        if (n == 0 && m == 0) break;
//
//        cin.ignore(); 
//
//        map<string, person*> nametoperson;
//        vector<person*> persons;
//
//        person* currentparent = nullptr;
//        int lastdepth = -1;
//
//        for (int i = 0; i < n; i++) {
//            string line;
//            getline(cin, line);
//
//            int depth = 0;
//            while (depth < line.length() && line[depth] == ' ') {
//                depth++;
//            }
//
//            string name = line.substr(depth);
//
//            person* newperson = new person(name, depth);
//            nametoperson[name] = newperson;
//            persons.push_back(newperson);
//
//            if (depth == 0) {
//                currentparent = newperson;
//            }
//            else if (depth > lastdepth) {
//                newperson->parent = currentparent;
//                if (currentparent) {
//                    currentparent->children.push_back(newperson);
//                }
//                currentparent = newperson;
//            }
//            else if (depth == lastdepth) {
//                newperson->parent = currentparent->parent;
//                if (currentparent->parent) {
//                    currentparent->parent->children.push_back(newperson);
//                }
//                currentparent = newperson;
//            }
//            else {
//                person* temp = currentparent;
//                while (temp && temp->depth >= depth) {
//                    temp = temp->parent;
//                }
//                newperson->parent = temp;
//                if (temp) {
//                    temp->children.push_back(newperson);
//                }
//                currentparent = newperson;
//            }
//
//            lastdepth = depth;
//        }
//
//        for (int i = 0; i < m; i++) {
//            string line;
//            getline(cin, line);
//
//            stringstream ss(line);
//            string x, y, relation;
//
//            ss >> x;
//
//            string temp;
//            ss >> temp;  // "is"
//            ss >> temp;
//
//            if (temp == "a" || temp == "an" || temp == "the") {
//                ss >> relation;
//            }
//            else {
//                relation = temp;
//            }
//
//            ss >> temp;
//
//            string ywithdot;
//            ss >> ywithdot;
//            y = ywithdot.substr(0, ywithdot.length() - 1);
//
//            person* personx = nametoperson[x];
//            person* persony = nametoperson[y];
//
//            bool result = false;
//
//            if (relation == "child") {
//                if (personx && persony && personx->parent == persony) {
//                    result = true;
//                }
//            }
//            else if (relation == "parent") {
//                if (personx && persony && persony->parent == personx) {
//                    result = true;
//                }
//            }
//            else if (relation == "sibling") {
//                if (personx && persony && personx->parent == persony->parent) {
//                    result = true;
//                }
//            }
//            else if (relation == "descendant") {
//                if (personx && persony) {
//                    person* current = personx;
//                    while (current) {
//                        if (current == persony) {
//                            result = true;
//                            break;
//                        }
//                        current = current->parent;
//                    }
//                    if (personx == persony) {
//                        result = true;
//                    }
//                }
//            }
//            else if (relation == "ancestor") {
//                if (personx && persony) {
//                    person* current = persony;
//                    while (current) {
//                        if (current == personx) {
//                            result = true;
//                            break;
//                        }
//                        current = current->parent;
//                    }
//                    if (personx == persony) {
//                        result = true;
//                    }
//                }
//            }
//            cout << (result ? "true" : "false") << endl;
//        }
//
//        cout << endl;  // 每个测试用例后输出空行
//
//        for (person* p : persons) {
//            delete p;
//        }
//    }
//
//    return 0;
//}