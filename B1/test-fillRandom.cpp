#include <boost/test/unit_test.hpp>
#include <stdexcept>

#include "fillRandom.hpp"

const double PRECISION = 1e-8;
const double MIN = -1.0;
const double MAX = 1.0;
const int SIZE = 10;

BOOST_AUTO_TEST_SUITE(fillRandomTests)

  BOOST_AUTO_TEST_CASE(nullptrArrayTest)
  {
    BOOST_CHECK_THROW(fillRandom(nullptr, SIZE), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(negitiveSizeTest)
  {
    double array[SIZE];
    BOOST_CHECK_THROW(fillRandom(array, -1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(correctArgumentsNoThrowTest)
  {
    double array[SIZE];
    BOOST_CHECK_NO_THROW(fillRandom(array, SIZE));
  }

  BOOST_AUTO_TEST_CASE(bordersTest)
  {
    double array[SIZE];
    fillRandom(array, SIZE);
    for (int i = 0; i < SIZE; ++i) {
      BOOST_CHECK((array[i] >= MIN) && (array[i] <= MAX));
    }
  }

  BOOST_AUTO_TEST_CASE(randomnessTest)
  {
    double firstArray[SIZE];
    double secondArray[SIZE];
    fillRandom(firstArray, SIZE);
    fillRandom(secondArray, SIZE);
    bool isEqual = true;
    for (int i = 0; i < SIZE; ++i) {
      if (firstArray[i] - secondArray[i] <= PRECISION) {
        continue;
      } else {
        isEqual = false;
        break;
      }
    }
    BOOST_CHECK(!isEqual);
  }

BOOST_AUTO_TEST_SUITE_END()
