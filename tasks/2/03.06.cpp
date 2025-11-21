#include <cassert>
#include <cmath>
#include <memory>
#include <numbers>
#include <vector>

class Shape
{
public:
    virtual ~Shape() = default;

    [[nodiscard]] virtual double perimeter() const = 0;
    [[nodiscard]] virtual double area() const = 0;
};

class Triangle : public Shape
{
    double a, b, c;

public:
    Triangle(double side_a, double side_b, double side_c)
        : a(side_a), b(side_b), c(side_c)
    {
    }

    [[nodiscard]] double perimeter() const override final
    {
        return a + b + c;
    }

    [[nodiscard]] double area() const override final
    {
        double s = perimeter() / 2.0;
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

class Square final : public Shape
{
    double side;

public:
    explicit Square(double s)
        : side(s)
    {
    }

    [[nodiscard]] double perimeter() const override
    {
        return 4.0 * side;
    }

    [[nodiscard]] double area() const override
    {
        return side * side;
    }
};

class Circle final : public Shape
{
    double radius;

public:
    explicit Circle(double r)
        : radius(r)
    {
    }

    [[nodiscard]] double perimeter() const override
    {
        return 2.0 * std::numbers::pi * radius;
    }

    [[nodiscard]] double area() const override
    {
        return std::numbers::pi * radius * radius;
    }
};

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Triangle>(3.0, 4.0, 5.0));
    shapes.push_back(std::make_unique<Square>(5.0));
    shapes.push_back(std::make_unique<Circle>(1.0));

    const double epsilon = 1e-5;

    assert(std::abs(shapes[0]->perimeter() - 12.0) < epsilon);
    assert(std::abs(shapes[0]->area() - 6.0) < epsilon);

    assert(std::abs(shapes[1]->perimeter() - 20.0) < epsilon);
    assert(std::abs(shapes[1]->area() - 25.0) < epsilon);

    assert(std::abs(shapes[2]->perimeter() - (2.0 * std::numbers::pi)) < epsilon);
    assert(std::abs(shapes[2]->area() - std::numbers::pi) < epsilon);
}