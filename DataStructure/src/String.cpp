#include <iostream>
#include <cstring>
#include <string>
#include "List.cpp"

using std::string;

List<string> split(const string& s, char ch){
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

string toLowerCase(const string& input) {
  string result = input;
  for (char& c : result) {
    if (isalpha(c) && isupper(c)) {
      c = tolower(c);
    }
  }
  return result;
}

string stripe(string s){
  string res = "";
  int index = 0;
  int endindex = s.size()-1;
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

string mergeSpaces(const string &input) {
    string result;
    bool lastWasSpace = false;

    for (char c : input) {
        if (c == ' ') {
            if (!lastWasSpace) {
                result.push_back(c);
            }
            lastWasSpace = true;
        } else {
            result.push_back(c);
            lastWasSpace = false;
        }
    }

    return result;
}