#include <iostream>
#include <fstream>
#include <string>
#include <regex>

// #include "include/lab2.h"
#include "../src/List.cpp"
#include "../src/Stack.cpp"
#include "../src/HtmlParser.cpp"

using namespace std;

struct TreeNode{
  HtmlElem data;
  List<TreeNode*> children;
  TreeNode(): data(), children(){}
  TreeNode(HtmlElem data){
    this->data = data;
  }
}; 



int main(){

  return 0;
}