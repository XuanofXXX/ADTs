#pragma once

#include "HtmlParser.h"

string readFile(const string& filename){
  /**
   * @brief Reading a file using its filename
   */
  std::fstream file(filename);
  if (!file){
    std::cerr << "Cannot open file!" << std::endl;
    exit(1);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  return buffer.str();
}

HtmlElem* isAnt(const string& s, int i){
  /**
   * \@brief 
   * \@param: s: string
   * \@param: i: index of the '<'
   * \@return: return the position of Annotation '>', if not Annotation, return i;
   */
  HtmlElem* newElem = new HtmlElem();
  i++;
  if (i+6 >= s.length() ||
    !(s[i] == '!' && s[i+1] == '-' && s[i+2] == '-'))
  {
    newElem->tag = "NONE";
    return newElem;
  }
  for (int j = i+5; j < s.size(); j++){
    if (s[j-2] == '-' && s[j-1] == '-' && s[j] == '>'){
      newElem->tag = "COMMENT";
      newElem->start_index = i;
      newElem->end_index = j;
      return newElem;
    }
  }
}

int isSelfClosing(const string& s){
  /**
   * @brief Determine whether the tag is a closing tag or not
   * @param s: string
   * @return : 1 if it is a closing tag, 0 if it is a self-closing tag, -1 if it is 
   */
  string self_closing_tags[] = {
      "area", "base", "br", "col", "command", "embed", "hr", "img", 
      "input", "keygen", "link", "meta", "param", "source", "track", "wbr"
  };

  string non_self_closing_tags[] = {
      "a", "abbr", "acronym", "address", "article", "aside",
      "audio", "b", "bdi", "bdo", "blockquote", "body", "button", 
      "canvas", "caption", "cite", "code", "colgroup", "data", 
      "datalist", "dd", "del", "details", "dfn", "dialog", "div", 
      "dl", "dt", "em", "fieldset", "figcaption", "figure", "footer", 
      "form", "h1", "h2", "h3", "h4", "h5", "h6", "head", "header",
      "html", "i", "iframe", "ins", "kbd", "label", "legend", "li",
      "main", "map", "mark", "nav", "noscript", "object", "ol",
      "optgroup", "option", "output", "p", "picture", "pre", "progress",
      "q", "rp", "rt", "ruby", "s", "samp", "script", "section", "select",
      "small", "span", "strong", "style", "sub", "summary", "sup", 
      "table", "tbody", "td", "textarea", "tfoot", "th", "thead", 
      "time", "title", "tr", "ul", "var", "video"
  };
  for (size_t i = 0; i < non_self_closing_tags->length(); i++)
  {
    if (s == non_self_closing_tags[i]){
      return 1;
    }
  }
  for (size_t i = 0; i < self_closing_tags->length(); i++)
  {
    if (s == self_closing_tags[i]){
      return 0;
    }
  }
  return -1;
}

HtmlElem* parseTag(const string& s, int i) {
  /**
   * @brief Given a string and the index of "<". Return the HtmlElem with tagName and tagContent(if had)
   * @attention : Couldn't determine whether the tag is an annotation or not.
   * @param s: string
   * @param i: index of "<"
   * @return : Return the HtmlElem with tagName and Attr
   */
  HtmlElem* res = new HtmlElem();
  res->start_index = i;
  if (s[i+1] == '/'){  // Eng Tag </head>
    res->endTag= true;
    i++;
  }
  
  Stack<char> st;
  string attribute;
  string tagname = "";
  for (int j = i+1; j < s.length(); j++) // Get Tag Name
  {
    if (s[j] == ' ' or s[j] == '>'){
      i = j;
      res->tag = tagname;
    }
    tagname += s[j];
  }

  if (isSelfClosing(tagname) == 0){   // Self Closing Tag
    res->selfClosing = true;
    return res;
  }
  
  for (int j = i; j < s.size(); j++)
  {
    if (s[j] == '"'){     // class="f>f"
      if (st.empty()){
        st.push('"');
      }else{
        st.pop();
      }
    }
    
    if (st.empty() and s[j] == '>'){  // End of Tag
      res->attribute = attribute;
      res->end_index = j;
      return res;
    }
    attribute += s[j];    
  }
  return res;
}

HtmlElem* parseContent(const string& s, int i){
  HtmlElem* res = new HtmlElem();
  res->start_index = i;
  res->tag = "CONTENT";
  for (i; i < s.size(); i++)
  {
    if (s[i] == '<'){
      res->end_index = i-1;
      return res;
    }
    res->attribute += s[i];
  }
  return res;
}

// string removeHtmlComments(const string& input) {
//     std::regex commentPattern("<!--([\\s\\S]*?)-->");
//     return std::regex_replace(input, commentPattern, "");
// }

HtmlElem* parseHtml(const string& doc){
  Stack<HtmlElem*> nodeStack;
  HtmlElem* dummyRoot = new HtmlElem;
  dummyRoot->tag = "ROOT";
  nodeStack.push(dummyRoot);

  int index = 0;
  
  while (!nodeStack.empty()){
    HtmlElem* cur = nodeStack.top();

    if (doc[index] == '<'){
      HtmlElem* newEle = parseTag(doc, index);  // <node>

      if (newEle->endTag){  // </node>
        if (newEle->tag == cur->tag){
          cur->children.append(newEle);
          index = newEle->end_index;
          nodeStack.pop();
          break;
        }
        else{   // parse error
          // TODO: More Robust
          return nullptr;
        }
      }

      if (!newEle->selfClosing && newEle->tag != "COMMENT"){
        nodeStack.push(newEle);
        cur->children.append(newEle);
        index = newEle->end_index+1;
        break;
      }
      cur->children.append(newEle);
      index = newEle->end_index+1;
    }else{
      HtmlElem* newEle = parseContent(doc, index);
      cur->children.append(newEle);
      index = newEle->end_index+1;
    }

  }
  return dummyRoot;
}