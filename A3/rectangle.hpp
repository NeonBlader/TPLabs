#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace kurenkov {
  class Rectangle: public Shape {
  public:
    Rectangle(double width, double height, const point_t &pos);

    double getArea() const noexcept override;
    rectangle_t getFrameRect() const override;
    void move(double xShift, double yShift) noexcept override;
    void move(const point_t &newCenter) override;
    void printInfo(std::ostream &out) const override;
    void scale(double coefficient) override;
    point_t getCenter() const override;
    double getWidth() const;
    double getHeight() const;

  private:
    double width_;
    double height_;
    point_t pos_;
  };
}
#endif //RECTANGLE_HPP
