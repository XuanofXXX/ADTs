/*
 * @Author: XiaChunxuan xiachunxuan@ruc.edu.cn
 * @Date: 2023-09-26 17:18:07
 * @LastEditors: XiaChunxuan xiachunxuan@ruc.edu.cn
 * @LastEditTime: 2023-09-27 12:48:50
 * @FilePath: /2023-2024_S3/数据结构1/ADTs/test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include<iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(){
  // std::string s;
  // std::ifstream inputFile("data.txt");
  // if (inputFile.is_open()) {
  //   // Read each line of the file
  //   while (std::getline(inputFile, s)) {
  //     std::istringstream iss(s);
  //     int num;
  //     std::string str;
  //     if (iss >> num) {
  //       std::getline(iss, str);
  //       std::cout << s <<std::endl;
  //       std::cout << num <<std::endl;
  //       std::cout << str <<std::endl;
  //     }
  //   }
  //   inputFile.close();
  int a;
  std::cin >> a;
  if (a <= 0){
    throw std::invalid_argument("Invalid argument");
  }else
  {
    std::cout << a <<std::endl;
  }
  
  
}