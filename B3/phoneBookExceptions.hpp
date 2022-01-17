#ifndef B3_PHONEBOOKEXCEPTIONS_HPP
#define B3_PHONEBOOKEXCEPTIONS_HPP

#include <stdexcept>


class InvalidBookmarkName: public std::exception {
public:
  InvalidBookmarkName():
    errorText_("Invalid bookmark name")
  {}
  const char *what() const noexcept override {return errorText_;}
private:
  const char *errorText_;
};

class InvalidNumber: public std::exception {
public:
  InvalidNumber():
    errorText_("Invalid number (contains not a digit)")
  {}
  const char *what() const noexcept override {return errorText_;}
private:
  const char *errorText_;
};

class PhoneBookUnderflow: public std::exception {
public:
  PhoneBookUnderflow():
    errorText_("Invalid number (contains not a digit)")
  {}
  const char *what() const noexcept override {return errorText_;}
private:
  const char *errorText_;
};

#endif //B3_PHONEBOOKEXCEPTIONS_HPP
