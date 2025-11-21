#include <algorithm>
#include <cassert>
#include <vector>

struct Rectangle
{
    int left, top, right, bottom;

    [[nodiscard]] int width() const noexcept
    {
        return std::max(0, right - left);
    }

    [[nodiscard]] int height() const noexcept
    {
        return std::max(0, bottom - top);
    }

    [[nodiscard]] int area() const noexcept
    {
        return width() * height();
    }
};

Rectangle get_bounding_box(const std::vector<Rectangle>& rectangles)
{
    if (rectangles.empty()) return { 0, 0, 0, 0 };

    auto result = rectangles.front();

    for (const auto& rect : rectangles)
    {
        result.left   = std::min(result.left,   rect.left);
        result.top    = std::min(result.top,    rect.top);
        result.right  = std::max(result.right,  rect.right);
        result.bottom = std::max(result.bottom, rect.bottom);
    }

    return result;
}

int get_intersection_area(const std::vector<Rectangle>& rectangles)
{
    if (rectangles.empty()) return 0;

    auto result = rectangles.front();

    for (const auto& rect : rectangles)
    {
        result.left   = std::max(result.left,   rect.left);
        result.top    = std::max(result.top,    rect.top);
        result.right  = std::min(result.right,  rect.right);
        result.bottom = std::min(result.bottom, rect.bottom);

        if (result.width() == 0 || result.height() == 0) return 0;
    }

    return result.area();
}

int main()
{
    std::vector<Rectangle> set1 = {
        { 0, 0, 10, 10 },
        { 5, 5, 15, 15 },
        { 2, 2, 12, 12 }
    };

    assert(get_intersection_area(set1) == 25);

    auto bounds1 = get_bounding_box(set1);
    assert(bounds1.left == 0 && bounds1.top == 0 && bounds1.right == 15 && bounds1.bottom == 15);

    std::vector<Rectangle> set2 = {
        { 0, 0, 10, 10 },
        { 11, 11, 20, 20 }
    };

    assert(get_intersection_area(set2) == 0);

    auto bounds2 = get_bounding_box(set2);
    assert(bounds2.left == 0 && bounds2.top == 0 && bounds2.right == 20 && bounds2.bottom == 20);

    std::vector<Rectangle> set3 = {
        { 0, 0, 10, 10 },
        { 5, 0, 15, 10 }
    };

    assert(get_intersection_area(set3) == 50);

    std::vector<Rectangle> set4 = {};
    assert(get_intersection_area(set4) == 0);
}