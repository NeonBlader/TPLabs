#include <sstream>
#include <string>
#include <cstddef>

#include <boost/test/unit_test.hpp>

#include "dataStruct.hpp"

const DataStruct DS1 = {0, 2, "Hm short"};
const DataStruct DS2 = {1, 3, "Not short"};
const DataStruct DS3 = {-3, -1, "Not shorter that short"};
const DataStruct DS4 = {0, 3, "Oh, what a large source string!"};
const DataStruct DS5 = {0, -5, "And, finally, it's largest string in this test suite"};
const DataStruct DS6 = {0, 2, "Oh, this string larger than a first DS string"};
const DataStruct DS7 = {0, 2, "Small"};

const std::string DS1_OUT = "0,2,Hm short";
const std::string DS2_OUT = "1,3,Not short";
const std::string DS3_OUT = "-3,-1,Not shorter that short";
const std::string DS4_OUT = "0,3,Oh, what a large source string!";
const std::string DS5_OUT = "0,-5,And, finally, it's largest string in this test suite";
const std::string DS6_OUT = "0,2,Oh, this string larger than a first DS string";
const std::string DS7_OUT = "0,2,Small";

const DataStruct DS_ARRAY[7] = {DS1, DS2, DS3, DS4, DS5, DS6, DS7};
const std::string DS_OUTPUT_ARRAY[7] = {DS1_OUT, DS2_OUT, DS3_OUT, DS4_OUT, DS5_OUT, DS6_OUT, DS7_OUT};

const std::size_t DS_COUNT = 7;

const std::string GOOD_IN1 = "0, -3, Correct Input";
const DataStruct DS_IN1 = {0, -3, "Correct Input"};
const std::string GOOD_IN2 = "5, -5,Some other correct input";
const DataStruct DS_IN2 = {5, -5, "Some other correct input"};
const std::string GOOD_IN3 = "2,-1,CorrectButWithNoSpaces";
const DataStruct DS_IN3 = {2, -1, "CorrectButWithNoSpaces"};
const std::string GOOD_IN4 = "0, -3,Correct Input And s o m a n y s p a c e s ";
const DataStruct DS_IN4 = {0, -3, "Correct Input And s o m a n y s p a c e s "};
const std::string GOOD_IN5 = "-2,4, Wihout space between keys";
const DataStruct DS_IN5 = {-2, 4, "Wihout space between keys"};

const std::string BAD_IN1 = "-6, -3, Less than it can be";
const std::string BAD_IN2 = "-4, 13, More than it can be";
const std::string BAD_IN3 = "a, 5, Not digit at all";
const std::string BAD_IN4 = "5, 0,";
const std::string BAD_IN5 = "Where's digits?";

const std::string CORRECT_INPUT_ARRAY[5] = {GOOD_IN1, GOOD_IN2, GOOD_IN3, GOOD_IN4, GOOD_IN5};
const std::string INVALID_INPUT_ARRAY[5] = {BAD_IN1, BAD_IN2, BAD_IN3, BAD_IN4, BAD_IN5};
const DataStruct DATA_STRUCTS_FROM_CORRENT_INPUT[5] = {DS_IN1, DS_IN2, DS_IN3, DS_IN4, DS_IN5};

const std::size_t IN_COUNT = 5;

BOOST_AUTO_TEST_SUITE(dataStructTests)

  BOOST_AUTO_TEST_CASE(comparingByFirstKeyTest)
  {
    BOOST_CHECK(DS1 < DS2);
    BOOST_CHECK(!(DS1 < DS3));
  }

  BOOST_AUTO_TEST_CASE(comparingBySecondKeyTest)
  {
    BOOST_CHECK(DS1 < DS4);
    BOOST_CHECK(!(DS1 < DS5));
  }

  BOOST_AUTO_TEST_CASE(comparingByString)
  {
    BOOST_CHECK(DS1 < DS6);
    BOOST_CHECK(!(DS1 < DS7));
  }

  BOOST_AUTO_TEST_CASE(correctInputCorrectnessOfInformationTest)
  {
    for (std::size_t i = 0; i < IN_COUNT; i++) {
      std::istringstream in(CORRECT_INPUT_ARRAY[i]);
      DataStruct dataStruct = {0, 0, ""};
      in >> dataStruct;
      BOOST_CHECK(dataStruct.key1 == DATA_STRUCTS_FROM_CORRENT_INPUT[i].key1);
      BOOST_CHECK(dataStruct.key2 == DATA_STRUCTS_FROM_CORRENT_INPUT[i].key2);
      BOOST_CHECK(dataStruct.str == DATA_STRUCTS_FROM_CORRENT_INPUT[i].str);
    }
  }

  BOOST_AUTO_TEST_CASE(correctInputNotFailBitTest)
  {
    for (std::size_t i = 0; i < IN_COUNT; i++) {
      std::istringstream in(CORRECT_INPUT_ARRAY[i]);
      DataStruct dataStruct = {0, 0, ""};
      in >> dataStruct;
      BOOST_CHECK(!in.fail());
    }
  }

  BOOST_AUTO_TEST_CASE(InvalidInputFailBitTest)
  {
    for (std::size_t i = 0; i < IN_COUNT; i++) {
      std::istringstream in(INVALID_INPUT_ARRAY[i]);
      DataStruct dataStruct = {0, 0, ""};
      in >> dataStruct;
      BOOST_CHECK(in.fail());
    }
  }

  BOOST_AUTO_TEST_CASE(outOperatorTest)
  {
    for (std::size_t i = 0; i < DS_COUNT; i++) {
      std::ostringstream out;
      out << DS_ARRAY[i];
      BOOST_CHECK(out.str() == DS_OUTPUT_ARRAY[i]);
    }
  }

BOOST_AUTO_TEST_SUITE_END()
