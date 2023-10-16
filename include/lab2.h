#pragma once

#include <iostream>
#include <string>

#include "../src/List.cpp"
#include "../src/Stack.cpp"

using namespace std;

struct HtmlElem{
  string tag;
  string tagContent;
  string text;
  bool isOpening;
  List<HtmlElem*> children;

  HtmlElem(): tag(), tagContent(), text(), isOpening(false), children(){}
  HtmlElem(string tag, string tagContent, string text): tag(tag), tagContent(tagContent), text(text), isOpening(false), children() {}

  HtmlElem(string tag, string tagContent, string text, bool isOpening){}
};


string readFile(const string& s, int i);

string removeHtmlComments(const string& input);
int isAnt(const string& s, int i);
HtmlElem* parseTag(const string& s, int i);

// List<HtmlElem> parseHtml(const string& s);


