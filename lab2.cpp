#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cctype>

// #include "include/lab2.h"
#include "./DataStructure/src/List.cpp"
#include "./DataStructure/src/Stack.cpp"
#include "HtmlParser.cpp"

using namespace std;

string OutHTML(HtmlElem* root, const string& s){
  if (s == "/"){
    return showSub(root);
  }

  List<string> res;
  string tmp = "";
  for (int i = 0; i < s.size(); i++){
    if (s[i] == '/'){
      if (tmp == "") continue;
      tmp = toLowerCase(tmp);
      res.append(tmp);
      tmp = "";
    }
    else{
      tmp += s[i];
    }
  }
  res.append(tmp);
  HtmlElem* cur = root;
  Queue<HtmlElem*> qe;
  qe.enqueue(cur);

  // ? good
  // for (int i = 0; i < res.size(); i++)
  // {
  //   cout << res[i] << endl;
  // }
  
  for (int i = 0; i < res.size(); i++)
  {
    string node = res[i];
    bool found = false;
    int size = qe.getSize();
    for (int time = 0; time < size; time++)
    {
      cur = qe.peek();
      qe.dequeue();
      for (int j = 0; j < cur->children.size(); j++){
        HtmlElem* Node = cur->children[j];
        if (cur->children[j]->tag == node){
          found = true;
          qe.enqueue(cur->children[j]);
        }
      }
    }
    if (found == false) return "NONE";
  }
  string ans = "";
  while (!qe.empty())
  {
    cur = qe.peek();
    qe.dequeue();
    ans += show(cur);
  } 
  return ans;
}

string Text(HtmlElem* root, const string& s){
  if (s == "/"){
    return showText(root);
  }

  List<string> res;
  string tmp = "";
  for (int i = 0; i < s.size(); i++){
    if (s[i] == '/'){
      if (tmp == "") continue;
      tmp = toLowerCase(tmp);
      res.append(tmp);
      tmp = "";
    }
    else{
      tmp += s[i];
    }
  }
  res.append(tmp);
  HtmlElem* cur = root;
  Queue<HtmlElem*> qe;
  qe.enqueue(cur);

  // ? good
  // for (int i = 0; i < res.size(); i++)
  // {
  //   cout << res[i] << endl;
  // }
  
  for (int i = 0; i < res.size(); i++)
  {
    string node = res[i];
    bool found = false;
    int size = qe.getSize();
    for (int time = 0; time < size; time++)
    {
      cur = qe.peek();
      qe.dequeue();
      for (int j = 0; j < cur->children.size(); j++){
        HtmlElem* Node = cur->children[j];
        if (cur->children[j]->tag == node){
          found = true;
          qe.enqueue(cur->children[j]);
        }
      }
    }
    if (found == false) return "NONE";
  }
  string ans = "";
  while (!qe.empty())
  {
    cur = qe.peek();
    qe.dequeue();
    ans += showText(cur);
  } 
  return ans;
}

int main(){
  string doc = readFile("./Test/实验02_case00.html");
  // cout << doc << endl;

  HtmlElem* root = new HtmlElem();
  // cout << doc.size();
  
  root = parseHtml(doc);
  if (root == nullptr){
    cout << "Illegal HTML file" << endl;
    return 0;
  }
  // cout << show(root) << endl;
  cout << showSub(root) << endl;
  // cout << show(root->children[0]) << endl;
  // cout << showSub(root->children[0]) << endl;
  // cout << endl;
  
  string path = "/";
  // cout << showText(root) << endl;
  
  return 0;
}
