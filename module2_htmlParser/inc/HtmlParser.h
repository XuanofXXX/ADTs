#pragma once

#include<string>
#include <fstream>
#include <regex>

#include "../src/List.cpp"
#include "../src/Stack.cpp"
#include "../src/Pair.cpp"

using std::string;

class HtmlElem{
public:    
  string tag;
  string attribute;
  bool selfClosing = false;
  bool endTag = false;
  int start_index;
  int end_index;

  List<HtmlElem*> children;

  HtmlElem(){};
  HtmlElem(string tag){
    this->tag = tag;
  }
  HtmlElem(string tag, string attribute){
    this->tag = tag;
    this->attribute = attribute;
  }

  void append(HtmlElem* other){
    children.append(other);
  }
};


string readFile(const string& filename);

int isSelfClosing(const string& s);// * @return : 1 if it is a closing tag, 0 if it is a self-closing tag, -1 if it is 

HtmlElem* parseTag(const string& s, int i);

HtmlElem* parseContent(const string& s, int i);

HtmlElem* parseHtml(const string& s);

string getTag(const string& s ,int i);