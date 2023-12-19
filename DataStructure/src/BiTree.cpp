#include <iostream>
#include <stack>
#define T int

using std::stack, std::cout, std::endl;

struct BiTreeNode {
  T data;
  BiTreeNode *lchild = nullptr, *rchild = nullptr;
};

void visit(T data) { cout << data; }

void PreOrderTraverse_iteration(BiTreeNode *root, void (*visit)(T)) {
  if (root == nullptr)
    return;
  stack<BiTreeNode *> st;
  st.push(root);
  while (!st.empty()) {
    BiTreeNode *cur = st.top();
    st.pop();
    visit(cur->data);
    if (cur->rchild != nullptr) {
      st.push(cur->rchild);
    }
    if (cur->lchild != nullptr) {
      st.push(cur->lchild);
    }
  }
}

void PreOrderTraverse_recursion(BiTreeNode *root, void (*visit)(T)) {
  if (root == nullptr)
    return;
  visit(root->data);
  PreOrderTraverse_recursion(root->lchild, visit);
  PreOrderTraverse_recursion(root->rchild, visit);
}

void InOrderTraverse_iteration(BiTreeNode *root, void (*visit)(T)) {
  if (root == nullptr) {
    return;
  }
  stack<BiTreeNode *> st;
  BiTreeNode *cur = root;
  while (!st.empty() || cur) {
    while (cur) {
      st.push(cur);
      cur = cur->lchild;
    }

    cur = st.top();
    st.pop();
    visit(cur->data);

    cur = cur->rchild;
  }
}

void InOrderTraverse_recursion(BiTreeNode *root, void (*visit)(T)) {
  if (root == nullptr) {
    return;
  }
  InOrderTraverse_recursion(root->lchild, visit);
  visit(root->data);
  InOrderTraverse_recursion(root->rchild, visit);
}

void PostOrderTraverse_iteration(BiTreeNode *root, void (*visit)(T)) {
  if (root == nullptr) {
    return;
  }
  stack<BiTreeNode *> s;
  BiTreeNode *lastVisited =nullptr;
  BiTreeNode *current = root;

  while (!s.empty() || current != NULL) {
    if (current != NULL) {
      s.push(current);
      current = current->lchild;
    } else {
      BiTreeNode *topNode = s.top();
      // 如果右子树存在且未被访问过
      if (topNode->rchild != NULL && lastVisited != topNode->rchild) {
        current = topNode->rchild;
      } else {
        visit(topNode->data);
        lastVisited = topNode;
        s.pop();
      }
    }
  }
}

void PostOrderTraverse_recursion(BiTreeNode *root, void (*visit)(T)) {
  if (root == nullptr) {
    return;
  }
  PostOrderTraverse_recursion(root->lchild, visit);
  PostOrderTraverse_recursion(root->rchild, visit);
  visit(root->data);
}

void insertBiSearchTree(BiTreeNode *root, T val){
  /**
   * @brief insert an element in a biSearchTree.
   * 
   */
  if (root == nullptr){
    return ;
  }
  BiTreeNode *cur = root;
  while (cur)
  {
    if (cur->data >= val){
      if (cur->lchild == nullptr){
        cur->lchild = new BiTreeNode;
        cur->lchild->data = val;
        return;
      }else{
        cur = cur->lchild;
      }
    }else{
      if(cur->rchild == nullptr){
        cur->rchild = new BiTreeNode;
        cur->rchild->data = val;
        return;
      }else{
        cur = cur->rchild;
      }
    }
  }
}