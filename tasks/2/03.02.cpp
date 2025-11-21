#include <cassert>
#include <cmath>
#include <numbers>

class Triangle
{
    double a, b, c;

public:
    Triangle(double side_a, double side_b, double side_c)
        : a(side_a), b(side_b), c(side_c)
    {
    }

    [[nodiscard]] double perimeter() const
    {
        return a + b + c;
    }

    [[nodiscard]] double area() const
    {
        double s = perimeter() / 2.0;
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

class Square
{
    double side;

public:
    explicit Square(double s)
        : side(s)
    {
    }

    [[nodiscard]] double perimeter() const
    {
        return 4.0 * side;
    }

    [[nodiscard]] double area() const
    {
        return side * side;
    }
};

class Circle
{
    double radius;

public:
    explicit Circle(double r)
        : radius(r)
    {
    }

    [[nodiscard]] double perimeter() const
    {
        return 2.0 * std::numbers::pi * radius;
    }

    [[nodiscard]] double area() const
    {
        return std::numbers::pi * radius * radius;
    }
};

int main()
{
    const double epsilon = 1e-5;

    Triangle t(3.0, 4.0, 5.0);
    assert(std::abs(t.perimeter() - 12.0) < epsilon);
    assert(std::abs(t.area() - 6.0) < epsilon);

    Square s(5.0);
    assert(std::abs(s.perimeter() - 20.0) < epsilon);
    assert(std::abs(s.area() - 25.0) < epsilon);

    Circle c(1.0);
    assert(std::abs(c.perimeter() - (2.0 * std::numbers::pi)) < epsilon);
    assert(std::abs(c.area() - std::numbers::pi) < epsilon);
}