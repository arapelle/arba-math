#include <arba/math/version.hpp>
#include <gtest/gtest.h>

TEST(project_version_tests, test_version_math)
{
    constexpr unsigned major = 0;
    constexpr unsigned minor = 5;
    constexpr unsigned patch = 0;
    static_assert(arba::math::version.core() == arba::vrsn::tri_version(major, minor, patch));
}
