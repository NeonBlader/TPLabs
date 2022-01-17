#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Circle : public Shape {
public:
  Circle(double radius, const point_t &center);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double xShift, double yShift) override;
  void move(const point_t &newCenter) override;
  void printInfo(std::ostream &out) const override;

private:
  double radius_;
  point_t pos_;
};

#endif //CIRCLE_HPP
