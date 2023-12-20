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

    // 测试插入二叉搜索树
    // BiTreeNode bstRoot{5};
    BiTreeNode bstRoot = node1;
    insertBiSearchTree(&bstRoot, 3);
    insertBiSearchTree(&bstRoot, 7);
    insertBiSearchTree(&bstRoot, 2);
    insertBiSearchTree(&bstRoot, 4);
    insertBiSearchTree(&bstRoot, 6);
    insertBiSearchTree(&bstRoot, 8);

    // 验证插入结果
    // result.clear();
    InOrderTraverse_recursion(&bstRoot, visit);
    cout << endl;
    // assert((result == std::vector<int>{2, 3, 4, 5, 6, 7, 8}));

    return 0;
}