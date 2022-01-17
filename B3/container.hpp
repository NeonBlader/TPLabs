#ifndef B3_CONTAINER_HPP
#define B3_CONTAINER_HPP

#include <cstddef>
#include <iterator>

class Container {
public:
  class FactorialIterator;

  Container(std::size_t min, std::size_t max);
  FactorialIterator begin() const;
  FactorialIterator end() const;

private:
  std::size_t min_;
  std::size_t max_;
  std::size_t minValue_;
  std::size_t maxValue_;

  std::size_t getFactorial(std::size_t value);
};

class Container::FactorialIterator: public std::iterator<std::bidirectional_iterator_tag, std::size_t,
    std::size_t, const std::size_t*, std::size_t> {
public:
  friend class Container;

  FactorialIterator &operator++();
  FactorialIterator operator++(int);
  FactorialIterator &operator--();
  FactorialIterator operator--(int);
  std::size_t &operator*();
  bool operator==(const FactorialIterator& other) const;
  bool operator!=(const FactorialIterator& other) const;

private:
  FactorialIterator(std::size_t index, std::size_t value, const Container *container);

  std::size_t index_;
  std::size_t value_;
  const Container *associatedContainer_;
};

#endif //B3_CONTAINER_HPP
