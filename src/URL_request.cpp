/**
 * @file URL_request.cpp
 * @author XiaChunxuan (xiachunxuan@ruc.edu.cn)
 * 
 * @brief
 * This file contains the implementation of the function that fetches the
 * content of a URL, which based on "curl".
 * 
 * @version 0.1
 * @date 2023-11-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <curl/curl.h>
#include <string>

using std::string;

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