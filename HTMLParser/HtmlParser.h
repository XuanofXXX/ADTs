#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <fstream>

#include "./HtmlElement.h"
#include "../DataStructure/src/Stack.cpp"
#include "../DataStructure/src/String.cpp"
#include "../DataStructure/src/Queue.cpp"

using std::cout;
using std::endl;

class HtmlParser {
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

  List<HtmlElem*> CssSelect(const string &s, HtmlElem *root);

  // List<HtmlElem*> XPathSelect(const string& path);

  void debug(HtmlElem *ele);

  HtmlElem *getRoot();

  string getDoc();
  
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
};

#endif