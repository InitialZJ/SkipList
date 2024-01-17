#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

#include <iostream>
#include <vector>

class Node {
 public:
  Node(int key, int value, int level);

  ~Node();

  const int& key() const;

  const int& value() const;

  std::vector<Node*> forward;

 private:
  int key_;
  int value_;
};

class SkipList {
 public:
  SkipList(int max_level);
  ~SkipList();

  int get_random_level();

  Node* create_node(int key, int value, int level);

  bool insert_element(int key, int value);

  bool search_element(int key, int& value);

  bool delete_element(int key);

  void display_list();

 private:
  int max_level_;

  int skip_list_level_;

  Node* header_;
};

#endif  // !SKIP_LIST_H_
