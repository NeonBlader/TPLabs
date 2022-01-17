#ifndef B3_SORT_HPP
#define B3_SORT_HPP

#include <memory>
#include <cstring>
#include <algorithm>
#include <stdexcept>

enum SortDirection {
  DESCENDING,
  ASCENDING
};

SortDirection convertCharIntoSortDirection(const char *direction);

template<template <class> class AppealType, typename Container>
void sort(Container &container, SortDirection direction)
{
  for (auto i = AppealType<Container>::getBegin(container); i != AppealType<Container>::getEnd(container); i++) {
    for (auto j = AppealType<Container>::getNext(i); j != AppealType<Container>::getEnd(container); j++) {

      typename Container::value_type &first = AppealType<Container>::getElement(container, i);
      typename Container::value_type &second = AppealType<Container>::getElement(container, j);

      if (((direction == ASCENDING) && (first > second)) || ((direction == DESCENDING) && (first < second))) {
        std::swap(first, second);
      }
    }
  }
}

#endif //B3_SORT_HPP
