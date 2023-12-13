#include <cassert>
#include <vector>
#include "BiTree.cpp"

int main() {
    // 创建一个简单的二叉树
    BiTreeNode node1{1}, node2{2}, node3{3}, node4{4}, node5{5};
    node1.lchild = &node2;
    node1.rchild = &node3;
    node2.lchild = &node4;
    node2.rchild = &node5;

    PreOrderTraverse_recursion(&node1, visit);
    cout << endl;
    // assert((result == std::vector<int>{1, 2, 4, 5, 3}));

    // result.clear();
    PreOrderTraverse_iteration(&node1, visit);
    cout << endl;
    // assert((result == std::vector<int>{1, 2, 4, 5, 3}));

    // 测试中序遍历
    // result.clear();
    InOrderTraverse_recursion(&node1, visit);
    cout << endl;
    // assert((result == std::vector<int>{4, 2, 5, 1, 3}));

    // result.clear();
    InOrderTraverse_iteration(&node1, visit);
    cout << endl;
    // assert((result == std::vector<int>{4, 2, 5, 1, 3}));

    // 测试后序遍历
    // result.clear();
    PostOrderTraverse_recursion(&node1, visit);
    cout << endl;
    // assert((result == std::vector<int>{4, 5, 2, 3, 1}));

    // result.clear();
    PostOrderTraverse_iteration(&node1, visit);
    cout << endl;
    // assert((result == std::vector<int>{4, 5, 2, 3, 1}));
    return 0;
}