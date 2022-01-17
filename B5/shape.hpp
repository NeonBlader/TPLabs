#ifndef B5_SHAPE_HPP
#define B5_SHAPE_HPP

#include <vector>
#include <iosfwd>

const std::size_t COUNT_OF_VERTICES_OF_TRIANGLE = 3;
const std::size_t COUNT_OF_VERTICES_OF_QUADRANGLE = 4;
const std::size_t COUNT_OF_VERTICES_OF_PENTAGON = 5;

struct Point {
  int x;
  int y;
};

using Shape = std::vector<Point>;

std::istream &operator>>(std::istream &in, Shape &shape);
std::ostream &operator<<(std::ostream &out, const Shape &shape);
std::istream &operator>>(std::istream &in, Point &point);
std::ostream &operator<<(std::ostream &out, const Point &point);
bool operator<(const Shape &left, const Shape &right);

std::size_t getDistanceSquare(const Point &firstPoint, const Point &secondPoint);
bool isSquare(const Shape &shape);
bool isRectangle(const Shape &shape);
bool isPentagon(const Shape &shape);
bool isQuadrangle(const Shape &shape);

#endif //B5_SHAPE_HPP
