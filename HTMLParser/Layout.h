#ifndef LAYOUT_H
#define LAYOUT_H

#include "HtmlParser.h"
#include "HtmlElement.h"

class Layout {
private:
  HtmlElem *root;
public:
  Layout();
  Layout(HtmlElem *root): root(root) {};

  string showSub(HtmlElem *const root);

  string show(HtmlElem *const root);

  string showText(HtmlElem *const root);

  string OutHTML(const string &s);

  string Text(HtmlElem *const root, const string &s);
  ~Layout();
};

Layout::Layout(/* args */) {}

Layout::~Layout() {
  delete root;
}

#endif