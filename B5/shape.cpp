#include <iostream>
#include <utility>
#include <cmath>
#include <iterator>
#include <cstddef>

#include "shape.hpp"
#include "streamManipulators.hpp"

std::istream &operator>>(std::istream &in, Shape &shape)
{
  std::size_t topsCount = 0;
  in >> std::ws >> topsCount;
  if ((in.fail()) || (topsCount < COUNT_OF_VERTICES_OF_TRIANGLE) || in.eof()) {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  shape.clear();
  Point point = {0, 0};
  for (std::size_t i = 0; i < topsCount; ++i) {
    in >> point;
    if (in.fail()) {
      if (in.eof()) {
        in.clear();
        in.setstate(std::ios_base::failbit);
      }
      return in;
    }
    shape.push_back(point);
  }
  return in;
}

std::ostream &operator<<(std::ostream &out, const Shape &shape)
{
  out << shape.size() << ' ';
  std::copy(shape.begin(), shape.end(), std::ostream_iterator<Point>(out, " "));
  return out;
}

std::istream &operator>>(std::istream &in, Point &point)
{
  std::pair<char, char> brackets({'\0', '\0'});
  std::pair<int, int> coordinates({0, 0});
  char semicolon = '\0';
  in >> skipWsOnly >> std::noskipws >> brackets.first >> skipWsOnly >> std::noskipws >> coordinates.first >> skipWsOnly
      >> std::noskipws >> semicolon >> skipWsOnly >> std::noskipws >> coordinates.second >> skipWsOnly >> std::noskipws >> brackets.second;
  if ((in.fail()) || (brackets.first != '(') || (brackets.second != ')') || (semicolon != ';')) {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  point = {coordinates.first, coordinates.second};
  return in;
}


std::ostream &operator<<(std::ostream &out, const Point &point)
{
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

bool operator<(const Shape &left, const Shape &right)
{
  if (left.size() != right.size()) {
    return left.size() < right.size();
  }
  if (!isRectangle(right)) {
    return isRectangle(left);
  }
  return isSquare(left) && isRectangle(right) && !isSquare(right);
}

std::size_t getDistanceSquare(const Point &firstPoint, const Point &secondPoint)
{
  return static_cast<std::size_t>(std::pow(firstPoint.x - secondPoint.x, 2) + std::pow(firstPoint.y - secondPoint.y, 2));
}

bool isSquare(const Shape &shape)
{
  return (isRectangle(shape)) && (getDistanceSquare(shape[0], shape[1]) == getDistanceSquare(shape[0], shape[3]));
}

bool isRectangle(const Shape &shape)
{
  if (shape.size() != COUNT_OF_VERTICES_OF_QUADRANGLE) {
    return false;
  }
  return ((shape[2].x - shape[1].x) * (shape[0].x - shape[1].x) + (shape[2].y - shape[1].y) * (shape[0].y - shape[1].y) == 0)
      && ((shape[2].x - shape[3].x) * (shape[0].x - shape[3].x) + (shape[2].y - shape[3].y) * (shape[0].y - shape[3].y) == 0);
}

bool isPentagon(const Shape &shape)
{
  return shape.size() == COUNT_OF_VERTICES_OF_PENTAGON;
}

bool isQuadrangle(const Shape &shape)
{
  return shape.size() == COUNT_OF_VERTICES_OF_QUADRANGLE;
}
