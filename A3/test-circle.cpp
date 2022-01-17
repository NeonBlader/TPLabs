#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>

#include "circle.hpp"

const double X = 3.0;
const double Y = 4.0;
const double RADIUS = 8;
const double COEFFICIENT = 2.5;
const double X_FOR_MOVING = 9;
const double Y_FOR_MOVING = 11.4;
const double AREA = M_PI * std::pow(RADIUS, 2);
const double PRECISION = 1e-8;

BOOST_AUTO_TEST_SUITE(circleTests)

  BOOST_AUTO_TEST_CASE(noThrowConstructorTest)
  {
    BOOST_CHECK_NO_THROW(kurenkov::Circle circle(RADIUS, {X, Y}));
  }

  BOOST_AUTO_TEST_CASE(invalidRadiusConstructorTest)
  {
    BOOST_CHECK_THROW(kurenkov::Circle(-RADIUS, {X, Y}), std::invalid_argument);
    BOOST_CHECK_THROW(kurenkov::Circle(0.0, {X, Y}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(getRadiusTest)
  {
    kurenkov::Circle circle(RADIUS, {X, Y});
    BOOST_CHECK_CLOSE(RADIUS, circle.getRadius(), PRECISION);
  }

  BOOST_AUTO_TEST_CASE(getCenterTest)
  {
    kurenkov::Circle circle(RADIUS, {X, Y});
    BOOST_CHECK_CLOSE(X, circle.getCenter().x, PRECISION);
    BOOST_CHECK_CLOSE(Y, circle.getCenter().y, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(getAreaTest)
  {
    kurenkov::Circle circle(RADIUS, {X, Y});
    BOOST_CHECK_CLOSE(circle.getArea(), AREA, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(getFrameRectTest)
  {
    kurenkov::Circle circle(RADIUS, {X, Y});
    BOOST_CHECK_CLOSE(RADIUS * 2, circle.getFrameRect().height, PRECISION);
    BOOST_CHECK_CLOSE(RADIUS * 2, circle.getFrameRect().width, PRECISION);
    BOOST_CHECK_CLOSE(X, circle.getFrameRect().pos.x, PRECISION);
    BOOST_CHECK_CLOSE(Y, circle.getFrameRect().pos.y, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(relativeMoveCenterChangeTest)
  {
    kurenkov::Circle circle(RADIUS, {X, Y});
    circle.move(X_FOR_MOVING, Y_FOR_MOVING);
    BOOST_CHECK_CLOSE(X + X_FOR_MOVING, circle.getCenter().x, PRECISION);
    BOOST_CHECK_CLOSE(Y + Y_FOR_MOVING, circle.getCenter().y, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(relativeMoveCharacteristicsPermanenceTest)
  {
    kurenkov::Circle circle(RADIUS, {X, Y});
    circle.move(X_FOR_MOVING, Y_FOR_MOVING);
    BOOST_CHECK_CLOSE(RADIUS, circle.getRadius(), PRECISION);
    BOOST_CHECK_CLOSE(AREA, circle.getArea(), PRECISION);
  }

  BOOST_AUTO_TEST_CASE(absoluteMoveCenterChangeTest)
  {
    kurenkov::Circle circle(RADIUS, {X, Y});
    circle.move({X_FOR_MOVING, Y_FOR_MOVING});
    BOOST_CHECK_CLOSE(X_FOR_MOVING, circle.getCenter().x, PRECISION);
    BOOST_CHECK_CLOSE(Y_FOR_MOVING, circle.getCenter().y, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(absoluteMoveCharacteristicsPermanenceTest)
  {
    kurenkov::Circle circle(RADIUS, {X, Y});
    circle.move({X_FOR_MOVING, Y_FOR_MOVING});
    BOOST_CHECK_CLOSE(RADIUS, circle.getRadius(), PRECISION);
    BOOST_CHECK_CLOSE(AREA, circle.getArea(), PRECISION);
  }

  BOOST_AUTO_TEST_CASE(correctScaleCoefficientTest)
  {
    kurenkov::Circle circle(RADIUS, {X, Y});
    BOOST_CHECK_NO_THROW(circle.scale(COEFFICIENT));
  }

  BOOST_AUTO_TEST_CASE(invalidScaleCoefficientTest)
  {
    kurenkov::Circle circle(RADIUS, {X, Y});
    BOOST_CHECK_THROW(circle.scale(-COEFFICIENT), std::invalid_argument);
    BOOST_CHECK_THROW(circle.scale(0.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(scaleCharacteristicsChangeTest)
  {
    kurenkov::Circle circle(RADIUS, {X, Y});
    circle.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(RADIUS * COEFFICIENT, circle.getRadius(), PRECISION);
    BOOST_CHECK_CLOSE(AREA * std::pow(COEFFICIENT, 2), circle.getArea(), PRECISION);
  }

  BOOST_AUTO_TEST_CASE(permanenceOfCenterAfterScaleTest)
  {
    kurenkov::Circle circle(RADIUS, {X, Y});
    circle.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(X, circle.getCenter().x, PRECISION);
    BOOST_CHECK_CLOSE(Y, circle.getCenter().y, PRECISION);
  }

BOOST_AUTO_TEST_SUITE_END()
