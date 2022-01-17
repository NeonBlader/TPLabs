#ifndef B3_PRINT_HPP
#define B3_PRINT_HPP

#include <iostream>

template<typename Container>
void print(const Container& container, std::ostream &out)
{
  for (typename Container::const_iterator i = container.begin(); i != container.end(); ++i) {
    out << *i << ' ';
  }
}

#endif //B3_PRINT_HPP
