#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iosfwd>

struct point_t;
struct rectangle_t;

class Shape {
public:
  virtual ~Shape() = default;

  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t &newCenter) = 0;
  virtual void move(double xShift, double yShift) = 0;
  virtual void printInfo(std::ostream &out) const = 0;
};

#endif //SHAPE_HPP
