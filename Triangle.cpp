#include "Triangle.h"

Triangle::Triangle(const Point& point1, const Point& point2,
                   const Point& point3)
    : Polygon(point1, point2, point3) {}

bool Triangle::isEqual(const Shape& other) const {
  if (!isSameType(other)) return false;
  const Polygon& other_p = dynamic_cast<const Polygon&>(other);
  if (other_p.verticesCount() != verticesCount()) return false;
  std::vector<Point> other_points = other_p.getVertices();
  std::vector<Point> inv = other_p.getVertices();
  swap(inv[0], inv[1]);

  std::cerr << "{ ";
  for (auto& p : points_) std::cerr << "{" << p.x << ", " << p.y << "},\n";
  std::cerr << "}\n\n";

  std::cerr << "{ ";
  for (auto& p : other_points) std::cerr << "{" << p.x << ", " << p.y << "},\n";
  std::cerr << "}\n\n";

  size_t size = verticesCount();
  for (size_t first = 0; first < size; ++first) {
    bool ok = true, rok = true, inv_ok = true, inv_rok = true;
    for (size_t second = 0; second < size; ++second) {
      if (points_[(first + second) % size] != other_points[second]) ok = false;
      if (points_[(first + second) % size] != other_points[size - 1 - second])
        rok = false;
      if (points_[(first + second) % size] != inv[second]) inv_ok = false;
      if (points_[(first + second) % size] != inv[size - 1 - second])
        inv_rok = false;
    }
    if (ok || rok || inv_ok || inv_rok) return true;
  }
  return false;
}

Circle Triangle::circumscribedCircle() const {
  return Circle(points_[0], points_[1], points_[2]);
}

Circle Triangle::inscribedCircle() const {
  double a = points_[1].dist(points_[2]);
  double b = points_[0].dist(points_[2]);
  double c = points_[0].dist(points_[1]);
  Point center =
      (points_[0] * a + points_[1] * b + points_[2] * c) / (a + b + c);
  double half_per = perimeter() / 2;
  double radius = std::sqrt((half_per - a) * (half_per - b) * (half_per - c) / half_per);
  return Circle(center, radius);
}

Point Triangle::centroid() const {
  Point center = (points_[1] + points_[2]) / 2;
  return (points_[0] + center * 2) / 3;
}

Point Triangle::orthocenter() const {
  Line side1(points_[0], points_[1]);
  Line norm1(points_[2], points_[2] + side1.normal());
  Line side2(points_[0], points_[2]);
  Line norm2(points_[1], points_[1] + side2.normal());
  return norm1.intersect(norm2);
}

Line Triangle::EulerLine() const {
  return Line(circumscribedCircle().center(), orthocenter());
}

Circle Triangle::ninePointsCircle() const {
  return Circle((points_[0] + points_[1]) / 2, (points_[0] + points_[2]) / 2,
                (points_[1] + points_[2]) / 2);
}