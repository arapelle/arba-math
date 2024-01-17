#include <arba/math/version.hpp>
#include <cstdlib>
#include <gtest/gtest.h>

TEST(project_version_tests, test_version_macros)
{
    ASSERT_EQ(ARBA_MATH_VERSION_MAJOR, 0);
    ASSERT_EQ(ARBA_MATH_VERSION_MINOR, 5);
    ASSERT_EQ(ARBA_MATH_VERSION_PATCH, 0);
    ASSERT_STREQ(ARBA_MATH_VERSION, "0.5.0");
}
