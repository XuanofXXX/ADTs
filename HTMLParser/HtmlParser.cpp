#include "./HtmlParser.h"

HtmlElem* HtmlParser::isComment(int i) {
  /**
   * \@brief
   * \@param: s: string
   * \@param: i: index of the '<'
   * \@return: return the position of Annotation '>', if not Annotation,
   * return i;
   */
  HtmlElem *res = new HtmlElem();
  res->tag = NONE;
  string comment = "";
  if (doc[i + 1] == '!' && doc[i + 2] == '-' && doc[i + 3] == '-') {
    res->tag = COMMENT;
    for (int j = i + 4; j + 2 < doc.size(); j++) {
      if (doc[j] == '-' && doc[j + 1] == '-' && doc[j + 2] == '>') {
        res->attribute = comment;
        res->start_index = i;
        res->end_index = j + 2;
        return res;
      }
      comment += doc[j];
    }
  }
  return res;
};

HtmlElem* HtmlParser::isJavaScript(int i) {
  /**
   * @brief Determine whether the tag is a JavaScript or not
   * @param s: string
   * @param i: index of the '<'
   * @return : return the position of JavaScript '>', if not JavaScript,
   * return i;
   */
  HtmlElem *res = new HtmlElem();
  res->tag = NONE;
  if (doc[i + 1] == 's' && doc[i + 2] == 'c' && doc[i + 3] == 'r' &&
      doc[i + 4] == 'i' && doc[i + 5] == 'p' && doc[i + 6] == 't') {
    res->tag = JAVASCRIPT;
    string script = "";
    for (int j = i + 7; j + 8 < doc.size(); j++) {
      if (doc[j] == '<' && doc[j + 1] == '/' && doc[j + 2] == 's' &&
          doc[j + 3] == 'c' && doc[j + 4] == 'r' && doc[j + 5] == 'i' &&
          doc[j + 6] == 'p' && doc[j + 7] == 't' && doc[j + 8] == '>') {
        res->attribute = script;
        res->start_index = i;
        res->end_index = j + 8;
        return res;
      }
      script += doc[j];
    }
  }
  return res;
}

HtmlElem * HtmlParser::isCSS(int i) {
  HtmlElem *res = new HtmlElem();
  res->tag = NONE;
  if (doc[i + 1] == 's' && doc[i + 2] == 't' && doc[i + 3] == 'y' &&
      doc[i + 4] == 'l' && doc[i + 5] == 'e') {
    res->tag = CSS;
    string script = "";
    for (int j = i + 6; j + 7 < doc.size(); j++) {
      if (doc[j] == '<' && doc[j + 1] == '/' && doc[j + 2] == 's' &&
          doc[j + 3] == 't' && doc[j + 4] == 'y' && doc[j + 5] == 'l' &&
          doc[j + 6] == 'e' && doc[j + 7] == '>') {
        res->attribute = script;
        res->start_index = i;
        res->end_index = j + 7;
        return res;
      }
      script += doc[j];
    }
  }
  return res;
}

int HtmlParser::isSelfClosing(const string &tag) {
  /**
   * @brief Determine whether the tag is a closing tag or not
   * @param s: string
   * @return : 1 if it is a closing tag, 0 if it is a self-closing tag, -1 if
   * it is
   */
  string self_closing_tags[] = {
      "area",  "base",   "br",    "col",    "command", "embed",
      "hr",    "img",    "input", "keygen", "link",    "meta",
      "param", "source", "track", "wbr",    "!DOCTYPE"};

  string non_self_closing_tags[] = {
      "a",          "abbr",     "acronym", "address",  "article",    "aside",
      "audio",      "b",        "bdi",     "bdo",      "blockquote", "body",
      "button",     "canvas",   "caption", "cite",     "code",       "colgroup",
      "data",       "datalist", "dd",      "del",      "details",    "dfn",
      "dialog",     "div",      "dl",      "dt",       "em",         "fieldset",
      "figcaption", "figure",   "footer",  "form",     "h1",         "h2",
      "h3",         "h4",       "h5",      "h6",       "head",       "header",
      "html",       "i",        "iframe",  "ins",      "kbd",        "label",
      "legend",     "li",       "main",    "map",      "mark",       "nav",
      "noscript",   "object",   "ol",      "optgroup", "option",     "output",
      "p",          "picture",  "pre",     "progress", "q",          "rp",
      "rt",         "ruby",     "s",       "samp",     "script",     "section",
      "select",     "small",    "span",    "strong",   "style",      "sub",
      "summary",    "sup",      "table",   "tbody",    "td",         "textarea",
      "tfoot",      "th",       "thead",   "time",     "title",      "tr",
      "ul",         "var",      "video"};
  for (auto &e : self_closing_tags) {
    if (tag == e) {
      return 1;
    }
  }

  for (auto &e : non_self_closing_tags) {
    if (tag == e) {
      return 0;
    }
  }

  return -1;
}

