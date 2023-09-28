/*
 * @Author: XiaChunxuan xiachunxuan@ruc.edu.cn
 * @Date: 2023-09-14 20:25:43
 * @LastEditors: XiaChunxuan xiachunxuan@ruc.edu.cn
 * @LastEditTime: 2023-09-27 14:13:50
 * @FilePath: /2023-2024_S3/数据结构1/ADTs/list.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
// #define Elemtype string

// template <typename Elemtype>
/**
 * @file list.cpp
 * @brief Implementation of a dynamic array-based list data structure.
 * 
 * This file contains the implementation of a dynamic array-based list data structure, 
 * which supports various operations such as appending, inserting, removing, popping, 
 * counting, reversing, extending, calculating similarity, searching for differences, 
 * concatenating, and indexing. 
 * 
 * The list is implemented using a dynamic array, which is automatically resized when 
 * necessary. The initial capacity of the array is 8, and the extend ratio is 2. 
 * 
 * 
 * 
 * @tparam Elemtype The type of elements stored in the list.
/*/
/*
class String {
public:
  String() {}
  String(const wchar_t* str) {
    int len = wcslen(str);
    data = new wchar_t[len + 1];
    wcscpy(data, str);
  }

  ~String() {
    delete[] data;
  }

  void append(const wchar_t* str) {
    int len1 = wcslen(data);
    int len2 = wcslen(str);
    wchar_t* newData = new wchar_t[len1 + len2 + 1];
    wcscpy(newData, data);
    wcscpy(newData + len1, str);
    delete[] data;
    data = newData;
  }

  const wchar_t* getData() const {
    return data;
  }

private:
    wchar_t* data = nullptr;
};
*/


template <typename Elemtype>
class List{

private:
  Elemtype *data;
  int dataSize = 0; 
  int dataCapacity = 8; 
  int extendRatio = 2;

public:
  List(){
    data = new Elemtype[dataCapacity];
  }

  void clear(){
    dataSize = 0;
    dataCapacity = 8;
    delete[] data;
    data = new Elemtype[dataCapacity];
  }

  // ~List(){
  //   delete[] data;
  //   std::cout << "Delete"<< std::endl;
  // }

  int size(){
  return dataSize;
  }

  int capacity(){
  return dataCapacity;
  }

  bool empty(){
  return dataSize == 0;
  }

  void extendCapacity(){  // 新增扩容量
  int newCapacity = capacity() * extendRatio;
  Elemtype *tmp = data;
  data = new Elemtype[newCapacity];
  for (int i = 0; i < size(); i++){
    data[i] = tmp[i];
  }
  delete[] tmp;
  dataCapacity = newCapacity;
    // std::cout << "ENTENDCAPACITY" << std::endl;
    // int newCapacity = capacity() * extendRatio;
    // Elemtype* newbase = ( Elemtype * ) realloc (data, newCapacity * sizeof(Elemtype) );
    // data = newbase;
    // dataCapacity = newCapacity;
    // std::cout << "ENTENDCAPACITY" << std::endl;
  }



  // 在尾部追加元素
  void append(Elemtype val){
    /**
     * 
     * 
     * 
    */
    if (size() + 1 > capacity()){
      extendCapacity();
    }
    data[size()] = val;
    dataSize ++;
  }

  // 在索引位置插入val
  void insert(int index, Elemtype &val){
    // std::cout<< "start insert" <<std::endl;

    if (index >= size() || index < 0) {
      // std::cout<< "asdfsadf"<<std::endl;
      throw "index out of range";
    }
    // std::cout<< "zzz"<<std::endl;
    if (size() + 1 > capacity()){
      extendCapacity();
    }
    // std::cout<< "zzz"<<std::endl;
    for (int i = size()-1;i >= index ;i--){
    // std::cout<< "i is "<< i << std::endl;
      data[i+1] = data[i];
    }
    data[index] = val;
    dataSize ++;
    std::cout << "insert finished" << std::endl;
  }

