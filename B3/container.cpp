#include "container.hpp"

#include <stdexcept>

Container::Container(std::size_t min, std::size_t max):
  min_(min),
  max_(max),
  minValue_(getFactorial(min)),
  maxValue_(getFactorial(max + 1))
{}

Container::FactorialIterator::FactorialIterator(std::size_t index, std::size_t value, const Container *container):
  index_(index),
  value_(value),
  associatedContainer_(container)
{}

Container::FactorialIterator &Container::FactorialIterator::operator++()
{
  if (index_ == associatedContainer_->max_ + 1) {
    throw std::out_of_range("Iter is already .end()");
  }
  value_ *= ++index_;
  return *this;
}

Container::FactorialIterator Container::FactorialIterator::operator++(int)
{
  FactorialIterator temp = *this;
  ++(*this);
  return temp;
}

Container::FactorialIterator &Container::FactorialIterator::operator--()
{
  if (index_ == associatedContainer_->min_) {
    throw std::out_of_range("Iter is already .begin()");
  }
  value_ /= index_--;
  return *this;
}

Container::FactorialIterator Container::FactorialIterator::operator--(int)
{
  FactorialIterator temp = *this;
  --(*this);
  return temp;
}

std::size_t &Container::FactorialIterator::operator*()
{
  if (index_ == associatedContainer_->max_+ 1) {
    throw std::out_of_range("You can't dereference .end()");
  }
  return value_;
}

bool Container::FactorialIterator::operator==(const Container::FactorialIterator &other) const
{
  return index_ == other.index_;
}

bool Container::FactorialIterator::operator!=(const Container::FactorialIterator &other) const
{
  return index_ != other.index_;
}

Container::FactorialIterator Container::begin() const
{
  return Container::FactorialIterator(min_, minValue_, this);
}

Container::FactorialIterator Container::end() const
{
  return Container::FactorialIterator(max_ + 1, maxValue_, this);
}

std::size_t Container::getFactorial(std::size_t value)
{
  std::size_t factorial = 1;
  for (std::size_t i = 2; i <= value; ++i) {
    factorial *= i;
  }
  return factorial;
}