int HtmlParser::isInline(const string &tag) {
  /**
   * @brief 判断给定的 HTML 标签是否为内联元素
   *
   * @param s 给定的 HTML 标签
   * @return int 返回值为 0 表示不是内联元素，返回值为 1
   * 表示是普通内联元素，返回值为 2 表示是特殊内联元素
   */
  string inline_elements[] = {
      "a",        "abbr",   "acronym", "b",      "bdo",    "big",
      "br",       "button", "cite",    "code",   "data",   "datalist",
      "dfn",      "em",     "i",       "img",    "input",  "kbd",
      "label",    "map",    "mark",    "meter",  "object", "output",
      "progress", "q",      "ruby",    "rbc",    "rtc",    "rb",
      "rp",       "rt",     "samp",    "script", "select", "small",
      "span",     "strong", "sub",     "sup",    "svg",    "textarea",
      "time",     "tt",     "var",     "wbr"};

  string block_elements[] = {
      "address", "article", "aside", "audio", "blockquote", "canvas", "dd",
      "details", "div", "dl", "dt", "fieldset", "figcaption", "figure",
      "footer", "form", "h1", "h2", "h3", "h4", "h5", "h6", "header", "hgroup",
      "hr", "li", "main", "nav", "noscript", "ol", "output", "p", "pre",
      "section", "table", "tfoot", "ul", "video", "figcaption", "summary",
      "blockquote", "figure", "hr", "menu", "ol", "ul", "pre", "address",
      "dialog",

      // Table related block elements
      "caption", "colgroup", "thead", "tbody", "tr", "td", "th",

      // Others
      "template",

      // else
      "html"};

  for (const auto e : block_elements) {
    if (tag == e) {
      if (tag == "h" or tag == "p" or tag == "dt") {
        return SPECIAL_BLOCK;
      } else {
        return NORMAL_BLOCK;
      }
    }
  }

  for (const auto e : inline_elements) {
    if (tag == e) {
      if (tag == "a") {
        return SPECIAL_INLINE;
      } else {
        return NORMAL_INLINE;
      }
    }
  }
  return 0;
}

HtmlElem *HtmlParser::parseTag(int i) {
  /**
   * @brief Given a string and the index of "<". Return the HtmlElem with
   * tagName and tagContent(if had)
   * @attention : Couldn't determine whether the tag is an annotation or not.
   * @param s: string
   * @param i: index of "<"
   * @return : Return the HtmlElem with tagName and Attr
   */
  HtmlElem *res = new HtmlElem();
  res->start_index = i;

  if (doc[i + 1] == '/') { // Eng Tag </head>
    res->endTag = true;
  }

  HtmlElem *temp = isComment(i);
  if (temp->tag != NONE) {
    return temp;
  }

  temp = isJavaScript(i);
  if (temp->tag != NONE) {
    return temp;
  }

  temp = isCSS(i);
  if (temp->tag != NONE) {
    return temp;
  }

  Stack<char> st;
  string attribute = "";
  string tagname = "";
  int index = i;

  for (int j = index + 1; j < doc.length(); j++) // Get Tag Name
  {
    if (doc[j] == ' ' or doc[j] == '>' or doc[j] == '\r' or doc[j] == '\n' or
        doc[j] == '\t') {
      // cout << "tagname finish:" << doc[j];
      index = j;
      if (tagname == "!DOCTYPE") {
        res->tag = tagname;
      } else {
        res->tag = toLowerCase(tagname);
      }
      break;
    }
    tagname += doc[j];
  }

  for (int j = index; j < doc.size(); j++) {
    if (doc[j] == '"') { // class=""
      if (st.empty()) {
        st.push('"');
      } else {
        st.pop();
      }
    }

    if (st.empty() and doc[j] == '>') { // End of Tag
      res->attribute = cleanAndReduceWhitespace(attribute);
      res->end_index = j;
      break;
    }
    attribute += doc[j];
  }

  res->attrs = parseAttribute(res->attribute);

  res->SelfType = isInline(res->tag);

  if (isSelfClosing(res->tag) == 1) { // Self Closing Tag
    res->selfClosing = true;
  }

  return res;
}

bool HtmlParser::checkNested(HtmlElem *child) {
  if (child->FatherType == NORMAL_BLOCK) {
    return true;
  }

  if (child->FatherType == NORMAL_INLINE) {
    if (child->SelfType == NORMAL_INLINE or child->SelfType == SPECIAL_INLINE)
      return true;
    else
      return false;
  }

  if (child->FatherType == SPECIAL_BLOCK) {
    if (child->SelfType == NORMAL_INLINE or child->SelfType == SPECIAL_INLINE) {
      return true;
    } else {
      return false;
    }
  }

  if (child->FatherType == SPECIAL_INLINE) {
    if (child->tag == "a")
      return false;
    else
      return true;
  }
  return true;
}

