#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include "../DataStructure/src/List.cpp"
#include <string>
#include <map>

using std::string;
using std::map;

class HtmlElem {
public:
  string tag;
  string attribute;
  map<string, string> attrs;
  int FatherType;
  int SelfType;
  bool selfClosing = false;
  bool endTag = false;
  int start_index;
  int end_index;

  List<HtmlElem *> children;

  HtmlElem(){};

  HtmlElem(string tag) { this->tag = tag; }

  HtmlElem(string tag, string attribute) {
    this->tag = tag;
    this->attribute = attribute;
  }

  void append(HtmlElem *other) { children.append(other); }
};

#endif