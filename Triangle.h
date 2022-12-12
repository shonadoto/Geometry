#include "Square.h"

class Triangle : public Polygon {
 public:
  Triangle(const Point&, const Point&, const Point&);
  Circle circumscribedCircle() const;
  Circle inscribedCircle() const;
  Point centroid() const;
  Point orthocenter() const;
  Line EulerLine() const;
  Circle ninePointsCircle() const;

  bool isEqual(const Shape&) const final;
};