HtmlElem *HtmlParser::parseContent(int i) {
  HtmlElem *res = new HtmlElem();
  res->start_index = i;
  res->end_index = doc.size();
  res->tag = CONTENT;

  string content = "";

  int index = i;
  for (index; index < doc.size(); index++) {
    if (doc[index] == '<') {
      res->end_index = index - 1;
      break;
    }
    content += doc[index];
  }

  content = strip(content);
  res->attribute = mergeSpaces(content);
  return res;
}

void HtmlParser::parseHtml() {
  /**
   * @brief Parse the whole HTML file
   * @param doc: string
   * @return : void
   */

  Stack<HtmlElem *> nodeStack;
  HtmlElem *dummyRoot = new HtmlElem;
  dummyRoot->tag = "ROOT";
  dummyRoot->SelfType = NORMAL_BLOCK;
  dummyRoot->FatherType = NORMAL_BLOCK;
  nodeStack.push(dummyRoot);

  int index = 0;
  while (!nodeStack.empty() && index + 1 < doc.length()) {
    HtmlElem *cur = nodeStack.top();

    if (doc[index] == '<') {
      HtmlElem *newEle = parseTag(index); // <node>
      newEle->FatherType = cur->SelfType;

      if (newEle->endTag) { // </node>
        string endtag = newEle->tag.substr(1, newEle->tag.length() - 1);
        if (endtag == cur->tag) {
          nodeStack.pop();
          cur = nodeStack.top();
          cur->children.append(newEle);
          index = newEle->end_index + 1;
          continue;
        } else { // parse error
          // TODO: read incomplete Html file
          this->root = nullptr;
          return;
        }
      }

      if (!newEle->selfClosing) {
        if (!checkNested(newEle)) {
          this->root = nullptr;
          return;
        }
      }

      if (!newEle->selfClosing && newEle->tag != COMMENT &&
          newEle->tag != JAVASCRIPT && newEle->tag != CSS) { // normal node
        nodeStack.push(newEle);
      }
      cur->children.append(newEle);
      index = newEle->end_index + 1;
    } else {
      HtmlElem *newEle = parseContent(index); // content
      newEle->FatherType = cur->SelfType;
      if (newEle->attribute != "")
        cur->children.append(newEle);
      index = newEle->end_index + 1;
    }
  }
  this->root = dummyRoot;
}

map<string, string> HtmlParser::parseAttribute(const string &attr) {
  map<string, string> res;
  string key = "";
  string value = "";
  bool isKey = true;
  bool isValue = false;
  bool isQuote = false;

  for (int i = 0; i < attr.size(); i++) {
    if (attr[i] == ' ') {
      continue;
    }
    if (attr[i] == '=') {
      isKey = false;
      isValue = true;
      continue;
    }
    if (attr[i] == '"') {
      if (isQuote == false) {
        isQuote = true;
        continue;
      } else {
        isQuote = false;
        res[key] = value;
        key = "";
        value = "";
        isKey = true;
        isValue = false;
        continue;
      }
    }
    if (isKey) {
      key += attr[i];
    }
    if (isValue) {
      value += attr[i];
    }
  }
  return res;
}

void HtmlParser::init() { parseHtml(); }

void HtmlParser::ReadHTML(string &html) { this->doc = html; }

void HtmlParser::ReadFile(const string &filename) {
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
  init();
}

string HtmlParser::showSub(HtmlElem *const root) {
  string res = "";
  Stack<HtmlElem *> st;
  Stack<int> st_indent;
  st_indent.push(-1);
  st.push(root);
  while (!st.empty()) {
    HtmlElem *cur = st.top();
    st.pop();
    int num = st_indent.top();
    st_indent.pop();
    if (cur->tag == COMMENT or cur->tag == JAVASCRIPT or cur->tag == CSS)
      continue;
    for (int i = 0; i < num; i) {
      res += '\t';
    }
    if (cur->tag == CONTENT)
      res += cur->attribute + '\n';
    else if (cur == root)
      ;
    else if (cur->selfClosing == true) {
      res += "<" + cur->tag + cur->attribute + ">\n";
    } else {
      res += "<" + cur->tag + cur->attribute + ">\n";
    }
    for (int i = cur->children.size() - 1; i >= 0; i--) {
      st_indent.push(num + 1);
      st.push(cur->children[i]);
    }
  }
  return res;
}

