#include <vector>
#include <iostream>

#include "print.hpp"

void refactorVectorWithIters(std::istream &in = std::cin, std::ostream &out = std::cout)
{
  std::vector<int> inputData;
  int currentElement = 0;
  while ((in >> currentElement) && (currentElement != 0) && (!in.eof())) {
    inputData.push_back(currentElement);
  }
  if (in.fail() && (!in.eof())) {
    throw std::ios_base::failure("Error while reading information");
  }
  if (currentElement != 0) {
    throw std::ios_base::failure("Incorrect last element");
  }
  if (inputData.empty()) {
    return;
  }
  auto iter = inputData.begin();
  if (inputData.back() == 1) {
    while (iter != inputData.end()) {
      if ((*iter % 2) == 0) {
        iter = inputData.erase(iter);
      } else {
        iter++;
      }
    }
  } else if (inputData.back() == 2) {
    while (iter != inputData.end()) {
      if ((*iter % 3) == 0) {
        iter = inputData.insert(++iter, 3, 1);
        iter += 3;
      } else {
        iter++;
      }
    }
  }
  print(inputData, out);
}