  // 移除对应元素
  void remove(int index){
    if (index >= size() || index < 0) throw "index out of range";
    for (int i = index; i < size()-1;i++){
      data[i] = data[i+1];
    }
    dataSize --;
  }

  // 弹出最后一个元素
  Elemtype pop(int index = -1){
    if (index >= size() || index < -1) throw "index out of range";
    if (index == -1) {
      dataSize --;
      return data[size()];
    }
    Elemtype temp = data[index];
    for (int i = index; i < size()-1;i++){  
      data[i] = data[i+1];
    } 
    dataSize --;
    return temp;
  }
  
  int count(Elemtype val){
    int res = 0;
    for (int i = 0 ; i< size();i++){
      if (data[i] == val) res ++;
    }
    return res;
  }

  // judge 回文
  bool judgeHuiwen(){
    if (size() <= 1) return true;
    int begin = 0, end = size()-1;
    while (begin<end){
      if (data[begin] != data[end]) return false;
      begin ++;
      end --;
    }
    return true;
  }

  // reverse
  void reverse(){
    int begin = 0, end = size()-1;
    while (begin<end){
      Elemtype temp;
      temp = data[begin];
      data[begin] = data[end];
      data[end] = temp;
      begin ++;
      end --;
    }
  }

  void extend(List<Elemtype> other){
    for (int i = 0 ;i < other.size();i++){
      append(other[i]);
    }
  }

  List<Elemtype> operator+(List<Elemtype> &other){
    List<Elemtype> res;
    res.extend(*this);
    res.extend(other);
    return res;
  }

  List<Elemtype>& operator+=(List<Elemtype> &other){
    extend(other);
    return *this;
  };

  // 定位，支持类似python的-1索引
  Elemtype operator[](int index){
    if (index >= size() || index < -size()) throw "index out of range";
    if (index < 0) return data[index+size()];
    else return data[index];
  }

  // 打印
  void display(){
    for (int i = 0 ;i< size();i++){
      std::cout << data[i] <<' ';
    }
    std::cout << std::endl;
  }
};


// int main(){
//   List<int> Mylist;
//   Mylist.print();
//   for (int i = 0;i < 21;i++){
//     Mylist.append(i);
//   }
//   Mylist.print();
//   std::cout <<"pop:" << Mylist.pop() << ' ' << Mylist.pop() << std::endl;
  
//   Mylist.print();
//   std::cout << std::endl;
//   Mylist.insert(0,999);
//   Mylist.print();
//   Mylist.remove(2);
//   Mylist.print();
// }


template <typename Elemtype>
struct Node {
  Elemtype data;
  Node* next;

  Node() : data(), next(nullptr) {}
  Node(Elemtype value) : data(value), next(nullptr) {}
};

// 定义链表类
template <typename Elemtype>
class LinkList {
private:
  Node<Elemtype>* head;
  int dataSize;

public:
  LinkList() : head(new Node<Elemtype>()) ,dataSize(0) {}
  
  int size(){
    return dataSize;
  }

  bool empty(){
    return dataSize == 0;
  }

	// Elemtype at(int index){
		
	// }

  void prepend(Elemtype val) {
    Node<Elemtype>* newNode = new Node<Elemtype>(val);
    newNode->next = head->next;
    head->next = newNode;
    dataSize ++;
  }

	void pop(int index = -1){
		remove(index);
	}

  void append(Elemtype val){
    Node<Elemtype>* cur = head;
    while (cur->next){
      cur = cur->next;
    }
    Node<Elemtype>* newNode = new Node<Elemtype>(val);
    cur->next = newNode;
    dataSize ++;
  }

  void display() {
    if (!head->next){
      std::cout << "None" << std::endl;
      return ;
    }
    Node<Elemtype>* cur = head;
    cur = cur->next;

    while(cur){
      std::cout << cur->data << " -> ";
      cur = cur->next;
    }
    std::cout <<"None" << std::endl;
    
    // for (int i= 0 ;i< dataSize;i++){
    //   std::cout << cur->data << " -> ";
      
    //   cur = cur->next; 
    // }
    // std::cout <<"None" << std::endl;
    
  }

