#ifndef CSSSELECTER_H
#define CSSSELECTER_H

#include "HtmlElement.h"
#include "HtmlParser.h"
#include <fstream>
#include <iostream>
enum Type { TAG, CLASS, ID, ATTRIBUTE, DESCENDANT, GROUP, CHILD, BROTHER, FIRST_CHILD, CSS_NONE };

struct SelectorPart {
  Type type = CSS_NONE;
  string value;
  string attributeValue; // 仅当 type == ATTRIBUTE 时使用
  SelectorPart(): type(CSS_NONE)  {}
  SelectorPart(Type type, string value) : type(type), value(value) {}
};

struct SelectorInfo {
  Type type = CSS_NONE;
  List<SelectorPart> parts; // 存储选择器的各个部分
  SelectorInfo(): type(CSS_NONE){}
  SelectorInfo(List<SelectorPart> parts) : parts(parts) {}
  SelectorInfo(Type type) : type(type) {}
};

class CssSelector {
public:
  void parseSelector(const string &selector);

  List<HtmlElem *> matchElements(HtmlElem *root);

private:
  // 解析器辅助函数
  SelectorInfo parseSimpleSelector(const string &selectorPart);
  
  // 匹配器辅助函数
  bool matchTag(HtmlElem *element, const string &tagName);
  bool matchClass(HtmlElem *element, const string &className);
  bool matchID(HtmlElem *element, const string &idName);
  bool matchAttribute(HtmlElem *element, const string &attributeName,
                      const string &attributeValue);

  // 存储解析后的选择器信息
  List<SelectorInfo> parsedSelector;

};
#endif