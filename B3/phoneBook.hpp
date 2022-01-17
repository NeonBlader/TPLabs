#ifndef B3_PHONEBOOK_HPP
#define B3_PHONEBOOK_HPP

#include <string>
#include <list>
#include <iosfwd>
#include <cstddef>
#include <map>

#include "phoneBookExceptions.hpp"

class PhoneBook {
public:
  struct BookNote {
    std::string number_;
    std::string name_;
  };

  friend std::ostream& operator<<(std::ostream &out, const std::list<BookNote>::iterator iter);

  std::list<BookNote>::iterator move(std::list<BookNote>::iterator &iter, int stepsCount) const;
  void insertBefore(const std::list<BookNote>::const_iterator &iter, const BookNote &note);
  void insertAfter(const std::list<BookNote>::const_iterator &iter, const BookNote &note);
  void pushBack(const BookNote &note);
  void replace(std::list<BookNote>::iterator &iter, const BookNote &note);
  void erase(std::list<BookNote>::iterator &iter);
  std::list<BookNote>::iterator begin();
  std::list<BookNote>::iterator end();
  std::list<BookNote>::const_iterator cbegin() const;
  std::list<BookNote>::const_iterator cend() const;
  std::size_t size() const;

private:
  std::list<BookNote> notes_;

  bool checkNumberCorrectness(const std::string &number) const;
};


#endif //B3_PHONEBOOK_HPP
