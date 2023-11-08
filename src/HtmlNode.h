#pragma once

#include<string>

using std::string;

/**
 * @brief 
 * Every element can be described by HtmlElem, which inl
 * 
 */
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