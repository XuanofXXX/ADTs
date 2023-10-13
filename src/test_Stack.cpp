#include "Stack.cpp"
#include <cassert>
#include <iostream>

using namespace std;
int main() {
  // Test default constructor
  Stack<int> s1;
  assert(s1.empty());
  assert(s1.size() == 0);

  // Test push and top
  s1.push(1);
  assert(!s1.empty());
  assert(s1.size() == 1);
  assert(s1.top() == 1);

  // Test pop
  s1.pop();
  assert(s1.empty());
  assert(s1.size() == 0);

  // Test clear
  s1.push(1);
  s1.push(2);
  s1.push(3);
  s1.clear();
  assert(s1.empty());
  assert(s1.size() == 0);

  // Test constructor with capacity
  Stack<int> s2(4);
  assert(s2.empty());
  assert(s2.size() == 0);

  // Test push and top with capacity
  s2.push(1);
  s2.push(2);
  s2.push(3);
  s2.push(4);
  assert(!s2.empty());
  assert(s2.size() == 4);
  assert(s2.top() == 4);

  // Test extend capacity
  s2.push(5);
  assert(s2.size() == 5);
  assert(s2.top() == 5);

  // Test pop with capacity
  s2.pop();
  assert(s2.size() == 4);
  assert(s2.top() == 4);

  std::cout << "All tests passed!" << std::endl;
  return 0;
}