#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cctype>
#include <curl/curl.h>

// #include "include/lab2.h"
#include "./DataStructure/src/List.cpp"
#include "./DataStructure/src/Stack.cpp"
#include "./DataStructure/src/String.cpp"
// #include "HtmlParser.cpp"

using namespace std;

// int heights[200][200];
// int a[200][200];
// int found[200][200];

// void dfs(int found[][200], int i, int j, int height){
//   int x_[] = {1,0,-1,0};
//   int y_[] = {0,1,0,-1};
//   bool f = false;
//   for (int k = 0; k < 4; k++){
//     if (found[i+x_[k]][j + y_[k]] == 0 && a[i][j] > a[i+x_[k]][j + y_[k]]){
//       f = true;
//       found[i+x_[k]][j + y_[k]] = 1;
//       dfs(found, i+x_[k], j + y_[k], height + 1);
//       found[i+x_[k]][j + y_[k]] = 0;
//     }
//   }
//   if (f = false){
//     heights[i][j] = height;
//   }
// }

int main() {
  // int n, m;
  // int a[200][200];
  // cin >> n >> m;
  // for (int i = 1; i <= n; i++)
  // {
  //   for (int  j = 1; j <= m; j++)
  //   {
  //     cin >> a[i][j];
  //   }
  // }
  // dfs(found, 1, 1, 1);
  // string block_elements[] = {
  //       "address", "article", "aside", "blockquote", "canvas", "dd", "div", "dl", "dt", "fieldset", 
  //       "figcaption", "figure", "footer", "form", "h1", "h2", "h3", "h4", "h5", "h6", "header", 
  //       "hgroup", "hr", "li", "nav", "noscript", "ol", "output", "p", "pre", "section", "table", 
  //       "tfoot", "ul", "video", "html"
  //   }; 
  // for (auto & ecvt : block_elements)
  // {
  //   cout << ecvt <<" "; 
  // }
  // cout <<endl;
  string a = " <a\r\n\t  \t  adfasfa a dfa af s       asf a";
  string a1 = "<a\r\n\t  \t  adfasfa a dfa af s       asf a";
  cout << cleanAndReduceWhitespace(a) <<endl;
  cout << cleanAndReduceWhitespace(a1) <<endl;
  // string b = "<adfa>";
  // cout << b.substr(5);
    //   for (int j = 0; j < s.length(); j++)
    // {
    //   if (s[j] == '"'){     // class=" >"
    //     if (st.empty()){
    //       st.push('"');
    //     }else{
    //       st.pop();
    //     }
    //   }
      
    //   if (st.empty() and s[j] == '>'){  // End of Tag
    //     res->end_index = j;
    //   }
    //   context += s[j];
    // }

    // context = cleanAndReduceWhitespace(context);
    
    // for (int j = 0; j < context.length(); j++) // Get Tag Name
    // {
    //   if (s[j] == ' ' or s[j] == '>'){
    //     // cout << "tagname finish:" << s[j];
    //     index = j;
    //     if (tagname == "!DOCTYPE"){
    //       res->tag = tagname;
    //     }else{
    //       res->tag = toLowerCase(tagname);
    //     }
    //     break;
    //   }
    //   tagname += s[j];
    // }
  return 0;
}
