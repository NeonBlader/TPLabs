#include <boost/test/unit_test.hpp>
#include <iostream>
#include <stdexcept>

void readTextAndOut(const char *fileName);

BOOST_AUTO_TEST_SUITE(readTextAndOutTests)

  BOOST_AUTO_TEST_CASE(nullptrFileNameTest)
  {
    BOOST_CHECK_THROW(readTextAndOut(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(invalidFileNameTest)
  {
    BOOST_CHECK_THROW(readTextAndOut("Absolutely wrong file name......."), std::ios_base::failure);
  }

BOOST_AUTO_TEST_SUITE_END()
