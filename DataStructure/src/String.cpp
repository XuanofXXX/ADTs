#ifndef STRING_CPP
#define STRING_CPP

#include "List.cpp"
#include <cstring>
#include <iostream>
#include <string>

using std::string;

List<string> split(const string &s, char ch) {
  List<string> res;
  string tmp = "";
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == ch) {
      res.append(tmp);
      tmp = "";
    } else {
      tmp += s[i];
    }
  }
  res.append(tmp);
  return res;
}

std::string strip(const std::string &str) {
  /**
   * @brief This function removes all leading and trailing whitespace characters
   * from the given string.
   *
   * @return Another string. It doesn't change the original string.
   */
  std::string whitespace = " \t\n\r\f\v";
  std::size_t start = str.find_first_not_of(whitespace);
  std::size_t end = str.find_last_not_of(whitespace);

  if (start == std::string::npos) { // 如果全部都是空白字符
    return "";
  }

  return str.substr(start, end - start + 1);
}

string cleanAndReduceWhitespace(const string &input) {
  string result;
  bool lastWasSpace = false;

  for (char c : input) {
    // 检查字符是否为空格或其他特定字符
    if (c == ' ' || c == '\r' || c == '\n' || c == '\t') {
      if (!lastWasSpace) { // 如果上一个字符不是空格，则添加一个空格到结果中
        result += ' ';
        lastWasSpace = true;
      }
    } else {
      result += c;
      lastWasSpace = false;
    }
  }

  return result;
}

string toLowerCase(const string &input) {
  string result = input;
  for (char &c : result) {
    if (isalpha(c) && isupper(c)) {
      c = tolower(c);
    }
  }
  return result;
}

string mergeSpaces(const string &input) {
  string result;
  bool lastWasSpace = false;

  for (char c : input) {
    if (c == ' ') {
      if (!lastWasSpace) {
        result.push_back(c);
      }
      lastWasSpace = true;
    } else {
      result.push_back(c);
      lastWasSpace = false;
    }
  }

  return result;
}
#endif