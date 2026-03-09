#include <gtest/gtest.h>
#include "sort.hpp"
#include <vector>
#include <numeric>
#include <algorithm>

TEST(SortTest, HandlesReverseSorted) {
    std::vector<int> v(1000);
    std::iota(v.rbegin(), v.rend(), 0);
    sort(v);
    ASSERT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(SortTest, HandlesAlreadySorted) {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), 0);
    sort(v);
    ASSERT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(SortTest, HandlesRandomData) {
    std::vector<double> v = {3.14, 1.41, 2.71, 0.57, 1.61, 9.81, 6.62};
    sort(v);
    ASSERT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(SortTest, HandlesStrings) {
    std::vector<std::string> v = {"delta", "alpha", "charlie", "bravo", "echo"};
    sort(v);
    ASSERT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(SortTest, HandlesEmptyVector) {
    std::vector<int> v;
    sort(v);
    ASSERT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(SortTest, HandlesSingleElement) {
    std::vector<int> v = {42};
    sort(v);
    ASSERT_TRUE(std::is_sorted(v.begin(), v.end()));
}
