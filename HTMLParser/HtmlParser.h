#pragma once

#include<string>
#include <fstream>

#include "../DataStructure/src/List.cpp"
#include "../DataStructure/src/Stack.cpp"
#include "../DataStructure/src/Queue.cpp"
#include "../DataStructure/src/String.cpp"

#define NORMAL_BLOCK 1
#define NORMAL_INLINE 2
#define SPECIAL_BLOCK 3
#define SPECIAL_INLINE 4

using std::string;
using std::cout;
using std::endl;

class HtmlElem{
public:    
  string tag; 
  string attribute;
  int FatherType;
  int SelfType;
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

// class HtmlParser
// {
// private:
//   HtmlElem* root;
//   string doc;

//   HtmlElem* isComment(const string& s, int i);

//   HtmlElem* isJavaScript(const string&s, int i);

//   HtmlElem* isCSS(const string&s, int i);
  
//   int isSelfClosing(const string& s);

//   int isInline(const string& s);

//   HtmlElem* parseTag(const string& s, int i);

//   bool checkNested(HtmlElem* child);

//   HtmlElem* parseContent(const string& s, int i);

//   void parseHtml(const string& doc);

// public:
//   HtmlParser() {};
  
//   void init();

//   void ReadHTML(string& html);

//   void ReadFile(const string& filename);

//   string showSub(HtmlElem* const root);

//   string show(HtmlElem* const root);

//   string showText(HtmlElem* const root);

//   string OutHTML(const string& s);

//   string Text(const string& s);

//   void debug(HtmlElem* ele);

//   HtmlElem* getRoot();

//   string getDoc();
// };
