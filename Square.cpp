#include "Square.h"

Square::Square(const Point& point1, const Point& point2)
    : Rectangle(point1, point2, 1) {}

Circle Square::circumscribedCircle() const {
  return Circle(center(), center().dist(points_[0]));
}

Circle Square::inscribedCircle() const {
  return Circle(center(), points_[0].dist(points_[1]));
}