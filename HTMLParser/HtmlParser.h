#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <fstream>

#include "./HtmlElement.h"
#include "../DataStructure/src/Stack.cpp"
#include "../DataStructure/src/String.cpp"
#include "../DataStructure/src/Queue.cpp"

#define NORMAL_BLOCK 1
#define NORMAL_INLINE 2
#define SPECIAL_BLOCK 3
#define SPECIAL_INLINE 4
#define CONTENT "CONTENT"
#define COMMENT "COMMENT"
#define JAVASCRIPT "JAVASCRIPT"
#define CSS "CSS"
#define NONE "NONE"

using std::cout;
using std::endl;

class HtmlParser {
private:
  HtmlElem *root;
  string doc;

  HtmlElem *isComment(int i);

  HtmlElem *isJavaScript(int i);

  HtmlElem *isCSS(int i);

  int isSelfClosing(const string &tag);

  int isInline(const string &tag);

  HtmlElem *parseTag(int i);

  bool checkNested(HtmlElem *child);

  HtmlElem *parseContent(int i);

  void parseHtml();

  map<string, string> parseAttribute(const string &attr);

public:
  HtmlParser(){};

  HtmlParser(string s) { this->doc = strip(s);};

  void init();

  void ReadHTML(string &html);

  void ReadFile(const string &filename);

  string showSub(HtmlElem *const root);

  string show(HtmlElem *const root);

  string showText(HtmlElem *const root);

  string OutHTML(const string &s);

  string Text(const string &s);

  void debug(HtmlElem *ele);

  HtmlElem *getRoot();

  string getDoc();
};

#endif