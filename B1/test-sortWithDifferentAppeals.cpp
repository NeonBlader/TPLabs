#include <boost/test/unit_test.hpp>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

void sortWithDifferentAccess(const char *direction, std::istream &in = std::cin, std::ostream &out = std::cout);

const std::string CORRECT_INPUT("11 16 0 -4 6 3 6 -3 66 -21");
const std::string INVALID_INPUT("11 16 0 4 2 trap");
const std::string EMPTY_INPUT;
const std::string ASCENDING_OUTPUT("-21 -4 -3 0 3 6 6 11 16 66 \n-21 -4 -3 0 3 6 6 11 16 66 \n-21 -4 -3 0 3 6 6 11 16 66 \n");
const std::string DESCENDING_OUTPUT("66 16 11 6 6 3 0 -3 -4 -21 \n66 16 11 6 6 3 0 -3 -4 -21 \n66 16 11 6 6 3 0 -3 -4 -21 \n");

BOOST_AUTO_TEST_SUITE(sortWithDifferentAppealsTests)

  BOOST_AUTO_TEST_CASE(nullptrDirectionTest)
  {
    std::istringstream in(CORRECT_INPUT);
    BOOST_CHECK_THROW(sortWithDifferentAccess(nullptr, in), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(invalidInputDataTest)
  {
    std::istringstream in(INVALID_INPUT);
    BOOST_CHECK_THROW(sortWithDifferentAccess("ascending", in), std::ios_base::failure);
  }

  BOOST_AUTO_TEST_CASE(correctInputNoThrowTest)
  {
    std::istringstream in(CORRECT_INPUT);
    BOOST_CHECK_NO_THROW(sortWithDifferentAccess("ascending", in));
  }

  BOOST_AUTO_TEST_CASE(correctAscendingOutputTest)
  {
    std::istringstream in(CORRECT_INPUT);
    std::ostringstream out;
    sortWithDifferentAccess("ascending", in, out);
    BOOST_CHECK(out.str() == ASCENDING_OUTPUT);
  }

  BOOST_AUTO_TEST_CASE(correctDescendingOutputTest)
  {
    std::istringstream in(CORRECT_INPUT);
    std::ostringstream out;
    sortWithDifferentAccess("descending", in, out);
    BOOST_CHECK(out.str() == DESCENDING_OUTPUT);
  }

  BOOST_AUTO_TEST_CASE(correctAscendingEmptyOutputTest)
  {
    std::istringstream in(EMPTY_INPUT);
    std::ostringstream out;
    sortWithDifferentAccess("ascending", in, out);
    BOOST_CHECK(out.str().empty());
  }

  BOOST_AUTO_TEST_CASE(correctDescendingEmptyOutputTest)
  {
    std::istringstream in(EMPTY_INPUT);
    std::ostringstream out;
    sortWithDifferentAccess("descending", in, out);
    BOOST_CHECK(out.str().empty());
  }
BOOST_AUTO_TEST_SUITE_END()
