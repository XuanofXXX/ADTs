/*
 * @Author       : xiachunxuan
 * @Date         : 2023-09-29 09:52:58
 * @LastEditTime : 2023-10-06 20:05:43
 * @LastEditors  : xiachunxuan
 * @Description  : Do not edit 
 * @FilePath     : /2023-2024_S3/数据结构1/ADTs/test.cpp
 */

#include<iostream>
#include <fstream>
#include <sstream>
#include <string>

size_t utf8CharLen(unsigned char firstByte) {
    if (firstByte < 0x80) return 1;
    else if ((firstByte & 0xE0) == 0xC0) return 2;
    else if ((firstByte & 0xF0) == 0xE0) return 3;
    else if ((firstByte & 0xF8) == 0xF0) return 4;
    // 可以继续为更长的UTF-8字符添加更多的条件
    return 0;  // 无效的UTF-8首字节
}

int main(){
  std::string s = "你好11啊22 dd阿道夫";
  for (int i = 0 ;i < s.length();i++){
    size_t charLen = utf8CharLen(s[i]);
    if (charLen == 1){
      std::cout << s[i] << " " << charLen << std::endl;
      continue;
    }
    std::string temp = s.substr(i,charLen);
    std::cout << temp << " " << charLen << std::endl;
    i += charLen - 1;
  }
}