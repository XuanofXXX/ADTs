/*
 * @Author: XiaChunxuan xiachunxuan@ruc.edu.cn
 * @Date: 2023-09-26 12:41:37
 * @LastEditors: XiaChunxuan xiachunxuan@ruc.edu.cn
 * @LastEditTime: 2023-09-28 22:46:20
 * @FilePath: /2023-2024_S3/数据结构1/ADTs/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>  // for runtime_error
#include "list.cpp"

using namespace std;

void menu(){
  cout << "0: 展示菜单" << endl;
  cout << "1: 新建字符串并分词存储" << endl;
  cout << "2: 查看现在存入的字符串" << endl;
  cout << "3: 合并字符串" << endl;
  cout << "4: 从文件中读取字符串" << endl;
  cout << "5: 销毁字符串" << endl;

  cout << "9: 选取其中一个字符串并进行更多操作" << endl;
}

void submenu(){
  cout << "0: 展示子菜单" << endl;
  cout << "1: 展示字符串" << endl;
  cout << "2: 插入单词" << endl;
  cout << "3: 删除单词" << endl;
  cout << "4: 倒置字符串" << endl;
  cout << "5: 判断是否是回文串" << endl;
  cout << "6: 计算字符串中单词的个数" << endl;
  // cout << "7: 销毁字符串" << endl;
  cout << "7: 计算字符串单词个数" << endl;
  cout << "-1: 退出" << endl;
}

int input(int d = 0, int u = 9){
  // NOTE Improve Robustness.
  int pos;
  bool is_inputvalue = false;
  while (!is_inputvalue){
    cout << "Please enter a valid number." << endl;
    if (cin >> pos) {
      if (pos >= d && pos <= u){
        is_inputvalue = true;
      }
    } else {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  return pos;
}

int input_for_menu(){
  // NOTE Improve Robustness.
  int pos;
  bool is_inputvalue = false;
  while (!is_inputvalue){
    cout << "Please enter a valid number." << endl;
    if (cin >> pos) {
      if ((pos >= 0&& pos <= 5) || (pos == 9)){
        is_inputvalue = true;
      }
    } else {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  return pos;
}

int input_for_submenu(){
  // NOTE Improve Robustness.
  int pos;
  bool is_inputvalue = false;
  while (!is_inputvalue){
    cout << "Please enter a valid number." << endl;
    if (cin >> pos) {
      if (pos >= -1 && pos <= 7){
        is_inputvalue = true;
      }
    } else {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  return pos;
}

bool isBiaodian(const string& s) {
    if (s == " ") return true;
    if (s == "，") return true;
    if (s == "。") return true;
    if (s == "？") return true;
    if (s == "！") return true;
    if (s == "、") return true;
    if (s == "；") return true;
    if (s == "：") return true;
    if (s == "“") return true;
    if (s == "”") return true;
    if (s == "‘") return true;
    if (s == "’") return true;
    if (s == "【") return true;
    if (s == "】") return true;
    if (s == "[") return true;
    if (s == "《") return true;
    if (s == "《") return true;
    if (s == "》") return true;
    if (s == "（") return true;
    if (s == "）") return true;
    if (s == "…") return true;
    if (s == "—") return true;
    if (s == "　") return true; // 全角空格
    if (s == "~") return true;
    if (s == "`") return true;
    if (s == "!") return true;
    if (s == "@") return true;
    if (s == "#") return true;
    if (s == "$") return true;
    if (s == "%") return true;
    if (s == "^") return true;
    if (s == "&") return true;
    if (s == "*") return true;
    if (s == "(") return true;
    if (s == ")") return true;
    if (s == "_") return true;
    if (s == "+") return true;
    if (s == "-") return true;
    if (s == "=") return true;
    if (s == "[") return true;
    if (s == "]") return true;
    if (s == "{") return true;
    if (s == "}") return true;
    if (s == "|") return true;
    if (s == "\\") return true;
    if (s == ";") return true;
    if (s == "'") return true;
    if (s == ":") return true;
    if (s == ",") return true;
    if (s == ".") return true;
    if (s == "/") return true;
    if (s == "<") return true;
    if (s == ">") return true;
    if (s == "?") return true; 
    // 如果不是以上的任何标点符号，返回false
    return false;
}

bool in_stop_words(char s){
  string t = " ~`!@#$%^&*()_+-=[]{}|\\;':\",./<>?";
  for (int i = 0;i < t.length(); i++){
    if (s == t[i]) return true;
  }
  return false;
}

size_t utf8CharLen(unsigned char firstByte) {
    if (firstByte < 0x80) return 1;
    else if ((firstByte & 0xE0) == 0xC0) return 2;
    else if ((firstByte & 0xF0) == 0xE0) return 3;
    else if ((firstByte & 0xF8) == 0xF0) return 4;
    // 可以继续为更长的UTF-8字符添加更多的条件
    return 0;  // 无效的UTF-8首字节
}

string replaceAllC(string s){
  vector<string> chinesePunctuations = {
    "。", "，", "、", "；", "：", "？", "！", 
    "“", "”", "‘", "’", "【", "】", "{", "}", 
    "《", "》", "<", ">", "「", "」", "(", ")", 
    "[", "]", "…", "—", "　"  // 注意这里的空格是全角空格
  };
  for (auto c : chinesePunctuations){
    while (s.find(c) != string::npos){
      s.replace(s.find(c), 3, " ");
    }
  }
  return s;
}

LinkList<string> splitChineseString(const string s){
  LinkList<string> result;
  Node<string>* node = result.head;
  string delimiters = "。，、；：？！“”‘’【】￥&#8203;{}《》<>「」()[]…—";// 中文标点和空格
  string token;
  istringstream tokenStream(s); 
  char c;
  while (tokenStream.get(c)) {
    if (delimiters.find(c) != string::npos) { // 如果字符是分隔符
      if (!token.empty()) {
        Node<string>* newNode = new Node<string>(token);
        node->next = newNode;
        node = node->next;
        token.clear();
      }
    } else {
      token += c;
    }
  }

  if (!token.empty()) {
    Node<string>* newNode = new Node<string>(token);
    node->next = newNode;
    node = node->next;
  }

  return result;
}

void ope_shell(){
  <LinkList<string>> Lists;
  string s;
  int ope, pre;
  int num1, num2;
  menu();
  while (1){
    LinkList<string> l1;
    LinkList<string> l2;
    // cout << "l1's address" << &l1 << endl;
    // cout << "l2's address" << &l2 << endl;
    // NOTE: 谨慎使用cin >> ope; 因为输入不是整数时会导致死循环
    ope = input_for_menu();
    switch (ope)
    {
      case 0:
        menu();
        break;
      case 1:{  // 输入
      // 在一个txt文件里面读取一个字符串，并表示为变量s
      
        getchar();
        cout << "请输入新字符串： ";
        getline(cin,s);
        pre = 0;
        if (l1.empty()){
          l1.clear();
        }
        for (int i = 0; i < s.length(); i++){
          if (s[i] == ' ' || s[i] == ','){
            string token = s.substr(pre, i-pre);
            pre = i+1;
            l1.append(token);
          }
        }
        if (pre != s.length()){
          l1.append(s.substr(pre, s.length()-pre));
        }
        l1.display();
        Lists.append(l1);
        break;
      }
      case 2:{  // 查看现在存入的字符串：
        for (int i = 0 ; i< Lists.size();i++){
          cout << i << ": ";

          LinkList<string> l = Lists[i];
          l.display();
        }
        break;
      }

      case 3:{  // 合并字符串
        num1 = -1; num2 = -1;
        for (int i = 0 ; i< Lists.size();i++){
          cout << i << ": ";
          Lists[i].display();
        }
        while (num1 < 0 || num2 < 0 || num1 >= Lists.size() || num2 >= Lists.size() || num1 == num2){
          cout << "请输入合并的两个字符串序号(s1 <- s2): ";
          cin >> num1 >> num2;
        }
        {
          LinkList<string> merge1 = Lists[num1];
          LinkList<string> merge2 = Lists[num2];
          // cout << merge1 << endl;
          // cout << &Lists[num1] <<endl;
          merge1 += merge2;
          Lists.remove(num1);
          Lists.insert(num1, merge1);
          Lists.remove(num2);
        }
        break;
      }
        
      case 4:
        {
          cout << "请输入读取的文件名（包含后缀）: "; 
          cin >> s;
          {
            ifstream inputFile("./"+s);
            if (!inputFile.is_open()) {
              cerr << "无法打开文件" << endl;
              throw runtime_error("Can't open the file!");
            }
            getline(inputFile, s);
            cout<<"读取成功！"<<endl;
            // cout<<s[0]<<endl;
            cout<<"文件的总长度为: "<<s.length()<<endl;
          }
          
          // if (s.find("。") != string::npos){
          //   s = replaceAllC(s);
          // }
          if (l1.empty()){
            l1.clear();
          }
          string now = "";
          Node<string>* node = l1.head;
          for (int i = 0; i < s.length();){
            size_t charLen = utf8CharLen(s[i]);
            string word = s.substr(i, charLen);
            // 如果当前字符不是停用词，就加入到 now
            if (!isBiaodian(word)) {
                now += word;
            }

            // 如果当前字符是停用词，或者是字符串的最后一个字符
            if (isBiaodian(word) || i == s.length() - 1) {
                if (now != "") {
                    node->next = new Node<string>(now);
                    node = node->next;
                    l1.dataSize++;
                    now = "";
                }
            }
            i += charLen;
          }
          cout<< "read complish!"<< endl;
          Lists.append(l1);
          cout<<"切词成功！"<<endl;
          break;
        }
      case 5:  // 销毁 
        for (int i = 0; i < Lists.size(); i++)
        {
          cout << i << ": ";
          Lists[i].display();          
        }
        num1 = -1;
        cout <<"请输入你想销毁的字符串编号: "; 
        while(num1 < 0 || num1 >= Lists.size()){
          cin >> num1;
        }
        Lists[num1].Destory();
        Lists.pop(num1);
        break;
      case 9:  // 针对某一个字符串进行操作
        for (int i = 0; i < Lists.size(); i++)
        {
          cout << i << ": ";
          Lists[i].display();          
        }
        num1 = -1;
        while (num1 >= Lists.size() || num1 < 0){
          cout<< "输入你想操作的字符串的编号: ";
          cin >> num1;
        } 
        l2 = Lists[num1];
        submenu();
        while (1){
          // submenu();
          ope = input_for_submenu();
          
          if (ope == -1) break;
          switch (ope){
            case 0:
              submenu();
              break;
            case 1:  // 展示字符串
              l2.display();
              break;
            case 2:  // 插入单词
            {
              int words_counts = -1;
              while(words_counts < 0){
                cout << "请输入想要插入的单词数目: ";
                cin >> words_counts;
                cout<<endl;
              }

              num1 = l2.size()+1;
              while(num1 > l2.size()){
                cout << "请输入想要插入的位置: ";
                cin >> num1;
                if (num1 < 0) num1 += l2.size()+1;
              }
              
              cout<<"接下来请输入你想要插入的单词，使用换行隔开" << endl;
              for (int i = 0;i < words_counts; i++){
                string word;
                cin >> word;
                l2.insert(num1, word);
                num1 ++;
              }
              break;
            }
            case 3:  // 删除单词
            {
              int words_counts = -1;
              while(words_counts < 0){
                cout << "请输入想要删除的单词数目: ";
                cin >> words_counts;
                cout<<endl;
              }

              num1 = l2.size();
              while( num1 >= l2.size()){
                cout << "请输入想要删除的单词的位置: ";
                cin >> num1;
                if (num1 < 0) num1 += l2.size();
              }
              for (int i = 0;i < words_counts && num1 < l2.size(); i++){
                l2.remove(num1);
              }
              break;
            }
            case 4:  // 倒置字符串
              l2.reverse();
              break;
            case 5:  // 判断是否是回文串
              if (l2.judgeHuiwen()) cout << "是回文串";
              else cout << "不是回文串";
              break;
            case 6:  // 计算字符串中单词的个数
              cout << "请输入想要查询的单词: ";
              cin >> s;
              cout << "这个词出现了" << l2.count(s) << "次";
              break; 
            case 7:  // 显示单词个数
              cout << "这个字符串单词个数为: " << l2.size();
              break;
            default:
              cout << "不存在此命令，请重新输入" << endl;
              break;
          }
          cout << endl;
        }
        break;
      default:
        cout << "不存在此命令，请重新输入";
        break;
    }
    cout << endl;
  }
}


// void ope_file(){
//   bool is_insubmenu = false;
//   bool have_readope = false;
//   LinkList<LinkList<string>> Lists;
//   ifstream inputFile("data.txt");
//   string s;
//   int ope, pre;
//   int num1, num2;
//   string line;
//   while (getline(inputFile, line)){
//     istringstream iss(line);
//     if (!have_readope){  // 如果还没有读取操作符，就读取操作符
//       if (iss >> ope){   
//         if (ope == 0)  have_readope = false;
//         else have_readope = true;
//       }
//       else throw "Irregular file in ope";
//       continue;
//     }
//     have_readope = false;
//     LinkList<string> l1;
//     LinkList<string> l2;
//     // char ch;
//     // getchar();
//     getline(iss, s);
//     cout<<ope << ':' << s << endl;
//     istringstream is(s);
//     // s = s.substr(1, s.length()-2);
//     if (!is_insubmenu){
//       switch (ope){
//         case 1:  // 输入
//           pre = 0;
//           if (l1.empty()){
//             l1.clear();
//           }
//           for (int i = 0; i < s.length(); i++){
//             if ((s[i] == ' ') || (s[i] == ',')){
//               // if (pre == i){
//               //   pre = i + 1;
//               //   continue;
//               // }
//               string token = s.substr(pre, i-pre);
//               pre = i+1;
//               l1.append(token);
//             }
//           }
//           if (pre != s.length()){
//             l1.append(s.substr(pre, s.length()-pre));
//           }
//           l1.display();
//           Lists.append(l1);
//           break;

//         case 2:  // 查看现在存入的字符串：
//           for (int i = 0 ; i< Lists.size();i++){
//             cout << i << ": ";
//             LinkList<string> l = Lists[i];
//             l.display();
//           }
//           break;

//         case 3:  // 合并字符串
//           for (int i = 0 ; i< Lists.size();i++){
//             cout << i << ": ";
//             Lists[i].display();
//           }
//           num1 = -1; num2 = -1;
//           if (is >> num1 >> num2){
//             LinkList<string> merge1 = Lists[num1];
//             LinkList<string> merge2 = Lists[num2];
//             // cout << merge1 << endl;
//             // cout << &Lists[num1] <<endl;
//             merge1 += merge2;
//             Lists.remove(num1);
//             Lists.insert(num1, merge1);
//             Lists.remove(num2);
//           }else{
//             throw "Irregular file in case 3";
//           }
        
//         break;

//         case 9:  // 销毁 
//           // for (int i = 0; i < Lists.size(); i++)
//           // {
//           //   cout << i << ": ";
//           //   Lists[i].display();          
//           // }
//           if (is >> num1){
//             Lists.pop(num1);
//           }else{
//             throw "Irregular file in case 9";
//           }
//           break;

//         case 0:
//           for (int i = 0; i < Lists.size(); i++)
//           {
//             cout << i << ": ";
//             Lists[i].display();          
//           }
//           num1 = -1;
//           if (is >> num1){
//             l2 = Lists[num1];
//             is_insubmenu = true;
//           }else{
//             throw "Irregular file in case 0";
//           }
//           break; //for case 0;
//         default:
//           cout << "不存在此命令，请重新输入";
//           break;
//       }
//     }else{
//       // submenu();
//       // ope = input_for_submenu();
//       if (ope == 0){
//         is_insubmenu = false;
//         continue;
//       }
//       switch (ope){
//         case 1:  // 展示字符串
//           l2.display();
//           break;
//         case 2:  // 插入单词
//           cout << "请输入想要插入的单词和位置: ";
//           if(is >> s >> num1){
//             l2.insert(num1, s);
//           }else{
//             throw "Irregular file in subcase 2";
//           }
//           break;
//         case 3:  // 删除单词
//           cout << "请输入想要删除的单词的位置: ";
//           if (is >> num1){
//             l2.remove(num1);
//           }else{
//             throw "Irregular file in subcase 3";
//           }
          
//         break;
//         case 4:  // 倒置字符串
//           l2.reverse();
//           break;
//         case 5:  // 判断是否是回文串
//           if (l2.judgeHuiwen()){
//             cout << "是回文串";
//           }else{
//             cout << "不是回文串";
//           }
//           break;
//         case 6:  // 计算字符串中单词的个数
//           cout << "请输入想要查询的单词: ";
//           if(is >> s){
//             cout << "这个词出现了" << l2.count(s) << "次";
//           }else{
//             throw "Irregular file in subcase 6";
//           }
//           break; 
//         case 7:  // 销毁 
//           l2.clear();
//           Lists.remove(num1);
//           break;
//         case 8:  // 显示单词个数
//           cout << "这个字符串单词个数为: " << l2.size();
//           break;
//         default:
//           cout << "不存在此命令，请重新输入" << endl;
//           break;
//       }
//       cout << endl;  
//     }
//     cout << endl;
//   }
// }

int main(){
  ope_shell();
  // ope_file();
  return 0;
}