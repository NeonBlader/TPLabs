#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "dataStruct.hpp"

int main()
{
  std::vector<DataStruct> structs((std::istream_iterator<DataStruct>(std::cin)), std::istream_iterator<DataStruct>());
  if (std::cin.bad()) {
    std::cerr << "Invalid input data";
    return 1;
  }
  if (!std::cin.eof()) {
    std::cerr << "Error while reading";
    return 1;
  }
  std::sort(structs.begin(), structs.end());
  std::copy(structs.cbegin(), structs.cend(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
  return 0;
}
