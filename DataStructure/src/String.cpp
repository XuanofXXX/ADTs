#include <iostream>
#include <cstring>

class String {
private:
  char* str;
  int len;
public:

  String(const char* s = "") {
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
  }

  String(const String& s) {
    len = s.len;
    str = new char[len + 1];
    std::strcpy(str, s.str);
  }

  ~String() {
    delete[] str;
  }

  int length() const {
    return len;
  }

  String operator+(const String& s) const {
    char* res = new char[len + s.len + 1];
    std::strcpy(res, str);
    std::strcat(res, s.str);
    String result(res);
    delete[] res;
    return result;
  }

  String operator+=(const String& s) {
    char* res = new char[len + s.len + 1];
    std::strcpy(res, str);
    std::strcat(res, s.str);
    delete[] str;
    str = res;
    len += s.len;
    return *this;
  }

  String operator=(const String& s) {
    if (this == &s) {
      return *this;
    }
    delete[] str;
    len = s.len;
    str = new char[len + 1];
    std::strcpy(str, s.str);
    return *this;
  }

  bool operator==(const String& s) const {
    return std::strcmp(str, s.str) == 0;
  }

  bool operator!=(const String& s) const {
    return std::strcmp(str, s.str) != 0;
  }

  bool operator<(const String& s) const {
    return std::strcmp(str, s.str) < 0;
  }

  bool operator>(const String& s) const {
    return std::strcmp(str, s.str) > 0;
  }

  bool operator<=(const String& s) const {
    return std::strcmp(str, s.str) <= 0;
  }

  bool operator>=(const String& s) const {
    return std::strcmp(str, s.str) >= 0;
  }

  char operator[](int i) const {
    if (i < 0 || i >= len) {
      std::cerr << "Index out of range" << std::endl;
      return '\0';
    }
    return str[i];
  }

  // Write a operation +=
  void operator+=(const char* s) {
    char* res = new char[len + std::strlen(s) + 1];
    std::strcpy(res, str);
    std::strcat(res, s);
    delete[] str;
    str = res;
    len += std::strlen(s);
  }

  void operator+=(const char s) {
    char* res = new char[len + std::strlen(&s) + 1];
    std::strcpy(res, str);
    std::strcat(res, &s);
    delete[] str;
    str = res;
    len += std::strlen(&s);
  }
  String substr(int start, int length) const {
    if (start < 0 || start >= len || length < 0 || start + length > len) {
      std::cerr << "Invalid substring" << std::endl;
      return String();
    }
    char* res = new char[length + 1];
    std::strncpy(res, str + start, length);
    res[length] = '\0';
    String result(res);
    delete[] res;
    return result;
  }

  const char* c_str() const {
    return str;
  }
};
