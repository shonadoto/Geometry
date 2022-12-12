#include "Polygon.h"

class Rectangle : public Polygon {
 public:
  Rectangle(const Point&, const Point&, double relation);
  Point center() const;
  std::pair<Line, Line> diagonals() const;
};