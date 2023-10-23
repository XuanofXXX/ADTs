#include <iostream>
#include <cstring>
#include <string>
#include "List.cpp"

using std::string;

List<string> split(string s, char ch){
  List<string> res;
  string tmp = "";
  for (int i = 0; i < s.size(); i++){
    if (s[i] == ch){
      res.append(tmp);
      tmp = "";
    }
    else{
      tmp += s[i];
    }
  }
  res.append(tmp);
  return res;
}

string stripe(string s){
  string res = "";
  int index = 0;
  int endindex = s.size();
  for (index; index < s.size(); index++)
  {
    if (s[index] != ' ' && s[index] != '\n' && s[index] != '\t'){
      break;
    }
  }

  if (index == s.size()-1){
    return "";
  }


  for (endindex; endindex >= 0; endindex --){
    if (s[endindex] != ' ' && s[endindex] != '\n' && s[endindex] != '\t'){
      break;
    }
  }

  if (index < endindex){
    for (int i = index; i <= endindex; i++){
      res += s[i];
    }
  }

  return res; 
}