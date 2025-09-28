#include <gtest/gtest.h>
#include "task1.h"

TEST(Task1, AddTest) {
    ASSERT_EQ(add(2, 2), 4);
    ASSERT_EQ(add(-1, 1), 0);
}