#include "phoneBook.hpp"

#include <stdexcept>
#include <ostream>

std::list<PhoneBook::BookNote>::iterator PhoneBook::move(std::list<PhoneBook::BookNote>::iterator &iter, int stepsCount) const
{
  auto tempIter = iter;
  if (stepsCount < 0) {
    for (int i = 0; i > stepsCount; --i) {
      if (tempIter == cbegin()) {
        throw std::invalid_argument("Steps count more than a count of previous notes");
      }
      tempIter--;
    }
  } else {
    for (int i = 0; i < stepsCount; ++i) {
      if (tempIter == cend()) {
        throw std::invalid_argument("Steps count more than a count of next notes");
      }
      tempIter++;
    }
  }
  iter = tempIter;
  return iter;
}

void PhoneBook::insertBefore(const std::list<PhoneBook::BookNote>::const_iterator &iter, const PhoneBook::BookNote &note)
{
  if (!checkNumberCorrectness(note.number_)) {
    throw InvalidNumber();
  }
  if (notes_.empty()) {
    pushBack(note);
  } else {
    notes_.insert(iter, note);
  }
}

void PhoneBook::insertAfter(const std::list<PhoneBook::BookNote>::const_iterator &iter, const PhoneBook::BookNote &note)
{
  if (!checkNumberCorrectness(note.number_)) {
    throw InvalidNumber();
  }
  if ((iter == notes_.end()) && (!notes_.empty())) {
    throw std::invalid_argument("You can't push note after .end()");
  }
  if (notes_.empty()) {
    pushBack(note);
  } else {
    notes_.insert(std::next(iter), note);
  }
}

void PhoneBook::pushBack(const PhoneBook::BookNote &note)
{
  if (!checkNumberCorrectness(note.number_)) {
    throw InvalidNumber();
  }
  notes_.push_back(note);
}

void PhoneBook::replace(std::list<PhoneBook::BookNote>::iterator &iter, const PhoneBook::BookNote &note)
{
  if (!checkNumberCorrectness(note.number_)) {
    throw InvalidNumber();
  }
  if (iter == notes_.end()) {
    throw std::invalid_argument("You can't replace .end() iterator");
  }
  *iter = note;
}

void PhoneBook::erase(std::list<PhoneBook::BookNote>::iterator &iter)
{
  if (iter == notes_.end()) {
    throw std::invalid_argument("You can't erase .end() iterator");
  }
  auto tempIter = iter;
  tempIter++;
  notes_.erase(iter);
  iter = tempIter;
}

std::list<PhoneBook::BookNote>::iterator PhoneBook::begin()
{
  return notes_.begin();
}

std::list<PhoneBook::BookNote>::iterator PhoneBook::end()
{
  return notes_.end();
}

std::list<PhoneBook::BookNote>::const_iterator PhoneBook::cbegin() const
{
  return notes_.cbegin();
}

std::list<PhoneBook::BookNote>::const_iterator PhoneBook::cend() const
{
  return notes_.cend();
}

std::size_t PhoneBook::size() const
{
  return notes_.size();
}

std::ostream &operator<<(std::ostream &out, const std::list<PhoneBook::BookNote>::iterator iter)
{
  out << iter->number_ << " " << iter->name_;
  return out;
}

bool PhoneBook::checkNumberCorrectness(const std::string &number) const
{
  if (number.empty()) {
    return false;
  }
  auto iter = number.begin();
  while (iter != number.end()) {
    if (!isdigit(*iter)) {
      return false;
    }
    iter++;
  }
  return true;
}
