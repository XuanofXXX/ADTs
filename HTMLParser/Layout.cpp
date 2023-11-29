#ifndef LAYOUT_CPP
#define LAYOUT_CPP

#include "Layout.h"

string Layout::showSub(HtmlElem *const root) {
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

string Layout::show(HtmlElem *const root) {
  if (root == nullptr)
    throw "Show Null pointer";
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

string Layout::showText(HtmlElem *const root) {
  if (root == nullptr)
    throw "Show Null pointer for text!";
  string res = "";
  Stack<HtmlElem *> st;
  st.push(root);
  while (!st.empty()) {
    HtmlElem *cur = st.top();
    st.pop();
    if (cur->tag == COMMENT or cur->tag == JAVASCRIPT or cur->tag == CSS)
      continue;
    if (cur->tag == CONTENT) {
      if (cur->fatherType == NORMAL_INLINE or
          cur->fatherType == SPECIAL_INLINE) {
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

string Layout::OutHTML(const string &s) {
  //
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

string Layout::Text(HtmlElem* root, const string &s) {
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

#endif