#include <vector>
#include <stdexcept>
#include <iostream>

#include "BracketAppeal.hpp"
#include "sort.hpp"
#include "fillRandom.hpp"
#include "print.hpp"

void fillRandomAndSort(const char *direction, std::size_t vectorSize, std::ostream &out = std::cout)
{
  SortDirection sortDirection = convertCharIntoSortDirection(direction);

  std::vector<double> array(vectorSize);
  fillRandom(array.data(), vectorSize);

  print(array, out);
  sort<BracketAppeal, std::vector<double>>(array, sortDirection);
  out << '\n';
  print(array, out);
}
