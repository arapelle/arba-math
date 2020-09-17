#include <math/vec2.hpp>
#include <gtest/gtest.h>
#include <cstdlib>

namespace ut
{
template <typename number>
void vec2_constructor_empty()
{
    math::vec2<number> vec;
    ASSERT_EQ(vec.x(), 0);
    ASSERT_EQ(vec.y(), 0);
    ASSERT_EQ(&vec.x(), &vec.x());
    ASSERT_EQ(&vec.y(), &vec.y());
}

template <typename number>
void vec2_constructor(const number& x, const number& y)
{
    math::vec2<number> vec(x, y);
    ASSERT_EQ(vec.x(), x);
    ASSERT_EQ(vec.y(), y);
}

template <typename number, typename other_number>
requires std::is_same_v<number, other_number>
void vec2_constructor_copy(const math::vec2<other_number>& v)
{
    math::vec2<number> vec(v);
    ASSERT_EQ(vec.x(), v.x());
    ASSERT_EQ(vec.y(), v.y());
}

template <typename number, typename other_number>
requires (!std::is_same_v<number, other_number>)
void vec2_constructor_other(const other_number& x, const other_number& y)
{
    math::vec2<number> vec(x, y);
    ASSERT_EQ(vec.x(), number(x));
    ASSERT_EQ(vec.y(), number(y));
}

template <typename number, typename other_number>
requires (!std::is_same_v<number, other_number>)
void vec2_constructor_copy_other(const math::vec2<other_number>& v)
{
    math::vec2<number> vec(v);
    ASSERT_EQ(vec.x(), number(v.x()));
    ASSERT_EQ(vec.y(), number(v.y()));
}

template <typename number, typename other_number>
requires std::is_same_v<number, other_number>
void vec2_assignment(const math::vec2<other_number>& v)
{
    math::vec2<number> vec;
    ASSERT_NE(vec.x(), v.x());
    ASSERT_NE(vec.y(), v.y());
    vec = v;
    ASSERT_EQ(vec.x(), v.x());
    ASSERT_EQ(vec.y(), v.y());
}

template <typename number, typename other_number>
requires (!std::is_same_v<number, other_number>)
void vec2_assignment_other(const math::vec2<other_number>& v)
{
    math::vec2<number> vec;
    ASSERT_NE(vec.x(), number(v.x()));
    ASSERT_NE(vec.y(), number(v.y()));
    vec = v;
    ASSERT_EQ(vec.x(), number(v.x()));
    ASSERT_EQ(vec.y(), number(v.y()));
}
}

// Unit tests:

TEST(math_tests, vec2_constructor_empty)
{
    ut::vec2_constructor_empty<uint8_t>();
    ut::vec2_constructor_empty<uint16_t>();
    ut::vec2_constructor_empty<uint32_t>();
    ut::vec2_constructor_empty<uint64_t>();
    ut::vec2_constructor_empty<int8_t>();
    ut::vec2_constructor_empty<int16_t>();
    ut::vec2_constructor_empty<int32_t>();
    ut::vec2_constructor_empty<int64_t>();
    ut::vec2_constructor_empty<float>();
    ut::vec2_constructor_empty<double>();
    ut::vec2_constructor_empty<long double>();
}

TEST(math_tests, vec2_constructor_copy)
{
    ut::vec2_constructor_copy<uint8_t>(math::vec2<uint8_t>(32, 42));
    ut::vec2_constructor_copy<uint16_t>(math::vec2<uint16_t>(32, 42));
    ut::vec2_constructor_copy<uint32_t>(math::vec2<uint32_t>(32, 42));
    ut::vec2_constructor_copy<uint64_t>(math::vec2<uint64_t>(32, 42));
    ut::vec2_constructor_copy<int8_t>(math::vec2<int8_t>(32, 42));
    ut::vec2_constructor_copy<int16_t>(math::vec2<int16_t>(32, 42));
    ut::vec2_constructor_copy<int32_t>(math::vec2<int32_t>(32, 42));
    ut::vec2_constructor_copy<int64_t>(math::vec2<int64_t>(32, 42));
    ut::vec2_constructor_copy<float>(math::vec2<float>(12.75, 36.25));
    ut::vec2_constructor_copy<double>(math::vec2<double>(12.75, 36.25));
    ut::vec2_constructor_copy<long double>(math::vec2<long double>(12.75, 36.25));
}

