/*
 * @Author: XiaChunxuan xiachunxuan@ruc.edu.cn
 * @Date: 2023-09-26 17:18:07
 * @LastEditors: XiaChunxuan xiachunxuan@ruc.edu.cn
 * @LastEditTime: 2023-09-27 15:27:53
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
  // int n;
  // std::cin >> n;
  int a = 0xFFFFFFFF;
  // std::cout <<sizeof(int)  <<std::endl;
  std::cout <<std::hex<< a <<std::endl;
  std::cout <<std::hex<< (a>>31)<<31 <<std::endl;
  std::cout <<std::hex<< (a>>31) <<std::endl;
}