#ifndef __TREAP
#define __TREAP
#include <string>
#include <cstdlib>
#include <string>

struct TreapNode {
  std::string key;
  int value;
  int priority;
  TreapNode* left;
  TreapNode* right;
  // TreapNode constructor
  TreapNode(int valuep, std::string keyp) 
  {
    priority = rand();
    left = NULL;
    right = NULL;
    value = valuep;
    key = keyp;
  }
  // you can add a constructor
};

class Treap {
  TreapNode *root;
  // add more helper functions here
  
 public:
  Treap(); // Constructor is defined in Treap.cc file
  void insert(const std::string& key, int value);
  TreapNode* insert_helper(const std::string& key, int value, TreapNode*& root);
  TreapNode* rotate_right(TreapNode* node);
  TreapNode* rotate_left(TreapNode* node);
  TreapNode* getRoot(void);
  int find(const std::string& key);
  TreapNode* find_helper(const std::string& key, TreapNode* root);
  // return value for the key if found
  // if not found returns -1
  void printTreap(TreapNode *&root);
  void printTreapHelper(TreapNode *&root, int depth);
};

#endif
