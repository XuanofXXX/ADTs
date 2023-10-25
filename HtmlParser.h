#pragma once

#include<string>
#include <fstream>
#include <regex>

#include "DataStructure/src/List.cpp"
#include "DataStructure/src/Stack.cpp"
#include "DataStructure/src/Queue.cpp"
#include "DataStructure/src/Pair.cpp"
#include "DataStructure/src/String.cpp"


using std::string;
using std::cout;
using std::endl;
/**
 * TODO: Add comments
 * TODO: Path:  
 * xTODO: Ignore comment, CSS, script;
 * TODO: Remove spare blanks
 * TODO: URL.parser 
 */


class HtmlElem{
public:    
  string tag; 
  string attribute;
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
// TODO: Case sensitive


string readFile(const string& filename);

HtmlElem* parseComment(const string& s, int i);

int isSelfClosing(const string& s);// * @return : 1 if it is a closing tag, 0 if it is a self-closing tag, -1 if it is 

HtmlElem* parseTag(const string& s, int i);

HtmlElem* parseContent(const string& s, int i);

HtmlElem* parseHtml(const string& s);

// HtmlElem* show();