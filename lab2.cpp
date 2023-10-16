#include <iostream>
#include <fstream>
#include <string>
#include <regex>

// #include "include/lab2.h"
#include "../src/List.cpp"
#include "../src/Stack.cpp"

using namespace std;

struct HtmlElem{
  string tag;
  string attribute;
  string text;
  // string type;
  bool isOpening;
  List<HtmlElem*> children;

  HtmlElem(): tag(), attribute(), text(), isOpening(false), children(){}
  HtmlElem(string tag, string attribute, string text): tag(tag), attribute(attribute), text(text), isOpening(false), children() {}

  HtmlElem(string tag, string tagContent, string text, bool isOpening){
    this->tag = tag;
    this->attribute = tagContent;
    this->text = text;
    this->isOpening = isOpening;
    this->children = List<HtmlElem*>();
  }
};

struct TreeNode{
  HtmlElem data;
  List<TreeNode*> children;
  TreeNode(): data(), children(){}
  TreeNode(HtmlElem data){
    this->data = data;
  }
}; 

int isAnt(const string& s, int i){
  /**
   * \@brief 
   * \@param: s: string
   * \@param: i: index of the '<'
   * \@return: return the position of Annotation '>', if not Annotation, return i;
   */
  i++;
  if (!(s[i] == '!' && s[i+1] == '-' && s[i+2] == '-')) return i;
  for (int j = i+3; j < s.size(); j++){
      if (s[j] == '-' && s[j+1] == '-' && s[j+2] == '>') return j+2;
  }
}

HtmlElem* parseTag(const string& s, int i) {
  /**
   * @brief Given a string and the index of "<". Return the HtmlElem with tagName and tagContent(if had)
   * @attention : Couldn't determine whether the tag is an annotation or not.
   * @param s: string
   * @param i: index of "<"
   * @return : Return the HtmlElem with tagName and Attr
   */
  HtmlElem* res;
  string tagContent;
  bool tagNaming = true;
  for (int j = i+1; j < s.size(); j++)
  {
    if (tagNaming){
      if (s[j] == ' '){
        res->tag = tagContent;
        tagNaming = false;
        tagContent = "";
      } else if (s[j] == '>'){
        res->tag = tagContent;
        return res;
      }else{
        tagContent += s[j];
      }
    }else{
      if (s[j] == '>'){
        res->attribute = tagContent;
        return res;
      }else{
        tagContent += s[j];
      }
    }
  }
}

string readFile(const string& filename){
  /**
   * @brief Reading a file using its filename
   */
  fstream file(filename);
  if (!file){
    cerr << "Cannot open file!" << endl;
    exit(1);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  return buffer.str();
}

string removeHtmlComments(const string& input) {
    std::regex commentPattern("<!--(.*?)-->", std::regex_constants::dotall);
    return std::regex_replace(input, commentPattern, "");
}

HtmlElem* parseHtml(const string doc){
  Stack<HtmlElem*> nodeStack;
  HtmlElem* dummyRoot = new HtmlElem;
  nodeStack.push(dummyRoot);

  bool inTag = false;
  string tagname;
  string tagContent;
  string text;  
  int index = 0;
  

  while (!nodeStack.empty()){
    HtmlElem* cur = nodeStack.top();
    nodeStack.pop();
    for (int i = index; i < doc.length(); i++){
      if (doc[i] == '<'){
        if (i <= doc.length() and doc[i+1] == '/'){  // </node>
          cur->isOpening = true;
          break;
        }
        
        HtmlElem* newEle = parseTag(doc, i);  // <node>
        cur->children.append(newEle);
        nodeStack.push(newEle);
      }
    }
    
  }

}

int main(){

  return 0;
}