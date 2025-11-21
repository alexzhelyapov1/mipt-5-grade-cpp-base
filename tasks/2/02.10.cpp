#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

void order(std::vector<int>& vector, std::size_t left, std::size_t right)
{
    for (auto i = left + 1; i < right; ++i)
    {
        for (auto j = i; j > left; --j)
        {
            if (vector[j - 1] > vector[j])
            {
                std::swap(vector[j], vector[j - 1]);
            }
        }
    }
}

std::size_t partition(std::vector<int>& vector, std::size_t left, std::size_t right)
{
    auto mid = std::midpoint(left, right - 1);
    auto last = right - 1;

    if (vector[mid] < vector[left]) std::swap(vector[left], vector[mid]);
    if (vector[last] < vector[left]) std::swap(vector[left], vector[last]);
    if (vector[last] < vector[mid]) std::swap(vector[mid], vector[last]);

    auto pivot = vector[mid];
    auto i = left - 1;
    auto j = right;

    while (true)
    {
        do { ++i; } while (vector[i] < pivot);
        do { --j; } while (vector[j] > pivot);

        if (i >= j) return j;

        std::swap(vector[i], vector[j]);
    }
}

void split(std::vector<int>& vector, std::size_t left, std::size_t right)
{
    if (right - left > 16)
    {
        auto p = partition(vector, left, right);

        split(vector, left, p + 1);
        split(vector, p + 1, right);
    }
    else
    {
        order(vector, left, right);
    }
}

void sort(std::vector<int>& vector)
{
    split(vector, 0, std::size(vector));
}

int main()
{
    auto size = 1'000uz;

    std::vector<int> vector(size, 0);

    for (auto i = 0uz; i < size; ++i)
    {
        vector[i] = size - i;
    }

    sort(vector);

    assert(std::ranges::is_sorted(vector));
}