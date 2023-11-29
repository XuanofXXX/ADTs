#ifndef UTILS_H
#define UTILS_H

#include "../DataStructure/src/Queue.cpp"
#include "../DataStructure/src/Stack.cpp"
#include "../DataStructure/src/String.cpp"

bool exist(LinkList<HtmlElem *> *l, HtmlElem *ele) {

  // For LinkList
  Node<HtmlElem *> *cur = l->head->next;
  while (cur) {
    if (cur->data->tag == ele->tag && cur->data->attrs == ele->attrs &&
        cur->data->attribute == ele->attribute) {
      return true;
    }
    cur = cur->next;
  }
  
  // For List
  // for (int i = 0; i < l->size(); i++) {
  //   if (l->at(i)->tag == ele->tag && l->at(i)->attribute == ele->attribute &&
  //       l->at(i)->attrs == ele->attrs)
  //     return true;
  // }
  return false;
}

#endif
