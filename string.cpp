#include <iostream>

class String {
public:
  String() {}
  String(const wchar_t* str) {
    int len = wcslen(str);
    data = new wchar_t[len + 1];
    wcscpy(data, str);
  }

  ~String() {
    delete[] data;
  }

  void append(const wchar_t* str) {
    int len1 = wcslen(data);
    int len2 = wcslen(str);
    wchar_t* newData = new wchar_t[len1 + len2 + 1];
    wcscpy(newData, data);
    wcscpy(newData + len1, str);
    delete[] data;
    data = newData;
  }

  const wchar_t* getData() const {
    return data;
  }

private:
    wchar_t* data = nullptr;
};

int main() {
  // Test default constructor
  String s1;
  assert(s1.getData() == nullptr);

  // Test constructor with string argument
  String s2(L"Hello");
  assert(wcscmp(s2.getData(), L"Hello") == 0);

  // Test append function
  s2.append(L", world!");
  assert(wcscmp(s2.getData(), L"Hello, world!") == 0);

  // Test destructor
  {
    String s3(L"Goodbye");
  } // s3 should be destroyed here

  // Test empty string
  String s4(L"");
  assert(s4.getData() != nullptr && wcscmp(s4.getData(), L"") == 0);
  std::cout << s2 <<std::endl;
  std::cout << "All tests passed!\n";
  return 0;
}
// END: 9f8e7d4b2c3a

