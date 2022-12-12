#include "Circle.h"

class Polygon : public Shape {
 protected:
  std::vector<Point> points_;

  void add_points(const Point&);
  template <typename... Args>
  void add_points(const Point&, Args...);

 public:
  template <typename... Args>
  Polygon(const Point&, const Point&, const Point&, Args...);

  Polygon(const std::vector<Point>&);

  size_t verticesCount() const;
  std::vector<Point> getVectors() const;
  const std::vector<Point>& getVertices() const;
  bool isConvex() const;

  virtual double perimeter() const override final;
  virtual double area() const override final;
  virtual bool isSameType(const Shape&) const override final;
  virtual bool isEqual(const Shape&) const override;
  virtual bool isCongruentTo(const Shape&) const override final;
  virtual bool isSimilarTo(const Shape&) const override final;
  virtual bool containsPoint(const Point&) const override final;

  virtual void rotate(const Point&, double angle) override final;
  virtual void reflect(const Point&) override final;
  virtual void reflect(const Line&) override final;
  virtual void scale(const Point&, double koef) override final;
};

template <typename... Args>
Polygon::Polygon(const Point& point1, const Point& point2, const Point& point3,
                 Args... tail)
    : points_() {
  add_points(point1), add_points(point2), add_points(point3);
  add_points(tail...);
}

template <typename... Args>
void Polygon::add_points(const Point& point, Args... tail) {
  add_points(point);
  add_points(tail...)
}

void Polygon::add_points(const Point& point) { points_.push_back(point); }
