#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cctype>
#include <curl/curl.h>

// #include "include/lab2.h"
#include "./DataStructure/src/List.cpp"
#include "./DataStructure/src/Stack.cpp"
#include "HtmlParser.cpp"

using namespace std;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
  ((string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

string fetch_url_content(const string& url) {
  CURL* curl;
  CURLcode res;
  string readBuffer;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }
  return readBuffer;
}

bool isHttpURL(const string& str) {
  return str.substr(0, 7) == "http://" || str.substr(0, 8) == "https://";
}

int main() {
  HtmlParser parser;
  
  while (true) {
    cout << "Enter command (ReadHTML, CheckHTML, OutHTML, Text, Exit): ";
    string command;
    getline(cin, command);
    if (command.substr(0,8) == "ReadHTML"){
      string path = command.substr(9); // 假设命令和路径之间有一个空格
      if (isHttpURL(path)){
        string content = fetch_url_content(path);
        parser.ReadHTML(content);
      }else{
        parser.readFile(path);
      }
    }
    else if (command == "CheckHTML") {
      if (parser.getRoot() == nullptr){
        cout <<"Illegal HTML file" << endl;
      }else{
        cout << "Legal HTML file" << endl;
      }
    } else if (command.substr(0, 7) == "OutHTML") {
      string path = command.substr(8); // 假设命令和路径之间有一个空格
      cout << parser.OutHTML(path) << endl;
    } else if (command.substr(0, 4) == "Text") {
      string path = command.substr(5); // 假设命令和路径之间有一个空格
      cout << parser.Text(path) << endl;
    } else if (command == "Exit") {
      break;
    } else {
      cout << "Invalid command." << endl;
    }
  }

  return 0;
}
