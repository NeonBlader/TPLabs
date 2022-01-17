#include <string>
#include <sstream>

#include <boost/test/unit_test.hpp>
#include "phoneBook.hpp"

const PhoneBook::BookNote CORRECT_NOTE = {"88005553535", "Mark Wolff"};
const PhoneBook::BookNote CORRECT_NOTE2 = {"7760342748", "Van Dark Home"};
const PhoneBook::BookNote CORRECT_NOTE3 = {"72159384512", "Billy Herrington"};
const PhoneBook::BookNote CORRECT_NOTE4 = {"73204295941", "Ricardo Milos"};
const PhoneBook::BookNote CORRECT_NOTE5 = {"733664235236", "Do u know de way"};
const PhoneBook::BookNote UNIQUE_NOTE = {"69696969696", "Unusual name"};
const PhoneBook::BookNote NOTE_WITH_INVALID_NUMBER = {"88005trap553535", "Ivanenko Inan"};
const PhoneBook::BookNote NOTE_WITH_INVALID_NUMBER2 = {"88005 553535", "Ivanenko Inan"};
const PhoneBook::BookNote NOTE_WITH_EMPTY_NUMBER = {"", "Ivanenko Inan"};
const PhoneBook::BookNote NOTES_ARRAY[5] = {CORRECT_NOTE, CORRECT_NOTE2, CORRECT_NOTE3, CORRECT_NOTE4, CORRECT_NOTE5};

const std::string DEFAULT_FIRST_BOOKMARK = {"current"};
const std::string BOOKMARK_NAME = {"First bookmark"};
const std::string BOOKMARK_NAME2 = {"Second bookmark"};
const std::string BOOKMARK_NAME3 = {"Third bookmark"};
const std::string NOT_EXISTING_BOOKMARK = {"This bookmark don't exist"};

const int MAX_STEPS_COUNT = 4;
const int EXTRA_MOVE_FORWARD_STEP = 6;
const int EXTRA_MOVE_BACKWARD_STEP = -6;
const int MAX_COUNT_OF_NOTES = 5;