TEST(math_tests, vec2_constructor)
{
    ut::vec2_constructor<uint8_t>(32, 42);
    ut::vec2_constructor<uint16_t>(32, 42);
    ut::vec2_constructor<uint32_t>(32, 42);
    ut::vec2_constructor<uint64_t>(32, 42);
    ut::vec2_constructor<int8_t>(32, 42);
    ut::vec2_constructor<int16_t>(32, 42);
    ut::vec2_constructor<int32_t>(32, 42);
    ut::vec2_constructor<int64_t>(32, 42);
    ut::vec2_constructor<float>(12.75, 36.25);
    ut::vec2_constructor<double>(12.75, 36.25);
    ut::vec2_constructor<long double>(12.75, 36.25);
}

TEST(math_tests, vec2_constructor_other)
{
    ut::vec2_constructor_other<uint8_t>(12.25, 36.75);
    ut::vec2_constructor_other<uint16_t>(12.25, 36.75);
    ut::vec2_constructor_other<uint32_t>(12.25, 36.75);
    ut::vec2_constructor_other<uint64_t>(12.25, 36.75);
    ut::vec2_constructor_other<int8_t>(12.25, 36.75);
    ut::vec2_constructor_other<int16_t>(12.25, 36.75);
    ut::vec2_constructor_other<int32_t>(12.25, 36.75);
    ut::vec2_constructor_other<int64_t>(12.25, 36.75);
    ut::vec2_constructor_other<float>(12, 36);
    ut::vec2_constructor_other<double>(12, 36);
    ut::vec2_constructor_other<long double>(12, 36);
}

TEST(math_tests, vec2_constructor_copy_other)
{
    ut::vec2_constructor_copy_other<uint8_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other<uint16_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other<uint32_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other<uint64_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other<int8_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other<int16_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other<int32_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other<int64_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other<float>(math::vec2<int>(12, 36));
    ut::vec2_constructor_copy_other<double>(math::vec2<int>(12, 36));
    ut::vec2_constructor_copy_other<long double>(math::vec2<int>(12, 36));
}

TEST(math_tests, vec2_assignment)
{
    ut::vec2_assignment<uint8_t>(math::vec2<uint8_t>(32, 42));
    ut::vec2_assignment<uint16_t>(math::vec2<uint16_t>(32, 42));
    ut::vec2_assignment<uint32_t>(math::vec2<uint32_t>(32, 42));
    ut::vec2_assignment<uint64_t>(math::vec2<uint64_t>(32, 42));
    ut::vec2_assignment<int8_t>(math::vec2<int8_t>(32, 42));
    ut::vec2_assignment<int16_t>(math::vec2<int16_t>(32, 42));
    ut::vec2_assignment<int32_t>(math::vec2<int32_t>(32, 42));
    ut::vec2_assignment<int64_t>(math::vec2<int64_t>(32, 42));
    ut::vec2_assignment<float>(math::vec2<float>(12.75, 36.25));
    ut::vec2_assignment<double>(math::vec2<double>(12.75, 36.25));
    ut::vec2_assignment<long double>(math::vec2<long double>(12.75, 36.25));
}

TEST(math_tests, vec2_assignment_other)
{
    ut::vec2_assignment_other<uint8_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_assignment_other<uint16_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_assignment_other<uint32_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_assignment_other<uint64_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_assignment_other<int8_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_assignment_other<int16_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_assignment_other<int32_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_assignment_other<int64_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_assignment_other<float>(math::vec2<int>(12, 36));
    ut::vec2_assignment_other<double>(math::vec2<int>(12, 36));
    ut::vec2_assignment_other<long double>(math::vec2<int>(12, 36));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
