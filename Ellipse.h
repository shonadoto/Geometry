#include "Shape.h"

class Ellipse : public Shape {
 protected:
  Point focus1_, focus2_;
  double big_axis_;

 public:
  Ellipse(const Point&, const Point&, double);
  std::pair<Point, Point> focuses() const;
  std::pair<Line, Line> directrices() const;
  Point center() const;
  double eccentricity() const;
  double halfBigAxis() const;
  double halfSmallAxis() const;

  virtual double perimeter() const override final;
  virtual double area() const override final;
  virtual bool isSameType(const Shape&) const override final;
  virtual bool isEqual(const Shape&) const override final;
  virtual bool isCongruentTo(const Shape&) const override final;
  virtual bool isSimilarTo(const Shape&) const override final;
  virtual bool containsPoint(const Point&) const override final;

  virtual void rotate(const Point&, double angle) override final;
  virtual void reflect(const Point&) override final;
  virtual void reflect(const Line&) override final;
  virtual void scale(const Point&, double koef) override final;
};
