#include "FilipVector.hpp"
#include <iostream>

int main() {
  FilipVector<int> vec;
  FilipVector<int> vec2(5);
  for (int i = 0; i < 30; ++i) {
    vec.pushBack(i);
  }
  for (int i = 0; i < 30; ++i) {
    vec2.pushBack(i + 100); //!
  }

  for (int i = 0; i < 30; ++i) {
    std::cout << vec[i] << ' ';
  }
  std::cout << '\n';
  for (int i = 0; i < 30; ++i) {
    std::cout << vec2[i] << ' ';
  }
  std::cout << '\n';
  std::cout << '\n';

  vec.swap(vec2);

  for (int i = 0; i < 30; ++i) {
    std::cout << vec[i] << ' ';
  }
  std::cout << '\n';
  for (int i = 0; i < 30; ++i) {
    std::cout << vec2[i] << ' ';
  }
  std::cout << '\n';
  std::cout << '\n';
}