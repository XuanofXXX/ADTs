#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include "../DataStructure/src/LinkedList.cpp"
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
  string tag = "";
  string attribute = "";
  map<string, string> attrs;
  HtmlElem* father = nullptr;
  HtmlElem* brother = nullptr;
  int fatherType = -1;
  int SelfType = -1;
  bool selfClosing = false;
  bool endTag = false;
  int start_index = -1;
  int end_index = -1;

  LinkList<HtmlElem *> children;

  HtmlElem(){};

  HtmlElem(string tag) { this->tag = tag; }

  HtmlElem(string tag, string attribute) {
    this->tag = tag;
    this->attribute = attribute;
  }

  void append(HtmlElem *other) { children.append(other); }
};

#endif