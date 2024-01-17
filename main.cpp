#include <iostream>

#include "skiplist.h"
using namespace std;

int main() {
  int level;
  cout << "最大层数：";
  cin >> level;
  cout << "OK!" << endl << endl;
  SkipList lst(level);
  string command;
  int key, value;
  while (true) {
    cin >> command;
    if (command[0] == 'q') {
      break;
    } else if (command[0] == 'i') {
      cin >> key >> value;
      bool res = lst.insert_element(key, value);
      if (!res) {
        cout << "插入失败，重复" << endl;
      }
    } else if (command[0] == 's') {
      cin >> key;
      bool res = lst.search_element(key, value);
      if (res) {
        cout << "找到了：" << value << endl;
      } else {
        cout << "没找到" << endl;
      }
    } else if (command[0] == 'd') {
      cin >> key;
      bool res = lst.delete_element(key);
      if (res) {
        cout << "删除成功" << endl;
      } else {
        cout << "没找到" << endl;
      }
    }
    lst.display_list();
  }
  return 0;
}
