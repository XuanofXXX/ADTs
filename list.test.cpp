#include <iostream>
#include "list.cpp"

int main() {
  List<wchar_t*> Mylist;
  Mylist.append(L"Hello");
  Mylist.append(L"World");
  Mylist.display(); // Output: Hello World

  Mylist.insert(1, L"Beautiful");
  Mylist.display(); // Output: Hello Beautiful World

  Mylist.remove(2);
  Mylist.display(); // Output: Hello Beautiful

  std::wcout << Mylist.pop() << std::endl; // Output: Beautiful
  Mylist.display(); // Output: Hello

  List<wchar_t*> Otherlist;
  Otherlist.append(L"World");
  Otherlist.append(L"Hello");
  std::wcout << Mylist.calcSimilarity(Otherlist) << std::endl; // Output: 0.5

  Mylist.reverse();
  Mylist.display(); // Output: olleH

  Mylist.extend(Otherlist);
  Mylist.display(); // Output: olleH World Hello

  Mylist.searchDiff(Otherlist); // Output: 1 2

  List<wchar_t*> ConcatenatedList = Mylist + Otherlist;
  ConcatenatedList.display(); // Output: olleH World Hello World Hello

  Mylist += Otherlist;
  Mylist.display(); // Output: olleH World Hello World Hello

  std::wcout << Mylist[0] << std::endl; // Output: olleH
  std::wcout << Mylist[-1] << std::endl; // Output: Hello

  return 0;
}