#include "composite-shape.hpp"

#include <stdexcept>
#include <ostream>
#include <algorithm>

#include "base-types.hpp"

kurenkov::CompositeShape::CompositeShape() noexcept:
  count_(0),
  shapesArray_(nullptr)
{}

kurenkov::CompositeShape::CompositeShape(const kurenkov::CompositeShape &other):
  count_(other.count_),
  shapesArray_(std::make_unique<std::shared_ptr<Shape>[]>(other.count_))
{
  for (unsigned int i = 0; i < count_; ++i) {
    shapesArray_[i] = other.shapesArray_[i];
  }
}

kurenkov::CompositeShape &kurenkov::CompositeShape::operator=(const kurenkov::CompositeShape &other)
{
  if (this != &other) {
    count_ = other.count_;
    shapesArray_ = std::make_unique<std::shared_ptr<Shape>[]>(other.count_);
    for (unsigned int i = 0; i < count_; ++i) {
      shapesArray_[i] = other.shapesArray_[i];
    }
  }
  return *this;
}

kurenkov::CompositeShape::CompositeShape(kurenkov::CompositeShape &&other) noexcept:
  count_(other.count_),
  shapesArray_(std::move(other.shapesArray_))
{
  other.count_ = 0;
}

kurenkov::CompositeShape &kurenkov::CompositeShape::operator=(kurenkov::CompositeShape &&other) noexcept
{
  count_ = other.count_;
  shapesArray_ = std::move(other.shapesArray_);
  other.count_ = 0;
  return *this;
}

std::shared_ptr<kurenkov::Shape> kurenkov::CompositeShape::operator[](unsigned int index) const
{
  if (index > count_ - 1) {
    throw std::invalid_argument("Invalid index");
  }
  return shapesArray_[index];
}

double kurenkov::CompositeShape::getArea() const noexcept
{
  double tmpArea = 0.0;
  for (unsigned int i = 0; i < count_; ++i) {
    tmpArea += shapesArray_[i]->getArea();
  }
  return tmpArea;
}

kurenkov::rectangle_t kurenkov::CompositeShape::getFrameRect() const
{
  if (count_ == 0) {
    throw std::underflow_error("Composite shape is empty");
  }
  rectangle_t frameRect = shapesArray_[0]->getFrameRect();
  double minX = frameRect.pos.x - frameRect.width / 2;
  double minY = frameRect.pos.y - frameRect.height / 2;
  double maxX = frameRect.pos.x + frameRect.width / 2;
  double maxY = frameRect.pos.y + frameRect.height / 2;
  for (unsigned int i = 1; i < count_; ++i) {
    frameRect = shapesArray_[i]->getFrameRect();
    minX = std::min(minX, frameRect.pos.x - frameRect.width / 2);
    minY = std::min(minY, frameRect.pos.y - frameRect.height / 2);
    maxX = std::max(maxX, frameRect.pos.x + frameRect.width / 2);
    maxY = std::max(maxY, frameRect.pos.y + frameRect.height / 2);
  }
  return {maxX - minX, maxY - minY, {(minX + maxX) / 2, (minY + maxY) / 2}};
}

void kurenkov::CompositeShape::move(const kurenkov::point_t &newCenter)
{
  point_t rectCenter = getFrameRect().pos;
  move(newCenter.x - rectCenter.x, newCenter.y - rectCenter.y);
}

void kurenkov::CompositeShape::move(double xShift, double yShift) noexcept
{
  for (unsigned int i = 0; i < count_; ++i) {
    shapesArray_[i]->move(xShift, yShift);
  }
}

void kurenkov::CompositeShape::printInfo(std::ostream &out) const
{
  out << "Count of elements: " << count_ << '\n';
  out << "Their total area: " << getArea() << '\n';
  rectangle_t frameRect = getFrameRect();
  out << "Frame rectangle's height: " << frameRect.height << '\n';
  out << "Frame rectangle's width: " << frameRect.width << '\n';
  out << "Frame rectangle's center: (" << frameRect.pos.x << "; " << frameRect.pos.y << ")\n";
}

void kurenkov::CompositeShape::printDetailedInfo(std::ostream &out) const
{
  for (unsigned int i = 0; i < getCount(); ++i) {
    out << "Shape with index " << i << ":\n";
    shapesArray_[i]->printInfo(out);
  }
}

void kurenkov::CompositeShape::scale(double coefficient)
{
  if (coefficient <= 0.0) {
    throw std::invalid_argument("Non-positive scale coefficient");
  }
  point_t compositeShapeCenter = getFrameRect().pos;
  for (unsigned int i = 0; i < count_; ++i) {
    shapesArray_[i]->scale(coefficient);
    point_t shapeFrameRect = shapesArray_[i]->getFrameRect().pos;
    double xShift = (shapeFrameRect.x - compositeShapeCenter.x) * (coefficient - 1);
    double yShift = (shapeFrameRect.y - compositeShapeCenter.y) * (coefficient - 1);
    shapesArray_[i]->move(xShift, yShift);
  }
}

void kurenkov::CompositeShape::pushItem(unsigned int index, const std::shared_ptr<Shape> &shape)
{
  if (index > count_) {
    throw std::invalid_argument("Invalid index");
  }
  if (shape == nullptr) {
    throw std::invalid_argument("The added shape is empty");
  }
  if (shape.get() == this) {
    throw std::logic_error("Can't add itself");
  }
  unsigned int tmpCount = count_ + 1;
  std::unique_ptr<std::shared_ptr<Shape>[]> tmpArr = std::make_unique<std::shared_ptr<Shape>[]>(tmpCount);
  for (unsigned int i = 0; i < tmpCount; i++) {
    if (i < index) {
      tmpArr[i] = shapesArray_[i];
    } else if (i == index) {
      tmpArr[i] = shape;
    } else {
      tmpArr[i] = shapesArray_[i - 1];
    }
  }
  count_++;
  shapesArray_ = std::move(tmpArr);
}

void kurenkov::CompositeShape::pushBack(const std::shared_ptr<Shape> &shape)
{
  if (shape == nullptr) {
    throw std::invalid_argument("The added shape is empty");
  }
  pushItem(count_, shape);
}

void kurenkov::CompositeShape::deleteItem(unsigned int index)
{
  if (count_ == 0) {
    throw std::underflow_error("Array is empty");
  }
  if (index > count_ - 1) {
    throw std::invalid_argument("Invalid index");
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> tmpArr = std::make_unique<std::shared_ptr<Shape>[]>(count_ - 1);
  for (unsigned int i = 0; i < index; ++i) {
    tmpArr[i] = shapesArray_[i];
  }
  for (unsigned int i = index; i < count_ - 1; ++i) {
    tmpArr[i] = shapesArray_[i + 1];
  }
  count_--;
  shapesArray_ = std::move(tmpArr);
}

void kurenkov::CompositeShape::deleteBack()
{
  if (count_ == 0) {
    throw std::underflow_error("Array is empty");
  }
  deleteItem(count_ - 1);
}

kurenkov::point_t kurenkov::CompositeShape::getCenter() const
{
  return getFrameRect().pos;
}

unsigned int kurenkov::CompositeShape::getCount() const noexcept
{
  return count_;
}