string HtmlParser::show(HtmlElem *const root) {
  if (root == nullptr) throw "Show Null pointer";
  string res = "";
  Stack<HtmlElem *> st;
  Stack<int> st_indent;
  string startTag = root->tag;
  st_indent.push(0);
  st.push(root);
  while (!st.empty()) {
    HtmlElem *cur = st.top();
    st.pop();
    int num = st_indent.top();
    st_indent.pop();
    if (cur->tag == COMMENT or cur->tag == JAVASCRIPT or cur->tag == CSS)
      continue;
    for (int i = 0; i < num; i++) {
      res += '\t';
    }
    if (cur->tag == CONTENT)
      res += cur->attribute + '\n';

    else {
      if (cur->selfClosing == true) {
        res += "<" + cur->tag + cur->attribute + ">\n";
      } else {
        res += "<" + cur->tag + cur->attribute + ">\n";
      }
    }

    for (int i = cur->children.size() - 1; i >= 0; i--) {
      st_indent.push(num + 1);
      st.push(cur->children[i]);
    }
  }
  res += "</" + startTag + ">\n";
  return res;
}

string HtmlParser::showText(HtmlElem *const root) {
  if (root == nullptr) throw "Show Null pointer for text!";
  string res = "";
  Stack<HtmlElem *> st;
  st.push(root);
  while (!st.empty()) {
    HtmlElem *cur = st.top();
    st.pop();
    if (cur->tag == COMMENT or cur->tag == JAVASCRIPT or cur->tag == CSS)
      continue;
    if (cur->tag == CONTENT) {
      if (cur->FatherType == NORMAL_INLINE or
          cur->FatherType == SPECIAL_INLINE) {
        res += cur->attribute + ' ';
      } else {
        res += cur->attribute + '\n';
      }
    }
    for (int i = cur->children.size() - 1; i >= 0; i--) {
      st.push(cur->children[i]);
    }
  }
  return res;
}

string HtmlParser::OutHTML(const string &s) {
  if (root == nullptr) {
    return "Illegal HTML file";
  }

  if (s == "/") {
    return showSub(root);
  }

  List<string> res;
  string tmp = "";
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '/') {
      if (tmp == "")
        continue;
      tmp = toLowerCase(tmp);
      res.append(tmp);
      tmp = "";
    } else {
      tmp += s[i];
    }
  }
  res.append(tmp);
  HtmlElem *cur = root;
  Queue<HtmlElem *> qe;
  qe.enqueue(cur);

  for (int i = 0; i < res.size(); i++) {
    string node = res[i];
    bool found = false;
    int size = qe.getSize();
    for (int time = 0; time < size; time++) {
      cur = qe.peek();
      qe.dequeue();
      for (int j = 0; j < cur->children.size(); j++) {
        HtmlElem *Node = cur->children[j];
        if (cur->children[j]->tag == node) {
          found = true;
          qe.enqueue(cur->children[j]);
        }
      }
    }
    if (found == false)
      return NONE;
  }
  string ans = "";
  while (!qe.empty()) {
    cur = qe.peek();
    qe.dequeue();
    ans += show(cur);
  }
  return ans;
}

string HtmlParser::Text(const string &s) {
  if (root == nullptr) {
    return "Illegal HTML";
  }

  if (s == "/") {
    return showText(root);
  }

  List<string> res;
  string tmp = "";
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '/') {
      if (tmp == "")
        continue;
      tmp = toLowerCase(tmp);
      res.append(tmp);
      tmp = "";
    } else {
      tmp += s[i];
    }
  }
  res.append(tmp);
  HtmlElem *cur = root;
  Queue<HtmlElem *> qe;
  qe.enqueue(cur);

  for (int i = 0; i < res.size(); i++) {
    string node = res[i];
    bool found = false;
    int size = qe.getSize();
    for (int time = 0; time < size; time++) {
      cur = qe.peek();
      qe.dequeue();
      for (int j = 0; j < cur->children.size(); j++) {
        HtmlElem *Node = cur->children[j];
        if (cur->children[j]->tag == node) {
          found = true;
          qe.enqueue(cur->children[j]);
        }
      }
    }
    if (found == false)
      return NONE;
  }
  string ans = "";
  while (!qe.empty()) {
    cur = qe.peek();
    qe.dequeue();
    ans += showText(cur);
  }
  return ans;
}

void HtmlParser::debug(HtmlElem *ele) {
  cout << "ele.tag: " << ele->tag << endl;
  cout << "ele.attribute: " << ele->attribute << endl;
  cout << "ele.start_index: " << ele->start_index << endl;
  cout << "ele.end_index: " << ele->end_index << endl;
  cout << "ele.selfClosing: " << ele->selfClosing << endl;
  cout << "ele.endTag: " << ele->endTag << endl;
  cout << "ele.children.size(): " << ele->children.size() << endl;
  cout << endl;
}

HtmlElem *HtmlParser::getRoot() { return this->root; }

string HtmlParser::getDoc() { return this->doc; }
