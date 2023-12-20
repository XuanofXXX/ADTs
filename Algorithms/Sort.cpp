#include <vector>
#define T int

using namespace std;

void InsertSort(vector<T> &list) {
  for (int i = 1; i < list.size(); i++) {
    T cur = list[i];
    int j = i - 1;
    while ((j >= 0) && (list[j] > cur)) {
      list[j + 1] = list[j];
      j--;
    }
    list[j + 1] = cur;
  }
}

void BubbleSort(vector<T> &list) {
  for (int i = 0; i < list.size(); i++) {
    for (int j = 0; j < list.size() - 1 - i; j++) {
      if (list[j] > list[j+1]){
        T temp = list[j];
        list[j] = list[j+1];
        list[j+1] = temp;
      }
    }
  }
}

void ShellSort(vector<T> &list){


  return ;
}