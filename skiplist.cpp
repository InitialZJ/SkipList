#include "skiplist.h"

Node::Node(int key, int value, int level) {
  key_ = key;
  value_ = value;
  forward = std::vector<Node*>(level, nullptr);
}

Node::~Node() { forward.clear(); }

const int& Node::key() const { return key_; }

const int& Node::value() const { return value_; }

SkipList::SkipList(int max_level) {
  max_level_ = max_level;
  skip_list_level_ = 0;
  header_ = new Node(0, 0, max_level_);
  srand(time(nullptr));
}

SkipList::~SkipList() {
  auto tmp = header_;
  while (header_->forward[0]) {
    tmp = header_->forward[0];
    header_->forward[0] = tmp->forward[0];
    delete tmp;
  }
  delete header_;
}

int SkipList::get_random_level() {
  int k = 1;
  while (k < max_level_ && rand() & 1) {
    k++;
  }
  return k;
}

Node* SkipList::create_node(int key, int value, int level) {
  return new Node(key, value, level);
}

bool SkipList::insert_element(int key, int value) {
  Node* cur = header_;
  std::vector<Node*> update(max_level_, nullptr);

  for (int i = skip_list_level_ - 1; i >= 0; i--) {
    while (cur->forward[i] && cur->forward[i]->key() < key) {
      cur = cur->forward[i];
    }
    update[i] = cur;
  }

  cur = cur->forward[0];
  if (cur && cur->key() == key) {
    return false;
  }

  int random_level = get_random_level();
  if (random_level > skip_list_level_) {
    for (int i = skip_list_level_; i < random_level; i++) {
      update[i] = header_;
    }
    skip_list_level_ = random_level;
  }

  Node* insert_node = create_node(key, value, random_level);
  for (int i = 0; i < random_level; i++) {
    insert_node->forward[i] = update[i]->forward[i];
    update[i]->forward[i] = insert_node;
  }
  return true;
}

bool SkipList::search_element(int key, int& value) {
  Node* cur = header_;
  for (int i = skip_list_level_ - 1; i >= 0; i--) {
    while (cur->forward[i] && cur->forward[i]->key() < key) {
      cur = cur->forward[i];
    }
  }

  cur = cur->forward[0];
  if (cur && cur->key() == key) {
    value = cur->value();
    return true;
  }
  return false;
}

bool SkipList::delete_element(int key) {
  Node* cur = header_;
  std::vector<Node*> update(max_level_, nullptr);

  for (int i = skip_list_level_ - 1; i >= 0; i--) {
    while (cur->forward[i] && cur->forward[i]->key() < key) {
      cur = cur->forward[i];
    }
    update[i] = cur;
  }

  cur = cur->forward[0];
  if (!cur || cur->key() != key) {
    return false;
  }

  for (int i = 0; i < skip_list_level_; i++) {
    if (update[i]->forward[i] != cur) {
      break;
    }
    update[i]->forward[i] = cur->forward[i];
  }

  while (skip_list_level_ > 0 &&
         header_->forward[skip_list_level_ - 1] == nullptr) {
    skip_list_level_--;
  }
  delete cur;
  return true;
}

void SkipList::display_list() {
  std::cout << "*************************" << std::endl;
  for (int i = skip_list_level_ - 1; i >= 0; i--) {
    Node* node = header_->forward[i];
    std::cout << "L " << i << ": ";
    while (node) {
      std::cout << "[" << node->key() << ", " << node->value() << "] ";
      node = node->forward[i];
    }
    std::cout << std::endl;
  }
  std::cout << "*************************" << std::endl << std::endl;
}
