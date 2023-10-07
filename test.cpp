/*
 * @Author       : xiachunxuan
 * @Date         : 2023-09-29 09:52:58
 * @LastEditTime : 2023-10-07 15:39:02
 * @LastEditors  : xiachunxuan
 * @Description  : Do not edit 
 * @FilePath     : /2023-2024_S3/数据结构1/ADTs/test.cpp
 */

#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


size_t utf8CharLen(unsigned char firstByte) {
    if (firstByte < 0x80) return 1;
    else if ((firstByte & 0xE0) == 0xC0) return 2;
    else if ((firstByte & 0xF0) == 0xE0) return 3;
    else if ((firstByte & 0xF8) == 0xF0) return 4;
    // 可以继续为更长的UTF-8字符添加更多的条件
    return 0;  // 无效的UTF-8首字节
}

int main(){
  vector<int> v ;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  for (int i = 0; i < v.size(); i++)
  {
    cout << v.at(i) << " ";
  }
  v.erase(v.begin()+1);
  for (int i = 0; i < v.size(); i++)
  {
    cout << v.at(i) << " ";
  }

  
}