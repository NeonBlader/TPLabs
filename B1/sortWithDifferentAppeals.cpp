#include <vector>
#include <forward_list>
#include <iostream>
#include <stdexcept>

#include "BracketAppeal.hpp"
#include "AtAppeal.hpp"
#include "IterAppeal.hpp"
#include "sort.hpp"
#include "print.hpp"

void sortWithDifferentAccess(const char *direction, std::istream &in = std::cin, std::ostream &out = std::cout)
{
  SortDirection sortDirection = convertCharIntoSortDirection(direction);
  std::vector<int> bracketVector;
  int value = 0;
  while ((!in.eof()) && (in >> value)) {
    bracketVector.push_back(value);
  }
  if ((in.fail()) && (!in.eof())) {
    throw std::ios_base::failure("Incorrect input information");
  }
  if (bracketVector.empty()) {
    return;
  }
  std::forward_list<int> iterList(bracketVector.begin(), bracketVector.end());
  std::vector<int> atVector(bracketVector);

  sort<BracketAppeal, std::vector<int>>(bracketVector, sortDirection);
  print(bracketVector, out);
  out << '\n';

  sort<AtAppeal, std::vector<int>>(atVector, sortDirection);
  print(atVector, out);
  out << '\n';

  sort<IterAppeal, std::forward_list<int>>(iterList, sortDirection);
  print(iterList, out);
  out << '\n';
}
