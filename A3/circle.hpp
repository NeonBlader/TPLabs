#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace kurenkov {
  class Circle: public Shape {
  public:
    Circle(double radius, const point_t &center);

    double getArea() const noexcept override;
    rectangle_t getFrameRect() const override;
    void move(double xShift, double yShift) noexcept override;
    void move(const point_t &newCenter) override;
    void printInfo(std::ostream &out) const override;
    void scale(double coefficient) override;
    point_t getCenter() const override;
    double getRadius() const;

  private:
    double radius_;
    point_t pos_;
  };
}

#endif //CIRCLE_HPP
