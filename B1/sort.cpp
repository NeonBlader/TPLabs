#include "sort.hpp"

#include <stdexcept>
#include <cstring>

SortDirection convertCharIntoSortDirection(const char *direction)
{
  if (direction == nullptr) {
    throw std::invalid_argument("Direction can't be nullptr");
  }
  if (!std::strcmp(direction, "ascending")) {
    return SortDirection::ASCENDING;
  }
  if (!std::strcmp(direction, "descending")) {
    return SortDirection::DESCENDING;
  }
  throw std::invalid_argument("Invalid direction of sorting");
}
