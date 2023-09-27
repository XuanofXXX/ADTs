#include <iostream>
#include "list.cpp"

int main() {
    // Test List class
    List<int> Mylist;
    for (int i = 0; i < 21; i++) {
        Mylist.append(i);
    }
    Mylist.display(); // Expected output: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
    std::cout << "pop: " << Mylist.pop() << ' ' << Mylist.pop() << std::endl; // Expected output: pop: 20 19
    Mylist.display(); // Expected output: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
    Mylist.insert(0, 999);
    Mylist.display(); // Expected output: 999 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
    Mylist.remove(2);
    Mylist.display(); // Expected output: 999 0 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
    std::cout << "Mylist[0]: " << Mylist[0] << std::endl; // Expected output: Mylist[0]: 999
    std::cout << "Mylist[-1]: " << Mylist[-1] << std::endl; // Expected output: Mylist[-1]: 18

    // Test LinkList class
    LinkList<int> MyLinkList;
    for (int i = 0; i < 5; i++) {
        MyLinkList.prepend(i);
    }
    MyLinkList.display(); // Expected output: 4 -> 3 -> 2 -> 1 -> 0 -> None
    MyLinkList.insert(2, 999);
    MyLinkList.display(); // Expected output: 4 -> 3 -> 999 -> 2 -> 1 -> 0 -> None
    MyLinkList.remove(3);
    MyLinkList.display(); // Expected output: 4 -> 3 -> 999 -> 1 -> 0 -> None
    std::cout << "MyLinkList.find(999): " << MyLinkList.find(999) << std::endl; // Expected output: MyLinkList.find(999): 1
    std::cout << "MyLinkList.find(888): " << MyLinkList.find(888) << std::endl; // Expected output: MyLinkList.find(888): 0
    MyLinkList.reverse();
    MyLinkList.display(); // Expected output: 0 -> 1 -> 999 -> 3 -> 4 -> None
    std::cout << "MyLinkList.count(999): " << MyLinkList.count(999) << std::endl; // Expected output: MyLinkList.count(999): 1
    std::cout << "MyLinkList.count(0): " << MyLinkList.count(0) << std::endl; // Expected output: MyLinkList.count(0): 1
    std::cout << "MyLinkList.judgeHuiwen(): " << MyLinkList.judgeHuiwen() << std::endl; // Expected output: MyLinkList.judgeHuiwen(): 0

    // Test operator overloading
    LinkList<int> MyLinkList1;
    for (int i = 0; i < 5; i++) {
        MyLinkList1.prepend(i);
    }
    LinkList<int> MyLinkList2;
    for (int i = 3; i < 8; i++) {
        MyLinkList2.prepend(i);
    }
    // LinkList<int> MyLinkList3 = MyLinkList1 + MyLinkList2;
    // MyLinkList3.display(); // Expected output: 4 -> 3 -> 2 -> 1 -> 0 -> 7 -> 6 -> 5 -> 4 -> 3 -> None
    // std::cout << MyLinkList3.size() << std::endl;
    MyLinkList1 += MyLinkList2;
    MyLinkList1.display(); // Expected output: 4 -> 3 -> 2 -> 1 -> 0 -> 7 -> 6 -> 5 -> 4 -> 3 -> None

    return 0;
}
// #include <iostream>
// #include "list.cpp"

// int main() {
//     LinkList<int> list1;
//     LinkList<int> list2;

//     // Test append and display
//     list1.append(1);
//     list1.append(2);
//     list1.append(3);
//     list1.display(); // Expected output: 1 2 3

//     // Test prepend and display
//     list2.prepend(3);
//     list2.prepend(2);
//     list2.prepend(1);
//     list2.display(); // Expected output: 1 2 3

//     // Test insert and display
//     list1.insert(2, 4);
//     list1.display(); // Expected output: 1 2 4 3

//     // Test remove and display
//     list2.remove(2);
//     list2.display(); // Expected output: 1 3

//     // Test reverse and display
//     list1.reverse();
//     list1.display(); // Expected output: 3 4 2 1

//     // Test count
//     std::cout << list1.count(2) << std::endl; // Expected output: 1

//     // Test find
//     std::cout << list2.find(2) << std::endl; // Expected output: 0
//     std::cout << list2.find(3) << std::endl; // Expected output: 1

//     // Test extend and display
//     list1.extend(list2);
//     list1.display(); // Expected output: 3 4 2 1 1 3

//     // Test calcSimilarity
//     std::cout << list1.calcSimilarity(list2) << std::endl; // Expected output: 0.285714

//     // Test clear and display
//     list1.clear();
//     list1.display(); // Expected output: 
// }