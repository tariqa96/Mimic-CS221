#include "treap.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <vector>

using namespace std;
/**
 * Constructor
 */
Treap::Treap(void)
{
  srand(time(0));
  root = NULL;
}
/**
 * Getter function to get root for testing purposes.
 */
TreapNode* Treap::getRoot() {
  return root;
}
/**
 * find function which returns the value in a TreapNode that has a matching key, or -1 if the key does not match with any existing TreapNodes.
 */
int Treap::find(const string& key)
{
  TreapNode *result = Treap::find_helper(key, root);
  return (result == NULL) ? -1 : result->value; // Ternary operator to return TreapNode value or -1 if not found
}

/**
 * find helper function; Returns the TreapNode if found or NULL if not 
 */
TreapNode* Treap::find_helper(const string& key, TreapNode* root)
{
  // Base cases to terminate recursive function; if root is either null or we have found the key, we return NULL or the key
  if (root == NULL)
    return NULL;
  if (root->key == key)
    return root;
  // Recurse while returning the TreapNode
  TreapNode *leftTreapNode = Treap::find_helper(key, root->left);
  TreapNode *rightTreapNode = Treap::find_helper(key, root->right);

  if (leftTreapNode != NULL)
    return leftTreapNode;
  if (rightTreapNode != NULL)
    return rightTreapNode;
  
  return NULL;
}
/**
 * Rotate right function for inserting a node into Treap
 */
TreapNode* Treap::rotate_right(TreapNode* node)
{
  // Adjust pointers to rotate the given node right in the Treap 
  TreapNode *newNode1 = node->left;
  TreapNode *newNode2 = newNode1->right;
  newNode1->right = node;
  node->left = newNode2;
  return newNode1;
}
/**
 * Rotate left function for inserting a node into Treap
 */
TreapNode* Treap::rotate_left(TreapNode* node)
{
  // Adjust pointers to rotate the given node left in the Treap 
  TreapNode *newNode1 = node->right;
  TreapNode *newNode2 = newNode1->left;
  newNode1->left = node;
  node->right = newNode2;
  return newNode1;
}
/**
 * insert function which takes in a key and value and inserts and TreapNode with those values into the Treap.
 * The inserted TreapNode is rotated to maintain binary search tree and heap order property
 */
void Treap::insert(const string& key, int value)
{
  Treap::insert_helper(key, value, root);
}

/**
 * insert helper function; Returns the TreapNode inserted.
 * 
 */
TreapNode* Treap::insert_helper(const string& key, int value, TreapNode*& node)
{
  // Create a new TreapNode
  if (node == NULL) {
    TreapNode *newTreapNode = new TreapNode(value, key);
    if (root == NULL) 
      root = newTreapNode;
    return newTreapNode;
  }
  // Maintains order based on TreapNode value
  if (value <= node->value) {
    // Recursive call to insert a TreapNode to the left of the treap, which reaches the end of the left branch
    node->left = Treap::insert_helper(key, value, node->left);
    // Treap is built based on TreapNode priority, which is randomly assigned.
    if (node->left->priority < node->priority)
      node = Treap::rotate_right(node);
  }
  else {
    // Recursive call to insert a TreapNode to the right of the treap, which reaches the end of the right branch
    node->right = Treap::insert_helper(key, value, node->right);
    // Treap is built based on TreapNode priority, which is randomly assigned.
    if (node->right->priority < node->priority)
      node = Treap::rotate_left(node);
  }
  return node; 
}
/**
 * Function to print the Treap for testing purposes
 */
void Treap::printTreapHelper(TreapNode *&root, int depth)
{
  if (root == NULL)
    return;
  Treap::printTreapHelper(root->right, depth+1);
  cout << setw(7 * depth) << "";
  cout << root->key << "(" << root->priority << ")" << endl;
  Treap::printTreapHelper(root->left, depth + 1);
}

void Treap::printTreap(TreapNode *&root)
{
  cout << "------------------------------------------------------------Printing Treap------------------------------------------------------------ " << endl;
  cout << endl;
  Treap::printTreapHelper(root, 0);
}
