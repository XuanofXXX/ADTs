#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cctype>
#include <curl/curl.h>

// #include "include/lab2.h"
#include "../DataStructure/src/List.cpp"
#include "../DataStructure/src/Stack.cpp"
#include "HtmlParser.cpp"

using namespace std;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  ((string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

string fetch_url_content(const string &url)
{
  CURL *curl;
  CURLcode res;
  string readBuffer;

  curl = curl_easy_init();
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }
  return readBuffer;
}

bool isHttpURL(const string &str)
{
  return str.substr(0, 7) == "http://" || str.substr(0, 8) == "https://";
}

void menu()
{
  cout << "1. ReadHTML" << endl;
  cout << "2. CheckHTML" << endl;
  cout << "3. OutHTML" << endl;
  cout << "4. TextHTML" << endl;
  cout << "0. EXIT" << endl;
}

string input()
{
  string a;
  cout << "请输入路径/网址: ";
  cin >> a;
  return a;
}

string inputPath()
{
  string a;
  cout << "请输入路径: ";
  cin >> a;
  return a;
}

int main()
{
  HtmlParser parser;

  while (true)
  {
    menu();
    int command;
    cin >> command;
    if (command == 1)
    {
      string path = input(); // 假设命令和路径之间有一个空格
      if (isHttpURL(path))
      {
        string content = fetch_url_content(path);
        parser.ReadHTML(content);
      }
      else
      {
        parser.ReadFile(path);
      }
      parser.init();
    }
    else if (command == 2)
    {
      if (parser.getRoot() == nullptr)
      {
        cout << "Illegal HTML file" << endl;
      }
      else
      {
        cout << "Legal HTML file" << endl;
      }
    }
    else if (command == 3)
    {
      string path = inputPath(); // 假设命令和路径之间有一个空格
      cout << path << endl;
      cout << parser.OutHTML(path) << endl;
    }
    else if (command == 4)
    {
      string path = inputPath(); // 假设命令和路径之间有一个空格
      cout << path << endl;
      cout << parser.Text(path) << endl;
    }
    else if (command == 0)
    {
      break;
    }
    else
    {
      cout << "Invalid command." << endl;
    }
  }
  return 0;
}