  void insert(int pos, Elemtype val){
    Node<Elemtype>* cur = head;
    Node<Elemtype>* newNode = new Node<Elemtype>(val);
    while (pos --){
      cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
    dataSize ++;
  }

  Elemtype remove(int pos){
    Node<Elemtype>* cur = head;
    while (pos--){
      cur = cur->next;
    }
    Node<Elemtype>* tar = cur->next;
    cur->next = cur->next->next;
    dataSize --;
    return tar->data;
  } 

  bool find(Elemtype val){
    Node<Elemtype>* cur = head;
    if (dataSize < 1) return false;
    cur = cur->next;
    while (cur){
      if (cur->data == val){
        return true;
      }
      cur = cur->next;
    }
    return false;
  }
	
  void reverse(){
    if (dataSize <= 1) return;

    Node<Elemtype>* cur = head->next;
    Node<Elemtype>* prev = nullptr;
    Node<Elemtype>* next = nullptr;

    while (cur) {
      next = cur->next;  
      cur->next = prev;  
      prev = cur;    
      cur = next;    
    }
    head->next = prev;
  }

  int count(Elemtype val){
    int res = 0;
    if (! head->next) return 0;
    Node<Elemtype>* cur = head;
    cur = cur->next;
    while (cur){
      if (cur->data == val) res ++;
      cur = cur->next;
    }
    return res;
  }

  bool judgeHuiwen(){
    Node<Elemtype>* cur = head;
    if (dataSize <= 1) return true;
    cur = cur->next;
    Node<Elemtype>* prev = nullptr;
    Node<Elemtype>* next = nullptr;
    while (cur){
      next = cur->next;
      cur->next = prev;
      prev = cur;
      cur = next;
    }
    Node<Elemtype>* cur1 = head->next;
    Node<Elemtype>* cur2 = prev;
    while (cur1){
      if (cur1->data != cur2->data) return false;
      cur1 = cur1->next;
      cur2 = cur2->next;
    }
    return true;
  }

  void extend(LinkList<Elemtype> other){
    Node<Elemtype>* cur = head;
    while (cur->next){
      cur = cur->next;   
    }
    Node<Elemtype>* cur_other = other.head->next;
    while (cur_other){

      Node<Elemtype>* newNode = new Node<Elemtype>(cur_other->data);
      cur->next = newNode;

      cur = cur->next;
      cur_other = cur_other->next;
    }
    this->dataSize += other.dataSize;
  }


  void clear(){
		Node<Elemtype>* cur = head;
		while (cur->next){
			Node<Elemtype>* next = cur->next;
			delete cur;
			cur = next;
		}
		delete head;
    head = new Node<Elemtype>();
    dataSize = 0;
  }
  /*

  // DEBUG When LinkList<int> MyList3 = Mylist1 + Mylist2; Mylist1 will change?
  // NOTE: NOT SUPPORT + operation for LinkList!
  LinkList<Elemtype> operator+(LinkList<Elemtype> &other){
    LinkList<Elemtype> res;
    res.extend(*this);
    res.extend(other);
    return res;
  }
  
  */

 	// LinkList<Elemtype> operator=(LinkList<Elemtype> &other){
	// 	clear();
	// 	extend(other);
	// 	return *this;
	// }

	Elemtype operator[](int index){
		if (index >= size() || index < -size()) throw "index out of range";
		if (index < 0) index += size();
		Node<Elemtype> * cur = head;
		cur = cur->next;
		while (index--){
			cur = cur->next;
		}
		return cur->data;
	}

  LinkList<Elemtype>& operator+=(LinkList<Elemtype> &other){
    extend(other);
    return *this;
  }


  // ~LinkList() {
  //   Node<Elemtype>* cur = head;

  //   while (cur && cur->next) {
  //     Node<Elemtype>* next = cur->next;
  //     delete cur;
  //     cur = next;
  //   }
  //   // delete head;
  // }
};