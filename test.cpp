#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cctype>
#include <curl/curl.h>

// #include "include/lab2.h"
#include "./DataStructure/src/List.cpp"
#include "./DataStructure/src/Stack.cpp"
#include "HtmlParser.cpp"

using namespace std;




int main() {
  HtmlParser parser;
  parser.ReadFile("./Test/实验02_case13.html");
  parser.init();
  string s;
  cin >> s;
  cout << parser.OutHTML(s) << endl;
  // cout << parser.Text("") << endl;
  return 0;
}
