#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"

namespace kurenkov {
  class CompositeShape: public Shape {
  public:
    CompositeShape() noexcept;
    CompositeShape(const CompositeShape &other);
    CompositeShape(CompositeShape &&other) noexcept;
    ~CompositeShape() override = default;

    CompositeShape &operator=(const CompositeShape &other);
    CompositeShape &operator=(CompositeShape &&other) noexcept;
    std::shared_ptr<Shape> operator[](unsigned int index) const;

    double getArea() const noexcept override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &newCenter) override;
    void move(double xShift, double yShift) noexcept override;
    void printInfo(std::ostream &out) const override;
    void printDetailedInfo(std::ostream &out) const;
    void scale(double coefficient) override;
    void pushItem(unsigned int index, const std::shared_ptr<Shape> &shape);
    void pushBack(const std::shared_ptr<Shape> &shape);
    void deleteItem(unsigned int index);
    void deleteBack();
    point_t getCenter() const override;
    unsigned int getCount() const noexcept;

  private:
    unsigned int count_;
    std::unique_ptr<std::shared_ptr<Shape>[]> shapesArray_;
  };
}
#endif //COMPOSITE_SHAPE_HPP
