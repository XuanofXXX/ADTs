#ifndef CSSSELECTOR_CPP
#define CSSSELECTOR_CPP

#include "./CssSelector.h"
#include "CssSelector.h"

bool CssSelector::matchTag(HtmlElem *element, const string &tagName) {
  if (element == nullptr)
    return false;
  if (element->tag == tagName)
    return true;
  return false;
}

bool CssSelector::matchClass(HtmlElem *element, const string &className) {
  if (element == nullptr)
    return false;
  List<string> classes = split(element->attrs["class"], ' ');
  for (int i = 0; i < classes.size(); i++) {
    if (classes[i] == className)
      return true;
  }
  return false;
}

bool CssSelector::matchID(HtmlElem *element, const string &idName) {
  if (element == nullptr)
    return false;
  if (element->attrs["id"] == idName)
    return true;
  return false;
}

bool CssSelector::matchAttribute(HtmlElem *element, const string &attributeName,
                                 const string &attributeValue) {
  if (element == nullptr)
    return false;
  auto it = element->attrs.find(attributeName);
  if (it != element->attrs.end()) {
    if (attributeValue == "" || it->second == attributeValue)
      return true;
  }
  return false;
}

SelectorInfo CssSelector::parseSimpleSelector(const string &simple_part) {
  SelectorInfo info;
  SelectorPart part;

  bool inClass = false, inID = false, inAttr = false, inAttrValue = false,
       inAttrName = false;

  string attrName = "", attrValue = "", className = "", tagName = "";

  for (int i = 0; i < simple_part.size(); i++) {
    if (simple_part[i] == '.') {
      inClass = true;
      continue;
    } else if (simple_part[i] == '#') {
      inID = true;
      continue;
    } else if (simple_part[i] == '[') {
      inAttr = true;
      inAttrName = true;
      continue;
    }
    if (inClass) {
      if (simple_part[i] == '.' || simple_part[i] == '#' ||
          simple_part[i] == ' ') {
        part.type = CLASS;
        part.value = className;
        info.parts.append(part);
        className = "";
        part = SelectorPart();
        inClass = false;
        if (simple_part[i] == '.')
          inClass = true;
      }
      className += simple_part[i];
    }
    if (inAttr) {
      if (simple_part[i] == '=') {
        inAttrName = false;
        inAttrValue = true;
        continue;
      }
      if (simple_part[i] == ']') {
        inAttr = false;
        inAttrName = false;
        inAttrValue = false;
        part.type = ATTRIBUTE;
        part.value = attrName;
        part.attributeValue = attrValue;
        info.parts.append(part);
        attrName = "";
        attrValue = "";
        part = SelectorPart();
        continue;
      }
      if (inAttrName) {
        attrName += simple_part[i];
      }
      if (inAttrValue) {
        attrValue += simple_part[i];
      }
    }
    if (inID) {
      if (simple_part[i] == '.' || simple_part[i] == '#' ||
          simple_part[i] == ' ') {
        part.type = ID;
        part.value = tagName;
        info.parts.append(part);
        tagName = "";
        part = SelectorPart();
        inID = false;
      }
      tagName += simple_part[i];
    }
  }
  if (part.type == CSS_NONE)
    info.parts.append(part);
  return info;
}

void CssSelector::parseSelector(const string &selector) {
  parsedSelector; // 使用列表存储解析后的选择器部分
  int begin_index = 0;
  int end_index = 0;
  for (int i = 0; i < selector.size(); i++) {
    SelectorInfo info;
    if (selector[i] == ' ') {
      info.type = DESCENDANT;
    } else if (selector[i] == '>') {
      info.type = CHILD;
    } else if (selector[i] == ',') {
      info.type = GROUP;
    } else if (selector[i] == '~') {
      info.type = BROTHER;
    } else if (selector[i] == '+') {
      info.type = FIRST_CHILD;
    } else {
      end_index = i;
    }
    if (info.type != CSS_NONE) {
      parsedSelector.append(info);
      info = SelectorInfo(parseSimpleSelector(
          selector.substr(begin_index, end_index - begin_index)));
      begin_index = i + 1;
      parsedSelector.append(info);
    }
  }
  if (begin_index < selector.size()) {
    parsedSelector.append(SelectorInfo(parseSimpleSelector(
        selector.substr(begin_index, selector.size() - begin_index))));
  }
}

#endif