BOOST_AUTO_TEST_SUITE(phoneBookTests)

  BOOST_AUTO_TEST_CASE(constructorNoThrowTest)
  {
    BOOST_CHECK_NO_THROW(PhoneBook phoneBook);
  }

  BOOST_AUTO_TEST_CASE(pushBackFirstElementNoThrowTest)
  {
    PhoneBook phoneBook;
    BOOST_CHECK_NO_THROW(phoneBook.pushBack(CORRECT_NOTE));
  }

  BOOST_AUTO_TEST_CASE(pushBackNotFirstElementNoThrowTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    BOOST_CHECK_NO_THROW(phoneBook.pushBack(CORRECT_NOTE));
    BOOST_CHECK_NO_THROW(phoneBook.pushBack(CORRECT_NOTE));
  }

  BOOST_AUTO_TEST_CASE(pushBackInvalidNumbersTest)
  {
    PhoneBook phoneBook;
    BOOST_CHECK_THROW(phoneBook.pushBack(NOTE_WITH_INVALID_NUMBER), InvalidNumber);
    BOOST_CHECK_THROW(phoneBook.pushBack(NOTE_WITH_INVALID_NUMBER2), InvalidNumber);
    BOOST_CHECK_THROW(phoneBook.pushBack(NOTE_WITH_EMPTY_NUMBER), InvalidNumber);
  }

  BOOST_AUTO_TEST_CASE(correctnessOfInformationAfterPushingBackTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    phoneBook.pushBack(CORRECT_NOTE2);
    phoneBook.pushBack(CORRECT_NOTE3);
    phoneBook.pushBack(CORRECT_NOTE4);
    auto iter = phoneBook.cbegin();

    for (std::size_t i = 0; i < phoneBook.size(); i++) {
      BOOST_CHECK((iter->number_ == NOTES_ARRAY[i].number_) && (iter->name_ == NOTES_ARRAY[i].name_));
      iter++;
    }
  }

  BOOST_AUTO_TEST_CASE(moveNoThrowWithZeroStepsTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    auto iter = phoneBook.begin();
    BOOST_CHECK_NO_THROW(phoneBook.move(iter, 0));
  }

  BOOST_AUTO_TEST_CASE(moveNoThrowNotZeroStepsTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    phoneBook.pushBack(CORRECT_NOTE2);
    phoneBook.pushBack(CORRECT_NOTE3);
    phoneBook.pushBack(CORRECT_NOTE4);
    phoneBook.pushBack(CORRECT_NOTE5);
    auto iter = phoneBook.begin();

    for (int i = 1; i <= MAX_STEPS_COUNT; ++i) {
      BOOST_CHECK_NO_THROW(iter = phoneBook.move(iter, i));
      BOOST_CHECK_NO_THROW(iter = phoneBook.move(iter, i * -1));
    }
  }

  BOOST_AUTO_TEST_CASE(moveThrowTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    phoneBook.pushBack(CORRECT_NOTE2);
    phoneBook.pushBack(CORRECT_NOTE3);
    phoneBook.pushBack(CORRECT_NOTE4);
    phoneBook.pushBack(CORRECT_NOTE5);
    auto iter = phoneBook.begin();

    BOOST_CHECK_THROW(phoneBook.move(iter, EXTRA_MOVE_FORWARD_STEP), std::invalid_argument);
    iter = phoneBook.end();
    BOOST_CHECK_THROW(phoneBook.move(iter, EXTRA_MOVE_BACKWARD_STEP), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(checkMoveToCorrectNoteByMove)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    phoneBook.pushBack(CORRECT_NOTE2);
    phoneBook.pushBack(CORRECT_NOTE3);
    phoneBook.pushBack(CORRECT_NOTE4);
    phoneBook.pushBack(CORRECT_NOTE5);
    auto iter = phoneBook.begin();

    for (std::size_t i = 0; i < phoneBook.size(); i++) {
      iter = phoneBook.move(iter, i);
      BOOST_CHECK((iter->number_ == NOTES_ARRAY[i].number_) && (iter->name_ == NOTES_ARRAY[i].name_));
      iter = phoneBook.move(iter, -i);
      BOOST_CHECK((iter->number_ == NOTES_ARRAY[0].number_) && (iter->name_ == NOTES_ARRAY[0].name_));
    }
  }

  BOOST_AUTO_TEST_CASE(insertBeforeInEptyPhoneBookNoThrowTest)
  {
    PhoneBook phoneBook;
    auto iter = phoneBook.begin();
    BOOST_CHECK_NO_THROW(phoneBook.insertBefore(iter, CORRECT_NOTE));
  }

  BOOST_AUTO_TEST_CASE(insertBeforeEndNoThrowTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    phoneBook.pushBack(CORRECT_NOTE2);
    phoneBook.pushBack(CORRECT_NOTE3);
    phoneBook.pushBack(CORRECT_NOTE4);
    phoneBook.pushBack(CORRECT_NOTE5);
    auto iter = phoneBook.end();
    BOOST_CHECK_NO_THROW(phoneBook.insertBefore(iter, CORRECT_NOTE));
  }

  BOOST_AUTO_TEST_CASE(insertBeforeInMiddleNoThrowTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    phoneBook.pushBack(CORRECT_NOTE2);
    phoneBook.pushBack(CORRECT_NOTE3);
    phoneBook.pushBack(CORRECT_NOTE4);
    phoneBook.pushBack(CORRECT_NOTE5);

    for (auto iter = phoneBook.begin(); iter != phoneBook.end(); iter++) {
      BOOST_CHECK_NO_THROW(phoneBook.insertBefore(iter, CORRECT_NOTE));
    }
  }

  BOOST_AUTO_TEST_CASE(insertBeforeThrowTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    auto iter = phoneBook.begin();
    BOOST_CHECK_THROW(phoneBook.insertBefore(iter, NOTE_WITH_INVALID_NUMBER), InvalidNumber);
  }

  BOOST_AUTO_TEST_CASE(insertBeforeCorectnessOfInsertedInformationTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    phoneBook.pushBack(CORRECT_NOTE2);
    phoneBook.pushBack(CORRECT_NOTE3);
    phoneBook.pushBack(CORRECT_NOTE4);
    phoneBook.pushBack(CORRECT_NOTE5);

    for (auto iter = phoneBook.begin(); iter != phoneBook.end(); iter++) {
      phoneBook.insertBefore(iter, CORRECT_NOTE);
      BOOST_CHECK((std::prev(iter)->name_ == CORRECT_NOTE.name_) && (std::prev(iter)->number_ == CORRECT_NOTE.number_));
    }
  }

  BOOST_AUTO_TEST_CASE(insertAfterEndThrowTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    auto iter = phoneBook.end();
    BOOST_CHECK_THROW(phoneBook.insertAfter(iter, CORRECT_NOTE), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(insertAfterInMiddleNoThrowTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    phoneBook.pushBack(CORRECT_NOTE2);
    phoneBook.pushBack(CORRECT_NOTE3);
    phoneBook.pushBack(CORRECT_NOTE4);
    phoneBook.pushBack(CORRECT_NOTE5);

    for (auto iter = std::prev(phoneBook.end()); iter != phoneBook.begin(); iter--) {
      BOOST_CHECK_NO_THROW(phoneBook.insertAfter(iter, CORRECT_NOTE));
    }
  }

  BOOST_AUTO_TEST_CASE(insertAfterThrowTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    auto iter = phoneBook.begin();
    BOOST_CHECK_THROW(phoneBook.insertAfter(iter, NOTE_WITH_INVALID_NUMBER), InvalidNumber);
  }

  BOOST_AUTO_TEST_CASE(insertAfterCorectnessOfInsertedInformationTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    phoneBook.pushBack(CORRECT_NOTE2);
    phoneBook.pushBack(CORRECT_NOTE3);
    phoneBook.pushBack(CORRECT_NOTE4);
    phoneBook.pushBack(CORRECT_NOTE5);

    for (auto iter = std::prev(phoneBook.end()); iter != phoneBook.begin(); iter--) {
      phoneBook.insertAfter(iter, CORRECT_NOTE);
      BOOST_CHECK((std::next(iter)->name_ == CORRECT_NOTE.name_) && (std::next(iter)->number_ == CORRECT_NOTE.number_));
    }
  }

  BOOST_AUTO_TEST_CASE(replaceNoThrowTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    auto iter = phoneBook.begin();
    BOOST_CHECK_NO_THROW(phoneBook.replace(iter, CORRECT_NOTE));
  }

  BOOST_AUTO_TEST_CASE(replaceInvalidNumberThrowTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    auto iter = phoneBook.begin();
    BOOST_CHECK_THROW(phoneBook.replace(iter, NOTE_WITH_INVALID_NUMBER), InvalidNumber);
  }

  BOOST_AUTO_TEST_CASE(replaceEndIterThrowTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    auto iter = phoneBook.end();
    BOOST_CHECK_THROW(phoneBook.replace(iter, CORRECT_NOTE), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(replaceCorrectnessOfReplacesInformationTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    phoneBook.pushBack(CORRECT_NOTE2);
    phoneBook.pushBack(CORRECT_NOTE3);
    phoneBook.pushBack(CORRECT_NOTE4);
    phoneBook.pushBack(CORRECT_NOTE5);

    for (auto iter = phoneBook.begin(); iter != phoneBook.end() ; iter++) {
      phoneBook.replace(iter, UNIQUE_NOTE);
      BOOST_CHECK((iter->name_ == UNIQUE_NOTE.name_) && (iter->number_ == UNIQUE_NOTE.number_));
    }
  }

  BOOST_AUTO_TEST_CASE(eraseBeginNoThrowTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    phoneBook.pushBack(CORRECT_NOTE2);
    auto iter = phoneBook.begin();
    BOOST_CHECK_NO_THROW(phoneBook.erase(iter));
  }

  BOOST_AUTO_TEST_CASE(eraseLastElementNoThrowTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    phoneBook.pushBack(CORRECT_NOTE2);
    auto iter = std::next(phoneBook.begin());
    BOOST_CHECK_NO_THROW(phoneBook.erase(iter));
  }

  BOOST_AUTO_TEST_CASE(eraseFromMiddleNoThrowTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    phoneBook.pushBack(CORRECT_NOTE2);
    phoneBook.pushBack(CORRECT_NOTE3);
    auto iter = std::next(phoneBook.begin());
    BOOST_CHECK_NO_THROW(phoneBook.erase(iter));
  }

  BOOST_AUTO_TEST_CASE(eraseEndThrowTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    auto iter = phoneBook.end();
    BOOST_CHECK_THROW(phoneBook.erase(iter), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(eraseCorrectCountChangingTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    phoneBook.pushBack(CORRECT_NOTE2);
    phoneBook.pushBack(CORRECT_NOTE3);
    phoneBook.pushBack(CORRECT_NOTE4);
    phoneBook.pushBack(CORRECT_NOTE5);
    auto iter = phoneBook.begin();

    for (int i = 1; i <= 5; ++i) {
      phoneBook.erase(iter);
      BOOST_CHECK(static_cast<int>(phoneBook.size()) == MAX_COUNT_OF_NOTES - i);
    }
  }

  BOOST_AUTO_TEST_CASE(eraseCorrectMoveToNextIterTest)
  {
    PhoneBook phoneBook;
    phoneBook.pushBack(CORRECT_NOTE);
    phoneBook.pushBack(CORRECT_NOTE2);
    phoneBook.pushBack(CORRECT_NOTE3);
    phoneBook.pushBack(CORRECT_NOTE4);
    phoneBook.pushBack(CORRECT_NOTE5);
    auto iter = phoneBook.begin();

    while (iter != phoneBook.end()) {
      auto nextIter = std::next(iter);
      phoneBook.erase(iter);
      BOOST_CHECK(iter == nextIter);
    }
  }

BOOST_AUTO_TEST_SUITE_END()
