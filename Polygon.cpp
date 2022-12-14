#include "Polygon.h"

Polygon::Polygon(const std::vector<Point>& points) : points_(points) {}

size_t Polygon::verticesCount() const { return points_.size(); }

const std::vector<Point>& Polygon::getVertices() const { return points_; }

std::vector<Point> Polygon::getVectors() const {
  std::vector<Point> vectors = points_;
  size_t size = verticesCount();
  for (size_t i = 0; i < size; ++i) {
    vectors[i] = vectors[(i + 1) % size] - vectors[i];
  }
  return vectors;
}

bool Polygon::isConvex() const {
  std::vector<Point> vectors = getVectors();
  size_t size = verticesCount();
  bool is_positive = doubleLess(0, crossProduct(vectors[0], vectors[1]));
  for (size_t i = 1; i < size; ++i) {
    if (is_positive !=
        doubleLess(0, crossProduct(vectors[i], vectors[(i + 1) % size])))
      return false;
  }
  return true;
}

double Polygon::perimeter() const {
  double cur_perimeter = 0;
  size_t size = verticesCount();
  for (size_t i = 0; i < size; ++i) {
    cur_perimeter += points_[i].dist(points_[(i + 1) % size]);
  }
  return cur_perimeter;
}

double Polygon::area() const {
  double cur_area = 0;
  size_t size = verticesCount();
  for (size_t i = 0; i < size; ++i) {
    cur_area += (points_[i].x * points_[(i + 1) % size].y -
                 points_[(i + 1) % size].x * points_[i].y) /
                2;
  }
  return std::abs(cur_area);
}

bool Polygon::isSameType(const Shape& other) const {
  return dynamic_cast<const Polygon*>(&other) != nullptr;
}

bool Polygon::isEqual(const Shape& other) const {
  if (!isSameType(other)) return false;
  const Polygon& other_p = dynamic_cast<const Polygon&>(other);

  if (verticesCount() != other_p.verticesCount()) return false;
  size_t size = verticesCount();
  for (size_t first = 0; first < size; ++first) {
    bool ok = true, rok = true;
    for (size_t second = 0; second < size; ++second) {
      if (points_[(first + second) % size] != other_p.points_[second])
        ok = false;
      if (points_[(first + second) % size] !=
          other_p.points_[size - 1 - second])
        rok = false;
    }
    if (ok || rok) return true;
  }
  return false;
}

bool Polygon::isCongruentTo(const Shape& other) const {
  return isSimilarTo(other) && doubleEqual(area() / other.area(), 1);
}

bool Polygon::isSimilarTo(const Shape& other) const {
  if (!isSameType(other)) return false;
  const Polygon& other_p = dynamic_cast<const Polygon&>(other);

  if (verticesCount() != other_p.verticesCount()) return false;
  double koef = std::sqrt(area() / other.area());
  std::vector<Point> vec = getVectors(), other_vec = other_p.getVectors();
  size_t size = verticesCount();
  for (size_t i = 0; i < size; ++i) {
    other_vec[i] = other_vec[i] * koef;
  }

  for (size_t first = 0; first < size; ++first) {
    bool ok = true, rok = true;
    for (size_t second = 0; second < size; ++second) {
      if (vec[(first + second) % size].length() != other_vec[second].length())
        ok = false;
      if (vec[(first + second) % size].length() !=
          other_vec[size - 1 - second].length())
        ok = false;
    }
    if (ok || rok) return true;
  }
  return false;
}

bool Polygon::containsPoint(const Point& point) const {
  double angle = 0;
  size_t size = verticesCount();
  for (size_t i = 0; i < size; ++i) {
    angle += std::acos(
        dotProduct(points_[i] - point, points_[(i + 1) % size] - point) /
        (points_[i] - point).length() /
        (points_[(i + 1) % size] - point).length());
  }
  if (doubleEqual(angle, M_PIf64 * 2)) return true;
  return false;
}

void Polygon::rotate(const Point& point, double angle) {
  for (Point& p : points_) p.rotate(point, angle);
}

void Polygon::reflect(const Point& point) {
  for (Point& p : points_) p.reflect(point);
}

void Polygon::reflect(const Line& line) {
  for (Point& p : points_) p.reflect(line);
}

void Polygon::scale(const Point& point, double koef) {
  for (Point& p : points_) p.scale(point, koef);
}
