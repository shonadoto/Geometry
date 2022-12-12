#include "Ellipse.h"

class Circle : public Ellipse {
    public:
    Circle(const Point&, double);
    Circle(const Point&, const Point&, const Point&);
    double radius() const;
};