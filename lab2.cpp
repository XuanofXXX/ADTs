#include <iostream>
#include <fstream>
#include <string>
#include <regex>

// #include "include/lab2.h"
#include "./DataStructure/src/List.cpp"
#include "./DataStructure/src/Stack.cpp"
#include "HtmlParser.cpp"

using namespace std;

int main(){
  string doc = readFile("./Test/实验02_case00.html");
  cout << doc << endl;

  
  return 0;
}