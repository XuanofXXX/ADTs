/*
 * @Author: XiaChunxuan xiachunxuan@ruc.edu.cn
 * @Date: 2023-09-26 12:41:37
 * @LastEditors: XiaChunxuan xiachunxuan@ruc.edu.cn
 * @LastEditTime: 2023-09-28 17:27:25
 * @FilePath: /2023-2024_S3/数据结构1/ADTs/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "list.cpp"

void menu(){
  std::cout << "1: 新建字符串并分词存储" << std::endl;
  std::cout << "2: 查看现在存入的字符串" << std::endl;
  // std::cout << "3: 计算两个字符串相似度" << std::endl;
  std::cout << "3: 合并字符串" << std::endl;
  std::cout << "9: 销毁字符串" << std::endl;

  std::cout << "0: 选取其中一个字符串并进行更多操作" << std::endl;
}

void submenu(){
  std::cout << "1: 展示字符串" << std::endl;
  std::cout << "2: 插入单词" << std::endl;
  std::cout << "3: 删除单词" << std::endl;
  std::cout << "4: 倒置字符串" << std::endl;
  std::cout << "5: 判断是否是回文串" << std::endl;
  std::cout << "6: 计算字符串中单词的个数" << std::endl;
  std::cout << "7: 销毁字符串" << std::endl;
  std::cout << "8: 计算字符串单词个数" << std::endl;
  std::cout << "0: 退出" << std::endl;
}

int input(int d = 0, int u = 9){
  // NOTE Improve Robustness.
  int pos;
  bool is_inputvalue = false;
  while (!is_inputvalue){
    std::cout << "Please enter a valid number." << std::endl;
    if (std::cin >> pos) {
      if (pos >= d && pos <= u){
        is_inputvalue = true;
      }
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return pos;
}
int input_for_menu(){
  // NOTE Improve Robustness.
  int pos;
  bool is_inputvalue = false;
  while (!is_inputvalue){
    std::cout << "Please enter a valid number." << std::endl;
    if (std::cin >> pos) {
      if ((pos >= 0&& pos <= 3) || (pos == 9)){
        is_inputvalue = true;
      }
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return pos;
}
int input_for_submenu(){
  // NOTE Improve Robustness.
  int pos;
  bool is_inputvalue = false;
  while (!is_inputvalue){
    std::cout << "Please enter a valid number." << std::endl;
    if (std::cin >> pos) {
      if (pos >= 0 && pos <= 7){
        is_inputvalue = true;
      }
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return pos;
}

void ope_shell(){
  LinkList<LinkList<std::string>> Lists;
  // menu();

  // { // 测试List的构造函数
  //   List<std::string> l6;   
  //   l6.clear();
  //   l6.append("1");
  //   if (l6.empty()){
  //     l6.clear();
  //   }
  // }
  
  
  std::string s;
  int ope, pre;
  int num1, num2;
  while (1){
    menu();
    LinkList<std::string> l1;
    LinkList<std::string> l2;
    // std::cout << "l1's address" << &l1 << std::endl;
    // std::cout << "l2's address" << &l2 << std::endl;
    // NOTE: 谨慎使用cin >> ope; 因为输入不是整数时会导致死循环 
    ope = input_for_menu();
    switch (ope)
    {
      case 1:  // 输入
        getchar();
        std::cout << "请输入新字符串： ";
        std::getline(std::cin,s);
        pre = 0;
        if (l1.empty()){
          l1.clear();
        }
        for (int i = 0; i < s.length(); i++){
          if (s[i] == ' ' || s[i] == ','){
            std::string token = s.substr(pre, i-pre);
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

      case 2:  // 查看现在存入的字符串：
        for (int i = 0 ; i< Lists.size();i++){
          std::cout << i << ": ";

          LinkList<std::string> l = Lists[i];
          l.display();
        }
        break;

      // case 3:  // 计算两个字符串相似度
      // // 废弃了

      //   for (int i = 0 ; i< Lists.size();i++){
      //     std::cout << i << ": ";
      //     Lists[i].display();
      //   }
      //   std::cout << "请输入想要计算的字符串编号 ";
      //   std::cin >> num1 >> num2;
      //   std::cout << "结果为：" << Lists[num1].calcSimilarity(Lists[num2]);

      //   break;

      case 3:  // 合并字符串
        num1 = -1; num2 = -1;
        for (int i = 0 ; i< Lists.size();i++){
          std::cout << i << ": ";
          Lists[i].display();
        }
        while (num1 < 0 || num2 < 0 || num1 >= Lists.size() || num2 >= Lists.size() || num1 == num2){
          std::cout << "请输入合并的两个字符串序号(s1 <- s2): ";
          std::cin >> num1 >> num2;
        }
        {
          LinkList<std::string> merge1 = Lists[num1];
          LinkList<std::string> merge2 = Lists[num2];
          // std::cout << merge1 << std::endl;
          // std::cout << &Lists[num1] <<std::endl;
          merge1 += merge2;
          Lists.remove(num1);
          Lists.insert(num1, merge1);
          Lists.remove(num2);
        }
        break;

      case 9:  // 销毁 
        for (int i = 0; i < Lists.size(); i++)
        {
          std::cout << i << ": ";
          Lists[i].display();          
        }
        num1 = -1;
        std::cout <<"请输入你想销毁的字符串编号: "; 
        while(num1 < 0 || num1 >= Lists.size()){
          std::cin >> num1;
        }
        Lists.pop(num1);
        break;

        break;
      case 0:
        for (int i = 0; i < Lists.size(); i++)
        {
          std::cout << i << ": ";
          Lists[i].display();          
        }
        num1 = -1;
        while (num1 >= Lists.size() || num1 < 0){
          std::cout<< "输入你想操作的字符串的编号: ";
          std::cin >> num1;
        } 
        l2 = Lists[num1];

        while (1){
          submenu();
          ope = input_for_submenu();
          
          if (ope == 0) break;
          switch (ope){
            case 1:  // 展示字符串
              l2.display();
              break;
            case 2:  // 插入单词
              std::cout << "请输入想要插入的单词和位置: ";
              std::cin >> s >> num1;
              l2.insert(num1, s);
              break;
            case 3:  // 删除单词
              std::cout << "请输入想要删除的单词的位置: ";
              std::cin >> num1;
              l2.remove(num1);
              break;
            case 4:  // 倒置字符串
              l2.reverse();
              break;
            case 5:  // 判断是否是回文串
              if (l2.judgeHuiwen()){
                std::cout << "是回文串";
              }else{
                std::cout << "不是回文串";
              }
              break;
            case 6:  // 计算字符串中单词的个数
              std::cout << "请输入想要查询的单词: ";
              std::cin >> s;
              std::cout << "这个词出现了" << l2.count(s) << "次";
              break; 
            case 7:  // 销毁 
              l2.clear();
              Lists.remove(num1);
              break;
            case 8:  // 显示单词个数
              std::cout << "这个字符串单词个数为: " << l2.size();
              break;
            default:
              std::cout << "不存在此命令，请重新输入" << std::endl;
              break;
          }
          std::cout << std::endl;
        }
        break;
      default:
        std::cout << "不存在此命令，请重新输入";
        break;
    }
    std::cout << std::endl;
  }
}


void ope_file(){
  bool is_insubmenu = false;
  bool have_readope = false;
  LinkList<LinkList<std::string>> Lists;
  std::ifstream inputFile("data.txt");
  std::string s;
  int ope, pre;
  int num1, num2;
  std::string line;
  while (std::getline(inputFile, line)){
    std::istringstream iss(line);
    if (!have_readope){  // 如果还没有读取操作符，就读取操作符
      if (iss >> ope){   
        if (ope == 0)  have_readope = false;
        else have_readope = true;
      }
      else throw "Irregular file in ope";
      continue;
    }
    have_readope = false;
    LinkList<std::string> l1;
    LinkList<std::string> l2;
    // char ch;
    // std::getchar();
    std::getline(iss, s);
    std::cout<<ope << ':' << s << std::endl;
    std::istringstream is(s);
    // s = s.substr(1, s.length()-2);
    if (!is_insubmenu){
      switch (ope){
        case 1:  // 输入
          pre = 0;
          if (l1.empty()){
            l1.clear();
          }
          for (int i = 0; i < s.length(); i++){
            if ((s[i] == ' ') || (s[i] == ',')){
              // if (pre == i){
              //   pre = i + 1;
              //   continue;
              // }
              std::string token = s.substr(pre, i-pre);
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

        case 2:  // 查看现在存入的字符串：
          for (int i = 0 ; i< Lists.size();i++){
            std::cout << i << ": ";
            LinkList<std::string> l = Lists[i];
            l.display();
          }
          break;

        case 3:  // 合并字符串
          for (int i = 0 ; i< Lists.size();i++){
            std::cout << i << ": ";
            Lists[i].display();
          }
          num1 = -1; num2 = -1;
          if (is >> num1 >> num2){
            LinkList<std::string> merge1 = Lists[num1];
            LinkList<std::string> merge2 = Lists[num2];
            // std::cout << merge1 << std::endl;
            // std::cout << &Lists[num1] <<std::endl;
            merge1 += merge2;
            Lists.remove(num1);
            Lists.insert(num1, merge1);
            Lists.remove(num2);
          }else{
            throw "Irregular file in case 3";
          }
        
        break;

        case 9:  // 销毁 
          // for (int i = 0; i < Lists.size(); i++)
          // {
          //   std::cout << i << ": ";
          //   Lists[i].display();          
          // }
          if (is >> num1){
            Lists.pop(num1);
          }else{
            throw "Irregular file in case 9";
          }
          break;

        case 0:
          for (int i = 0; i < Lists.size(); i++)
          {
            std::cout << i << ": ";
            Lists[i].display();          
          }
          num1 = -1;
          if (is >> num1){
            l2 = Lists[num1];
            is_insubmenu = true;
          }else{
            throw "Irregular file in case 0";
          }
          break; //for case 0;
        default:
          std::cout << "不存在此命令，请重新输入";
          break;
      }
    }else{
      // submenu();
      // ope = input_for_submenu();
      if (ope == 0){
        is_insubmenu = false;
        continue;
      }
      switch (ope){
        case 1:  // 展示字符串
          l2.display();
          break;
        case 2:  // 插入单词
          std::cout << "请输入想要插入的单词和位置: ";
          if(is >> s >> num1){
            l2.insert(num1, s);
          }else{
            throw "Irregular file in subcase 2";
          }
          break;
        case 3:  // 删除单词
          std::cout << "请输入想要删除的单词的位置: ";
          if (is >> num1){
            l2.remove(num1);
          }else{
            throw "Irregular file in subcase 3";
          }
          
        break;
        case 4:  // 倒置字符串
          l2.reverse();
          break;
        case 5:  // 判断是否是回文串
          if (l2.judgeHuiwen()){
            std::cout << "是回文串";
          }else{
            std::cout << "不是回文串";
          }
          break;
        case 6:  // 计算字符串中单词的个数
          std::cout << "请输入想要查询的单词: ";
          if(is >> s){
            std::cout << "这个词出现了" << l2.count(s) << "次";
          }else{
            throw "Irregular file in subcase 6";
          }
          break; 
        case 7:  // 销毁 
          l2.clear();
          Lists.remove(num1);
          break;
        case 8:  // 显示单词个数
          std::cout << "这个字符串单词个数为: " << l2.size();
          break;
        default:
          std::cout << "不存在此命令，请重新输入" << std::endl;
          break;
      }
      std::cout << std::endl;  
    }
    std::cout << std::endl;
  }
}

int main(){
  ope_shell();
  // ope_file();
  return 0;
}