#include <boost/test/unit_test.hpp>
#include "container.hpp"

const int FACTORIALS[10] = {1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};
const int MIN = 1;
const int MAX = 10;

BOOST_AUTO_TEST_SUITE(containerTests)

  BOOST_AUTO_TEST_CASE(containerConstructorNoThrowTest)
  {
    BOOST_CHECK_NO_THROW(Container container(MIN, MAX));
  }

  BOOST_AUTO_TEST_CASE(containerBeginNoThrowTest)
  {
    Container container(MIN, MAX);
    BOOST_CHECK_NO_THROW(container.begin());
  }

  BOOST_AUTO_TEST_CASE(containerEndNoThrowTest)
  {
    Container container(MIN, MAX);
    BOOST_CHECK_NO_THROW(container.end());
  }

  BOOST_AUTO_TEST_CASE(preIncrementNoThrowTest)
  {
    Container container(MIN, MAX);
    auto iter = container.begin();
    for (int i = MIN; i <= MAX; ++i) {
      BOOST_CHECK_NO_THROW(++iter);
    }
  }

  BOOST_AUTO_TEST_CASE(preIncrementationOfEndTest)
  {
    Container container(MIN, MAX);
    auto iter = container.end();
    BOOST_CHECK_THROW(++iter, std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(postIncrementNoThrowTest)
  {
    Container container(MIN, MAX);
    auto iter = container.begin();
    for (int i = MIN; i <= MAX; ++i) {
      BOOST_CHECK_NO_THROW(iter++);
    }
  }

  BOOST_AUTO_TEST_CASE(postIncrementationOfEndTest)
  {
    Container container(MIN, MAX);
    auto iter = container.end();
    BOOST_CHECK_THROW(iter++, std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(preDecrementNoThrowTest)
  {
    Container container(MIN, MAX);
    auto iter = container.end();
    for (int i = MIN; i <= MAX; ++i) {
      BOOST_CHECK_NO_THROW(--iter);
    }
  }

  BOOST_AUTO_TEST_CASE(preDecrementationOfBeginTest)
  {
    Container container(MIN, MAX);
    auto iter = container.begin();
    BOOST_CHECK_THROW(--iter, std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(postDecrementNoThrowTest)
  {
    Container container(MIN, MAX);
    auto iter = container.end();
    for (int i = MIN; i <= MAX; ++i) {
      BOOST_CHECK_NO_THROW(iter--);
    }
  }

  BOOST_AUTO_TEST_CASE(postDecrementationOfBeginTest)
  {
    Container container(MIN, MAX);
    auto iter = container.begin();
    BOOST_CHECK_THROW(iter--, std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(dereferenceByPreIncrementationCorrectnessTest)
  {
    Container container(MIN, MAX);
    auto iter = container.begin();
    for (int i = 0; i <= MAX - 1; ++i) {
      BOOST_CHECK_EQUAL(*iter, FACTORIALS[i]);
      ++iter;
    }
  }

  BOOST_AUTO_TEST_CASE(dereferenceByPostIncrementationCorrectnessTest)
  {
    Container container(MIN, MAX);
    auto iter = container.begin();
    for (int i = 0; i <= MAX - 1; ++i) {
      BOOST_CHECK_EQUAL(*iter, FACTORIALS[i]);
      iter++;
    }
  }

  BOOST_AUTO_TEST_CASE(dereferenceByPreDecrementationCorrectnessTest) //
  {
    Container container(MIN, MAX);
    auto iter = container.end();
    for (int i = MAX - 1; i >= 0; --i) {
      --iter;
      BOOST_CHECK_EQUAL(*iter, FACTORIALS[i]);
      if (iter == container.begin()) {
        break;
      }
    }
  }

  BOOST_AUTO_TEST_CASE(dereferenceByPostDecrementationCorrectnessTest)//
  {
    Container container(MIN, MAX);
    auto iter = container.end();
    for (int i = MAX - 1; i >= 0; --i) {
      iter--;
      BOOST_CHECK_EQUAL(*iter, FACTORIALS[i]);
      if (iter == container.begin()) {
        break;
      }
    }
  }

  BOOST_AUTO_TEST_CASE(equalityOperatorTest)
  {
    Container container(MIN, MAX);
    auto iter = container.begin();
    auto secondIter = container.begin();
    for (int i = 1; i <= MAX; ++i) {
      BOOST_CHECK(iter == secondIter);
      iter++;
      secondIter++;
    }
  }

  BOOST_AUTO_TEST_CASE(notEqualityOperatorTest)
  {
    Container container(MIN, MAX);
    auto iter = container.begin();
    auto secondIter = container.begin();
    secondIter++;
    for (int i = 1; i < MAX; ++i) {
      BOOST_CHECK(iter != secondIter);
      iter++;
      secondIter++;
    }
  }

  BOOST_AUTO_TEST_CASE(postIncrementNoChangingWhileOperationsTest)
  {
    Container container(MIN, MAX);
    auto iter = container.begin();
    auto secondIter = container.begin();
    for (int i = 1; i <= MAX; ++i) {
      BOOST_CHECK(iter++ == secondIter);
      secondIter++;
    }
  }

  BOOST_AUTO_TEST_CASE(postDecrementationNoChangingWhileOperationsTest)
  {
    Container container(MIN, MAX);
    auto iter = container.end();
    auto secondIter = container.end();
    for (int i = 0; i <= MAX - 1; ++i) {
      BOOST_CHECK(iter-- == secondIter);
      secondIter--;
    }
  }

BOOST_AUTO_TEST_SUITE_END()
