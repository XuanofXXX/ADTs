#pragma once

#include "HtmlParser.h"

class HtmlParser
{
private:
  HtmlElem* root;
  string doc;


  HtmlElem* isComment(const string& s, int i){
    /**
     * \@brief 
     * \@param: s: string
     * \@param: i: index of the '<'
     * \@return: return the position of Annotation '>', if not Annotation, return i;
     */
    HtmlElem* res = new HtmlElem();
    res->tag = "NONE";
    if (s[i+1] == '!' && s[i+2] == '-' && s[i+3] == '-')
    {
      res->tag = "COMMENT";
      string comment = "";
      for (int j = i+4; j+2 < s.size(); j++){
        if (s[j] == '-' && s[j+1] == '-' && s[j+2] == '>'){
          res->attribute = comment;
          res->start_index = i;
          res->end_index = j+2;
          return res;
        }
        comment += s[j];
      }
    }
    return res;
  }

  HtmlElem* isJavaScript(const string&s, int i){
  /**
   * @brief Determine whether the tag is a JavaScript or not
   * @param s: string
   * @param i: index of the '<'
   * @return : return the position of JavaScript '>', if not JavaScript, return i;
  */
    HtmlElem* res = new HtmlElem();
    res->tag = "NONE";
    if (s[i+1] == 's' && s[i+2] == 'c' && s[i+3] == 'r' && s[i+4] == 'i' && s[i+5] == 'p' && s[i+6] == 't')
    {
      res->tag = "SCRIPT";
      string script = "";
      for (int j = i+7; j+8 < s.size(); j++){
        if (s[j] == '<' && s[j+1] == '/' && s[j+2] == 's' && s[j+3] == 'c' && s[j+4] == 'r' && s[j+5] == 'i' && s[j+6] == 'p' && s[j+7] == 't' && s[j+8] == '>'){
          res->attribute = script;
          res->start_index = i;
          res->end_index = j+8;
          return res;
        }
        script += s[j];
      }
    }
    return res;
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
    for (size_t i = 0; i < 16; i++)
    { 
      if (s == self_closing_tags[i]){
        return 1;
      }
    }

    for (size_t i = 0; i < 93; i++)
    {
      if (s == non_self_closing_tags[i]){
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
    }
    
    HtmlElem* temp = isComment(s, i);
    if (temp->tag != "NONE"){
      return temp;
    }

    temp = isJavaScript(s,i);
    if (temp->tag != "NONE"){
      return temp;
    }
    
    Stack<char> st;
    string attribute = "";
    string tagname = "";
    int index = i;
    
    for (int j = index+1; j < s.length(); j++) // Get Tag Name
    {
      if (s[j] == ' ' or s[j] == '>'){
        // cout << "tagname finish:" << s[j];
        index = j;
        res->tag = tagname;
        break;
      }
      tagname += s[j];
    }
    
    for (int j = index; j < s.size(); j++)
    {
      if (s[j] == '"'){     // class=""
        if (st.empty()){
          st.push('"');
        }else{
          st.pop();
        }
      }
      
      if (st.empty() and s[j] == '>'){  // End of Tag
        res->attribute = attribute;
        res->end_index = j;
        break;
      }

      attribute += s[j];    
    }

    if (isSelfClosing(res->tag) == 1){   // Self Closing Tag
      res->selfClosing = true;
    }
    return res;
  }

  HtmlElem* parseContent(const string& s, int i){
    HtmlElem* res = new HtmlElem();
    res->start_index = i;
    res->tag = "CONTENT";

    string content = "";

    int index = i;

    for(index; index < s.size(); index++){
      if (s[index] == '<'){
        res->end_index = index-1;
        break;
      }
      // else if (s[index] == '\n'){
      //   content += ' ';
      // }else if (s[index] == '\t'){
      //   continue;
      // }else{
      //   content += s[index];
      // }
      content += s[index];
    }

    content = strip(content);
    res->attribute = mergeSpaces(content);
    return res;
  }

  void parseHtml(const string& doc){
    /**
     * @brief Parse the whole HTML file
     * @param doc: string
     * @return : void
     */
    Stack<HtmlElem*> nodeStack;
    HtmlElem* dummyRoot = new HtmlElem;
    dummyRoot->tag = "ROOT";
    nodeStack.push(dummyRoot);

    int index = 0;
    
    while (!nodeStack.empty() && index +1 < doc.length()){
      HtmlElem* cur = nodeStack.top();

      if (doc[index] == '<'){
        HtmlElem* newEle = parseTag(doc, index);  // <node>

        if (newEle->endTag){  // </node>
          string endtag = newEle->tag.substr(1, newEle->tag.length()-1);
          if (endtag == cur->tag){
            nodeStack.pop();
            cur = nodeStack.top();
            cur->children.append(newEle);
            index = newEle->end_index+1;
            // cur->children.append(newEle);
            // index = newEle->end_index;
            // nodeStack.pop();
            continue;
          }
          else{   // parse error
            // TODO: More Robust
            this->root = nullptr;
          }
        }

        if (! newEle->selfClosing && newEle->tag != "COMMENT" && newEle->tag != "SCRIPT"){  // normal node
          nodeStack.push(newEle);
        }
        cur->children.append(newEle);
        index = newEle->end_index+1;
      }
      else{
        HtmlElem* newEle = parseContent(doc, index);  // content
        if (newEle->attribute != ""){
          cur->children.append(newEle);
        }
        index = newEle->end_index+1;
      }

    }
    this->root = dummyRoot;
  }

public:
  HtmlParser() {};

  void init(){
    parseHtml(this->doc);
  }

  void ReadHTML(string& html){
    this->doc = html;
  }

  void readFile(const string& filename){
  /**
   * @brief Reading a file using its filename
   */
    std::fstream file(filename);
    if (!file) {
      std::cerr << "Cannot open file!" << std::endl;
      exit(1);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    string s = buffer.str();
    this->doc = s;
    return ;
  }

  string showSub(HtmlElem* const root){
    string res = "";
    Stack<HtmlElem*> st;
    Stack<int> st_indent;
    st_indent.push(-1);
    st.push(root);
    while (!st.empty())
    {
      HtmlElem* cur = st.top();
      st.pop();
      int num = st_indent.top();
      st_indent.pop();
      if (cur->tag == "COMMENT" or cur->tag == "SCRIPT") continue;
      for (int i = 0; i < num; i++)
      {
        res += '\t';
      }
      if (cur->tag == "CONTENT") res += cur->attribute + '\n';
      else if (cur == root);
      else {
        if (cur->selfClosing == true){
          res += "<" + cur->tag + cur->attribute + ">\n";
        }else{
          res += "<" + cur->tag + cur->attribute + ">\n";
        }
      }

      for (int i = cur->children.size()-1; i >= 0; i--){
        st_indent.push(num+1);
        st.push(cur->children[i]);
      }
    }
    return res;
  }

  string show(HtmlElem* const root){
    string res = "";
    Stack<HtmlElem*> st;
    Stack<int> st_indent;
    string startTag = root->tag;
    st_indent.push(0);
    st.push(root);
    while (!st.empty())
    {
      HtmlElem* cur = st.top();
      st.pop();
      int num = st_indent.top();
      st_indent.pop();
      if (cur->tag == "COMMENT" or cur->tag == "SCRIPT") continue;
      for (int i = 0; i < num; i++)
      {
        res += '\t';
      }
      if (cur->tag == "CONTENT") res += cur->attribute + '\n';
      
      else {
        if (cur->selfClosing == true){
          res += "<" + cur->tag + cur->attribute + ">\n";
        }else{
          res += "<" + cur->tag + cur->attribute + ">\n";
        }
      }

      for (int i = cur->children.size()-1; i >= 0; i--){
        st_indent.push(num+1);
        st.push(cur->children[i]);
      }
    }
    res += "</" + startTag + ">\n";
    return res;
  }

  string showText(HtmlElem* const root){
    string res = "";
    Stack<HtmlElem*> st;
    st.push(root);
    while (!st.empty())
    {
      HtmlElem* cur = st.top();
      st.pop();
      if (cur->tag == "COMMENT" or cur->tag == "SCRIPT") continue;
      if (cur->tag == "CONTENT") {
        res += cur->attribute + '\n';
      }
      for (int i = cur->children.size()-1; i >= 0; i--){
        st.push(cur->children[i]);
      }
    }
    return res;
  }

  string OutHTML(const string& s){
    if (s == "/"){
      return showSub(root);
    }

    List<string> res;
    string tmp = "";
    for (int i = 0; i < s.size(); i++){
      if (s[i] == '/'){
        if (tmp == "") continue;
        tmp = toLowerCase(tmp);
        res.append(tmp);
        tmp = "";
      }
      else{
        tmp += s[i];
      }
    }
    res.append(tmp);
    HtmlElem* cur = root;
    Queue<HtmlElem*> qe;
    qe.enqueue(cur);
    
    for (int i = 0; i < res.size(); i++)
    {
      string node = res[i];
      bool found = false;
      int size = qe.getSize();
      for (int time = 0; time < size; time++)
      {
        cur = qe.peek();
        qe.dequeue();
        for (int j = 0; j < cur->children.size(); j++){
          HtmlElem* Node = cur->children[j];
          if (cur->children[j]->tag == node){
            found = true;
            qe.enqueue(cur->children[j]);
          }
        }
      }
      if (found == false) return "NONE";
    }
    string ans = "";
    while (!qe.empty())
    {
      cur = qe.peek();
      qe.dequeue();
      ans += show(cur);
    } 
    return ans;
  }

  string Text(const string& s){
  if (s == "/"){
    return showText(root);
  }

  List<string> res;
  string tmp = "";
  for (int i = 0; i < s.size(); i++){
    if (s[i] == '/'){
      if (tmp == "") continue;
      tmp = toLowerCase(tmp);
      res.append(tmp);
      tmp = "";
    }
    else{
      tmp += s[i];
    }
  }
  res.append(tmp);
  HtmlElem* cur = root;
  Queue<HtmlElem*> qe;
  qe.enqueue(cur);
  
  for (int i = 0; i < res.size(); i++)
  {
    string node = res[i];
    bool found = false;
    int size = qe.getSize();
    for (int time = 0; time < size; time++)
    {
      cur = qe.peek();
      qe.dequeue();
      for (int j = 0; j < cur->children.size(); j++){
        HtmlElem* Node = cur->children[j];
        if (cur->children[j]->tag == node){
          found = true;
          qe.enqueue(cur->children[j]);
        }
      }
    }
    if (found == false) return "NONE";
  }
  string ans = "";
  while (!qe.empty())
  {
    cur = qe.peek();
    qe.dequeue();
    ans += showText(cur);
  } 
  return ans;
}




  void debug(HtmlElem* ele){
    cout << "ele.tag: " << ele->tag << endl;
    cout << "ele.attribute: " << ele->attribute << endl;
    cout << "ele.start_index: " << ele->start_index << endl;
    cout << "ele.end_index: " << ele->end_index << endl;
    cout << "ele.selfClosing: " << ele->selfClosing << endl;
    cout << "ele.endTag: " << ele->endTag << endl;
    cout << "ele.children.size(): " << ele->children.size() << endl;
    cout << endl;
  }

  HtmlElem* getRoot(){
    return this->root;
  }

  string getDoc(){
    return this->doc;
  }




};


