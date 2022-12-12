#include <Rectangle.h>

class Square : public Rectangle {
 public:
  Square(const Point&, const Point&);
  Circle circumscribedCircle() const;
  Circle inscribedCircle() const;
};