#include "Line.h"

class Shape {
 public:
  virtual double perimeter() const = 0;
  virtual double area() const = 0;
  virtual bool isSameType(const Shape&) const = 0;
  virtual bool isEqual(const Shape&) const = 0;
  virtual bool isCongruentTo(const Shape&) const = 0;
  virtual bool isSimilarTo(const Shape&) const = 0;
  virtual bool containsPoint(const Point&) const = 0;

  virtual void rotate(const Point&, double angle) = 0;
  virtual void reflect(const Point&) = 0;
  virtual void reflect(const Line&) = 0;
  virtual void scale(const Point&, double koef) = 0;
};

bool operator==(const Shape& lhs, const Shape& rhs) { return lhs.isEqual(rhs); }