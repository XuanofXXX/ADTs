#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include "../DataStructure/src/List.cpp"
#include <map>
#include <string>

#define NORMAL_BLOCK 1
#define NORMAL_INLINE 2
#define SPECIAL_BLOCK 3
#define SPECIAL_INLINE 4

#define CONTENT "CONTENT"
#define COMMENT "COMMENT"
#define JAVASCRIPT "JAVASCRIPT"
#define CSS "CSS"
#define NONE "NONE"

using std::map;
using std::string;

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