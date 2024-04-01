#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <utility>
#include <list>
#include <stack>

struct Node {

  std::string data;
  Node* parent = nullptr;
  std::list<Node*> children;

  Node(const std::string& str = ""):
    data(str) {}
};

void delete_node(Node* node) {

  if (!node) {
    return;
  }

  for (auto child: node->children) {
    delete_node(child);
  }
  
  delete node;
}

void insert_node(Node* node, const std::string& str) {

  Node* new_node = nullptr;  

  for (auto iter = node->children.begin(); iter != node->children.end(); ++iter) {

    Node* child = *iter;

    if (str == child->data) {
      return;
    }

    if (str.starts_with(child->data)) {

      insert_node(child, str);
      return;
    }

    if (child->data.starts_with(str)) {

      Node* new_node = new Node(str);

      child->parent = new_node;
      new_node->children.push_back(child);
      node->children.erase(iter);

      break;
    }
  }

  new_node = (new_node)? new_node : new Node(str);
  
  new_node->parent = node;
  node->children.push_back(new_node);
}

class Tree final {

  Node* root_ = new Node;

public:

  Tree() {}

  Tree(const Tree& that) = delete;
  Tree& operator=(const Tree& that) = delete;

  Tree(Tree&& that) {
    root_ = std::exchange(that.root_, nullptr);
  }

  Tree& operator=(Tree&& that) {
    std::swap(root_, that.root_);
    return *this;
  }

  ~Tree() {
    delete_node(root_);
  }

  void insert(const std::string& str) {
    insert_node(root_, str);
  }

  bool match(const std::string_view& str) {

    size_t str_len = str.size();

    std::stack<std::pair<Node*,size_t>> stack;

    for (auto iter = root_->children.begin(); iter != root_->children.end(); ++iter) {
      stack.push(std::make_pair(*iter, 0));
    }

    for (;;) {

      if (!stack.size()) {
        return false;
      }

      auto state = stack.top();
      Node* node = state.first;
      size_t cur_str_pos = state.second;

      stack.pop();

      for (auto iter = node->children.begin(); 
                iter != node->children.end(); ++iter) {
        stack.push(std::make_pair(*iter, cur_str_pos));
      }

      if (str.substr(cur_str_pos).starts_with(node->data)
       && str != node->data) {

        for (auto iter = node->children.begin(); iter != node->children.end(); ++iter) {
          stack.push(std::make_pair(*iter, cur_str_pos));
        }

        cur_str_pos += node->data.size();
        if (cur_str_pos == str_len) {
          return true;
        }

        for (auto iter = root_->children.begin(); iter != root_->children.end(); ++iter) {
          stack.push(std::make_pair(*iter, cur_str_pos));
        }

      }
    }
  }
};

int main() {

  unsigned num;
  std::cin >> num;

  std::set<std::string> set;

  for (unsigned elem_idx = 0; elem_idx < num; ++elem_idx) {

    std::string elem;
    std::cin >> elem;

    set.insert(elem);
  }

  Tree tree;

  for (const auto& str : set) {
    tree.insert(str);
  }

  auto iter = set.begin();

  while ((*iter).size() == 1) {
    iter++;
  }

  for (; iter != set.end(); ++iter) {

    if (tree.match(*iter)) {
      std::cout << *iter << std::endl;
    }
  }

  return 0;
}
