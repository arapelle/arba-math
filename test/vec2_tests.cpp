#include <arba/math/vec2.hpp>

#include <gtest/gtest.h>

#include <cassert>
#include <cstdlib>

namespace ut
{
template <typename Number>
class vec2_xy
{
public:
    Number x;
    Number y;

    vec2_xy(Number x, Number y) : x(x), y(y) {}

    const Number& operator[](std::size_t idx) const
    {
        assert(idx < 2);
        return idx == 0 ? x : y;
    }
    Number& operator[](std::size_t idx)
    {
        assert(idx < 2);
        return idx == 0 ? x : y;
    }
};

template <typename Number>
class vec2_sb
{
    Number x;
    Number y;

public:
    vec2_sb(Number x, Number y) : x(x), y(y) {}

    const Number& operator[](std::size_t idx) const
    {
        assert(idx < 2);
        return idx == 0 ? x : y;
    }
    Number& operator[](std::size_t idx)
    {
        assert(idx < 2);
        return idx == 0 ? x : y;
    }
};

template <typename Number>
void vec2_constructor_empty()
{
    arba::math::vec2<Number> vec;
    ASSERT_EQ(vec.x(), 0);
    ASSERT_EQ(vec.y(), 0);
    ASSERT_EQ(&vec.x(), &vec.x());
    ASSERT_EQ(&vec.y(), &vec.y());
}

template <typename Number>
void vec2_constructor(const Number& x, const Number& y)
{
    math::vec2<Number> vec(x, y);
    ASSERT_EQ(vec.x(), x);
    ASSERT_EQ(vec.y(), y);
}

template <typename Number, typename OtherNumber>
    requires std::is_same_v<Number, OtherNumber>
void vec2_constructor_copy(const math::vec2<OtherNumber>& v)
{
    math::vec2<Number> vec(v);
    ASSERT_EQ(vec.x(), v.x());
    ASSERT_EQ(vec.y(), v.y());
}

template <typename Number, typename OtherNumber>
    requires(!std::is_same_v<Number, OtherNumber>)
void vec2_constructor_other(const OtherNumber& x, const OtherNumber& y)
{
    math::vec2<Number> vec(x, y);
    ASSERT_EQ(vec.x(), Number(x));
    ASSERT_EQ(vec.y(), Number(y));
}

template <typename Number, typename OtherNumber>
    requires(!std::is_same_v<Number, OtherNumber>)
void vec2_constructor_copy_other(const math::vec2<OtherNumber>& v)
{
    math::vec2<Number> vec(v);
    ASSERT_EQ(vec.x(), Number(v.x()));
    ASSERT_EQ(vec.y(), Number(v.y()));
}

template <typename Number, typename VecType>
void vec2_constructor_copy_other_vec(VecType v)
{
    math::vec2<Number> vec(v);
    ASSERT_EQ(vec.x(), Number(v[0]));
    ASSERT_EQ(vec.y(), Number(v[1]));
}

template <typename Number, typename VecType>
void vec2_constructor_copy_other_rvec(const VecType& v)
{
    math::vec2<Number> vec{ VecType(v) };
    ASSERT_EQ(vec.x(), Number(v[0]));
    ASSERT_EQ(vec.y(), Number(v[1]));
}

template <typename Number, typename OtherNumber>
    requires std::is_same_v<Number, OtherNumber>
void vec2_assignment(const math::vec2<OtherNumber>& v)
{
    math::vec2<Number> vec;
    ASSERT_NE(vec.x(), v.x());
    ASSERT_NE(vec.y(), v.y());
    vec = v;
    ASSERT_EQ(vec.x(), v.x());
    ASSERT_EQ(vec.y(), v.y());
}

template <typename Number, typename OtherNumber>
    requires(!std::is_same_v<Number, OtherNumber>)
void vec2_assignment_other(const math::vec2<OtherNumber>& v)
{
    math::vec2<Number> vec;
    ASSERT_NE(vec.x(), Number(v.x()));
    ASSERT_NE(vec.y(), Number(v.y()));
    vec = v;
    ASSERT_EQ(vec.x(), Number(v.x()));
    ASSERT_EQ(vec.y(), Number(v.y()));
}

template <typename Number, typename OtherNumber>
    requires std::is_same_v<Number, OtherNumber>
void vec2_operator_equal(const math::vec2<OtherNumber>& v)
{
    math::vec2<Number> vec(v);
    ASSERT_EQ(vec, v);
}

template <typename Number, typename OtherNumber>
    requires std::is_same_v<Number, OtherNumber>
void vec2_operator_not_equal(const math::vec2<OtherNumber>& v)
{
    math::vec2<Number> vec;
    ASSERT_NE(vec, v);
}

template <typename Number, typename OtherNumber>
    requires(!std::is_same_v<Number, OtherNumber>)
void vec2_operator_equal_other(const math::vec2<OtherNumber>& v)
{
    math::vec2<Number> vec(v);
    ASSERT_EQ(vec, math::vec2<Number>(v));
    if constexpr (std::is_integral_v<Number>)
    {
        ASSERT_NE(vec, v);
    }
}

template <typename Number, typename OtherNumber>
    requires(!std::is_same_v<Number, OtherNumber>)
void vec2_operator_not_equal_other(const math::vec2<OtherNumber>& v)
{
    math::vec2<Number> vec;
    ASSERT_NE(vec, v);
}

// plus:

template <typename Number>
void vec2_operator_plus_equal(Number x1, Number y1, Number x2, Number y2, Number xr, Number yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<Number> v2(x2, y2);
    math::vec2<Number> vr(xr, yr);
    ASSERT_EQ(v1 += v2, vr);
}

template <typename Number, typename OtherNumber, typename ResNumber>
    requires(!std::is_same_v<Number, OtherNumber>)
void vec2_operator_plus_equal_other(Number x1, Number y1, OtherNumber x2, OtherNumber y2, ResNumber xr, ResNumber yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<OtherNumber> v2(x2, y2);
    math::vec2<ResNumber> vr(xr, yr);
    ASSERT_EQ(v1 += v2, vr);
}

template <typename Number>
void vec2_operator_plus(Number x1, Number y1, Number x2, Number y2, Number xr, Number yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<Number> v2(x2, y2);
    math::vec2<Number> vr(xr, yr);
    ASSERT_EQ(v1 + v2, vr);
}

template <typename Number, typename OtherNumber, typename ResNumber>
    requires(!std::is_same_v<Number, OtherNumber>)
void vec2_operator_plus_other(Number x1, Number y1, OtherNumber x2, OtherNumber y2, ResNumber xr, ResNumber yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<OtherNumber> v2(x2, y2);
    math::vec2<ResNumber> vr(xr, yr);
    ASSERT_EQ(v1 + v2, vr);
}

// minus:

template <typename Number>
void vec2_operator_minus_equal(Number x1, Number y1, Number x2, Number y2, Number xr, Number yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<Number> v2(x2, y2);
    math::vec2<Number> vr(xr, yr);
    ASSERT_EQ(v1 -= v2, vr);
}

template <typename Number, typename OtherNumber, typename ResNumber>
    requires(!std::is_same_v<Number, OtherNumber>)
void vec2_operator_minus_equal_other(Number x1, Number y1, OtherNumber x2, OtherNumber y2, ResNumber xr, ResNumber yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<OtherNumber> v2(x2, y2);
    math::vec2<ResNumber> vr(xr, yr);
    ASSERT_EQ(v1 -= v2, vr);
}

template <typename Number>
void vec2_operator_minus(Number x1, Number y1, Number x2, Number y2, Number xr, Number yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<Number> v2(x2, y2);
    math::vec2<Number> vr(xr, yr);
    ASSERT_EQ(v1 - v2, vr);
}

template <typename Number, typename OtherNumber, typename ResNumber>
    requires(!std::is_same_v<Number, OtherNumber>)
void vec2_operator_minus_other(Number x1, Number y1, OtherNumber x2, OtherNumber y2, ResNumber xr, ResNumber yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<OtherNumber> v2(x2, y2);
    math::vec2<ResNumber> vr(xr, yr);
    ASSERT_EQ(v1 - v2, vr);
}

// multiplies:

template <typename Number>
void vec2_operator_multiplies_equal(Number x1, Number y1, Number value, Number xr, Number yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<Number> vr(xr, yr);
    ASSERT_EQ(v1 *= value, vr);
}

template <typename Number, typename OtherNumber, typename ResNumber>
    requires(!std::is_same_v<Number, OtherNumber>)
void vec2_operator_multiplies_equal_other(Number x1, Number y1, OtherNumber value, ResNumber xr, ResNumber yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<ResNumber> vr(xr, yr);
    ASSERT_EQ(v1 *= value, vr);
}

template <typename Number>
void vec2_operator_multiplies(Number x1, Number y1, Number value, Number xr, Number yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<Number> vr(xr, yr);
    ASSERT_EQ(v1 * value, vr);
}

template <typename Number, typename OtherNumber, typename ResNumber>
    requires(!std::is_same_v<Number, OtherNumber>)
void vec2_operator_multiplies_other(Number x1, Number y1, OtherNumber value, ResNumber xr, ResNumber yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<ResNumber> vr(xr, yr);
    ASSERT_EQ(v1 * value, vr);
}

// divides:

template <typename Number>
void vec2_operator_divides_equal(Number x1, Number y1, Number value, Number xr, Number yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<Number> vr(xr, yr);
    ASSERT_EQ(v1 /= value, vr);
}

template <typename Number, typename OtherNumber, typename ResNumber>
    requires(!std::is_same_v<Number, OtherNumber>)
void vec2_operator_divides_equal_other(Number x1, Number y1, OtherNumber value, ResNumber xr, ResNumber yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<ResNumber> vr(xr, yr);
    ASSERT_EQ(v1 /= value, vr);
}

template <typename Number>
void vec2_operator_divides(Number x1, Number y1, Number value, Number xr, Number yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<Number> vr(xr, yr);
    ASSERT_EQ(v1 / value, vr);
}

template <typename Number, typename OtherNumber, typename ResNumber>
    requires(!std::is_same_v<Number, OtherNumber>)
void vec2_operator_divides_other(Number x1, Number y1, OtherNumber value, ResNumber xr, ResNumber yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<ResNumber> vr(xr, yr);
    ASSERT_EQ(v1 / value, vr);
}

// modulo:
template <typename Number>
void vec2_operator_modulo_equal(Number x1, Number y1, Number value, Number xr, Number yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<Number> vr(xr, yr);
    ASSERT_EQ(v1 %= value, vr);
}

template <typename Number>
void vec2_operator_modulo(Number x1, Number y1, Number value, Number xr, Number yr)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<Number> vr(xr, yr);
    ASSERT_EQ(v1 % value, vr);
}

template <typename Number>
void vec2_operator_negative(Number x1, Number y1)
{
    math::vec2<Number> v1(x1, y1);
    math::vec2<Number> vr(-x1, -y1);
    ASSERT_EQ(-v1, vr);
}

template <typename Number>
void vec2_hash(Number x1, Number y1)
{
    math::vec2<Number> vec(x1, y1);
    std::size_t expected_hash = 0;
    if constexpr (sizeof(math::vec2<Number>) <= sizeof(std::size_t))
    {
        union hasher
        {
            math::vec2<Number> vec;
            std::size_t hash_value;
        } hasher(vec);
        expected_hash = hasher.hash_value;
    }
    else
    {
        union vec_to_bytes
        {
            math::vec2<Number> vec;
            std::array<uint8_t, sizeof(math::vec2<Number>)> bytes;
        } hasher(vec);
        expected_hash = hash::murmur_hash_64(hasher.bytes);
    }
    ASSERT_EQ(std::hash<math::vec2<Number>>{}(vec), expected_hash);
}

template <typename Number>
void vec2_format(Number x1, Number y1)
{
    math::vec2<Number> vec(x1, y1);
    std::string str = std::format("{}", vec);
    ASSERT_EQ(str, std::format("{} {}", vec.x(), vec.y()));
}
} // namespace ut

// Unit tests:

TEST(vec2_tests, vec2_constructor_empty)
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

TEST(vec2_tests, vec2_constructor_copy)
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

TEST(vec2_tests, vec2_constructor)
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

TEST(vec2_tests, vec2_constructor_other)
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

TEST(vec2_tests, vec2_constructor_copy_other)
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

TEST(vec2_tests, vec2_constructor_copy_other_vec_xy)
{
    ut::vec2_constructor_copy_other_vec<uint8_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<uint16_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<uint32_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<uint64_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<int8_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<int16_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<int32_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<int64_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<float>(ut::vec2_xy<int>(12, 36));
    ut::vec2_constructor_copy_other_vec<double>(ut::vec2_xy<int>(12, 36));
    ut::vec2_constructor_copy_other_vec<long double>(ut::vec2_xy<int>(12, 36));
}

TEST(vec2_tests, vec2_constructor_copy_other_vec_sb)
{
    ut::vec2_constructor_copy_other_vec<uint8_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<uint16_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<uint32_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<uint64_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<int8_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<int16_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<int32_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<int64_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_vec<float>(ut::vec2_sb<int>(12, 36));
    ut::vec2_constructor_copy_other_vec<double>(ut::vec2_sb<int>(12, 36));
    ut::vec2_constructor_copy_other_vec<long double>(ut::vec2_sb<int>(12, 36));
}

TEST(vec2_tests, vec2_constructor_copy_other_rvec_xy)
{
    ut::vec2_constructor_copy_other_rvec<uint8_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<uint16_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<uint32_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<uint64_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<int8_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<int16_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<int32_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<int64_t>(ut::vec2_xy<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<float>(ut::vec2_xy<int>(12, 36));
    ut::vec2_constructor_copy_other_rvec<double>(ut::vec2_xy<int>(12, 36));
    ut::vec2_constructor_copy_other_rvec<long double>(ut::vec2_xy<int>(12, 36));
}

TEST(vec2_tests, vec2_constructor_copy_other_rvec_sb)
{
    ut::vec2_constructor_copy_other_rvec<uint8_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<uint16_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<uint32_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<uint64_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<int8_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<int16_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<int32_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<int64_t>(ut::vec2_sb<float>(32.75, 42.25));
    ut::vec2_constructor_copy_other_rvec<float>(ut::vec2_sb<int>(12, 36));
    ut::vec2_constructor_copy_other_rvec<double>(ut::vec2_sb<int>(12, 36));
    ut::vec2_constructor_copy_other_rvec<long double>(ut::vec2_sb<int>(12, 36));
}

TEST(vec2_tests, vec2_assignment)
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

TEST(vec2_tests, vec2_assignment_other)
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

TEST(vec2_tests, vec2_operator_equal)
{
    ut::vec2_operator_equal<uint8_t>(math::vec2<uint8_t>(32, 42));
    ut::vec2_operator_equal<uint16_t>(math::vec2<uint16_t>(32, 42));
    ut::vec2_operator_equal<uint32_t>(math::vec2<uint32_t>(32, 42));
    ut::vec2_operator_equal<uint64_t>(math::vec2<uint64_t>(32, 42));
    ut::vec2_operator_equal<int8_t>(math::vec2<int8_t>(32, 42));
    ut::vec2_operator_equal<int16_t>(math::vec2<int16_t>(32, 42));
    ut::vec2_operator_equal<int32_t>(math::vec2<int32_t>(32, 42));
    ut::vec2_operator_equal<int64_t>(math::vec2<int64_t>(32, 42));
    ut::vec2_operator_equal<float>(math::vec2<float>(12.75, 36.25));
    ut::vec2_operator_equal<double>(math::vec2<double>(12.75, 36.25));
    ut::vec2_operator_equal<long double>(math::vec2<long double>(12.75, 36.25));
}

TEST(vec2_tests, vec2_operator_not_equal)
{
    ut::vec2_operator_not_equal<uint8_t>(math::vec2<uint8_t>(32, 42));
    ut::vec2_operator_not_equal<uint16_t>(math::vec2<uint16_t>(32, 42));
    ut::vec2_operator_not_equal<uint32_t>(math::vec2<uint32_t>(32, 42));
    ut::vec2_operator_not_equal<uint64_t>(math::vec2<uint64_t>(32, 42));
    ut::vec2_operator_not_equal<int8_t>(math::vec2<int8_t>(32, 42));
    ut::vec2_operator_not_equal<int16_t>(math::vec2<int16_t>(32, 42));
    ut::vec2_operator_not_equal<int32_t>(math::vec2<int32_t>(32, 42));
    ut::vec2_operator_not_equal<int64_t>(math::vec2<int64_t>(32, 42));
    ut::vec2_operator_not_equal<float>(math::vec2<float>(12.75, 36.25));
    ut::vec2_operator_not_equal<double>(math::vec2<double>(12.75, 36.25));
    ut::vec2_operator_not_equal<long double>(math::vec2<long double>(12.75, 36.25));
}

TEST(vec2_tests, vec2_operator_equal_other)
{
    ut::vec2_operator_equal_other<uint8_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_equal_other<uint16_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_equal_other<uint32_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_equal_other<uint64_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_equal_other<int8_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_equal_other<int16_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_equal_other<int32_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_equal_other<int64_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_equal_other<float>(math::vec2<int>(12, 36));
    ut::vec2_operator_equal_other<double>(math::vec2<int>(12, 36));
    ut::vec2_operator_equal_other<long double>(math::vec2<int>(12, 36));
}

TEST(vec2_tests, vec2_operator_not_equal_other)
{
    ut::vec2_operator_not_equal_other<uint8_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_not_equal_other<uint16_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_not_equal_other<uint32_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_not_equal_other<uint64_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_not_equal_other<int8_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_not_equal_other<int16_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_not_equal_other<int32_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_not_equal_other<int64_t>(math::vec2<float>(32.75, 42.25));
    ut::vec2_operator_not_equal_other<float>(math::vec2<int>(12, 36));
    ut::vec2_operator_not_equal_other<double>(math::vec2<int>(12, 36));
    ut::vec2_operator_not_equal_other<long double>(math::vec2<int>(12, 36));
}

TEST(vec2_tests, vec2_operator_plus_equal)
{
    ut::vec2_operator_plus_equal<uint8_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus_equal<uint16_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus_equal<uint32_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus_equal<uint64_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus_equal<int8_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus_equal<int16_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus_equal<int32_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus_equal<int64_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus_equal<float>(12.5, 20.25, 14.25, 70.5, 26.75, 90.75);
    ut::vec2_operator_plus_equal<double>(12.5, 20.25, 14.25, 70.5, 26.75, 90.75);
    ut::vec2_operator_plus_equal<long double>(12.5, 20.25, 14.25, 70.5, 26.75, 90.75);
}

TEST(vec2_tests, vec2_operator_plus_equal_other)
{
    ut::vec2_operator_plus_equal_other<uint8_t>(32, 42, 15.25, 83.25, 47, 125);
    ut::vec2_operator_plus_equal_other<uint16_t>(32, 42, 15.25, 83.25, 47, 125);
    ut::vec2_operator_plus_equal_other<uint32_t>(32, 42, 15.25, 83.25, 47, 125);
    ut::vec2_operator_plus_equal_other<uint64_t>(32, 42, 15.25, 83.25, 47, 125);
    ut::vec2_operator_plus_equal_other<int8_t>(32, 42, 15.25, 83.25, 47, 125);
    ut::vec2_operator_plus_equal_other<int16_t>(32, 42, 15.25, 83.25, 47, 125);
    ut::vec2_operator_plus_equal_other<int32_t>(32, 42, 15.25, 83.25, 47, 125);
    ut::vec2_operator_plus_equal_other<int64_t>(32, 42, 15.25, 83.25, 47, 125);
    ut::vec2_operator_plus_equal_other<float>(12.5, 20.25, 14.25, 70.5, 26.75, 90.75);
    ut::vec2_operator_plus_equal_other<double>(12.5, 20.25, 14.25f, 70.5f, 26.75, 90.75);
    ut::vec2_operator_plus_equal_other<long double>(12.5, 20.25, 14.25f, 70.5f, 26.75, 90.75);
}

TEST(vec2_tests, vec2_operator_plus)
{
    ut::vec2_operator_plus<uint8_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus<uint16_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus<uint32_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus<uint64_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus<int8_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus<int16_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus<int32_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus<int64_t>(32, 42, 15, 83, 47, 125);
    ut::vec2_operator_plus<float>(12.5, 20.25, 14.25, 70.5, 26.75, 90.75);
    ut::vec2_operator_plus<double>(12.5, 20.25, 14.25, 70.5, 26.75, 90.75);
    ut::vec2_operator_plus<long double>(12.5, 20.25, 14.25, 70.5, 26.75, 90.75);
}

TEST(vec2_tests, vec2_operator_plus_other)
{
    ut::vec2_operator_plus_other<uint8_t>(32, 42, 15.25, 83.25, 47.25, 125.25);
    ut::vec2_operator_plus_other<uint16_t>(32, 42, 15.25, 83.25, 47.25, 125.25);
    ut::vec2_operator_plus_other<uint32_t>(32, 42, 15.25, 83.25, 47.25, 125.25);
    ut::vec2_operator_plus_other<uint64_t>(32, 42, 15.25, 83.25, 47.25, 125.25);
    ut::vec2_operator_plus_other<int8_t>(32, 42, 15.25, 83.25, 47.25, 125.25);
    ut::vec2_operator_plus_other<int16_t>(32, 42, 15.25, 83.25, 47.25, 125.25);
    ut::vec2_operator_plus_other<int32_t>(32, 42, 15.25, 83.25, 47.25, 125.25);
    ut::vec2_operator_plus_other<int64_t>(32, 42, 15.25, 83.25, 47.25, 125.25);
    ut::vec2_operator_plus_other<float>(12.5, 20.25, 14.25, 70.5, 26.75, 90.75);
    ut::vec2_operator_plus_other<double>(12.5, 20.25, 14.25f, 70.5f, 26.75, 90.75);
    ut::vec2_operator_plus_other<long double>(12.5, 20.25, 14.25f, 70.5f, 26.75, 90.75);
}

TEST(vec2_tests, vec2_operator_minus_equal)
{
    ut::vec2_operator_minus_equal<uint8_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus_equal<uint16_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus_equal<uint32_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus_equal<uint64_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus_equal<int8_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus_equal<int16_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus_equal<int32_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus_equal<int64_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus_equal<float>(26.75, 90.75, 12.5, 20.25, 14.25, 70.5);
    ut::vec2_operator_minus_equal<double>(26.75, 90.75, 12.5, 20.25, 14.25, 70.5);
    ut::vec2_operator_minus_equal<long double>(26.75, 90.75, 12.5, 20.25, 14.25, 70.5);
}

TEST(vec2_tests, vec2_operator_minus_equal_other)
{
    ut::vec2_operator_minus_equal_other<uint8_t>(47, 125, 32.25, 42.75, 14, 82);
    ut::vec2_operator_minus_equal_other<uint16_t>(47, 125, 32.25, 42.75, 14, 82);
    ut::vec2_operator_minus_equal_other<uint32_t>(47, 125, 32.25, 42.75, 14, 82);
    ut::vec2_operator_minus_equal_other<uint64_t>(47, 125, 32.25, 42.75, 14, 82);
    ut::vec2_operator_minus_equal_other<int8_t>(47, 125, 32.25, 42.75, 14, 82);
    ut::vec2_operator_minus_equal_other<int16_t>(47, 125, 32.25, 42.75, 14, 82);
    ut::vec2_operator_minus_equal_other<int32_t>(47, 125, 32.25, 42.75, 14, 82);
    ut::vec2_operator_minus_equal_other<int64_t>(47, 125, 32.25, 42.75, 14, 82);
    ut::vec2_operator_minus_equal_other<float>(26.75, 90.75, 12.5, 20.25, 14.25, 70.5);
    ut::vec2_operator_minus_equal_other<double>(26.75, 90.75, 12.5f, 20.25f, 14.25, 70.5);
    ut::vec2_operator_minus_equal_other<long double>(26.75, 90.75, 12.5f, 20.25f, 14.25, 70.5);
}

TEST(vec2_tests, vec2_operator_minus)
{
    ut::vec2_operator_minus<uint8_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus<uint16_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus<uint32_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus<uint64_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus<int8_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus<int16_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus<int32_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus<int64_t>(47, 125, 32, 42, 15, 83);
    ut::vec2_operator_minus<float>(26.75, 90.75, 12.5, 20.25, 14.25, 70.5);
    ut::vec2_operator_minus<double>(26.75, 90.75, 12.5, 20.25, 14.25, 70.5);
    ut::vec2_operator_minus<long double>(26.75, 90.75, 12.5, 20.25, 14.25, 70.5);
}

TEST(vec2_tests, vec2_operator_minus_other)
{
    ut::vec2_operator_minus_other<uint8_t>(47, 125, 32.25, 42.75, 14.75, 82.25);
    ut::vec2_operator_minus_other<uint16_t>(47, 125, 32.25, 42.75, 14.75, 82.25);
    ut::vec2_operator_minus_other<uint32_t>(47, 125, 32.25, 42.75, 14.75, 82.25);
    ut::vec2_operator_minus_other<uint64_t>(47, 125, 32.25, 42.75, 14.75, 82.25);
    ut::vec2_operator_minus_other<int8_t>(47, 125, 32.25, 42.75, 14.75, 82.25);
    ut::vec2_operator_minus_other<int16_t>(47, 125, 32.25, 42.75, 14.75, 82.25);
    ut::vec2_operator_minus_other<int32_t>(47, 125, 32.25, 42.75, 14.75, 82.25);
    ut::vec2_operator_minus_other<int64_t>(47, 125, 32.25, 42.75, 14.75, 82.25);
    ut::vec2_operator_minus_other<float>(26.75, 90.75, 12.5, 20.25, 14.25, 70.5);
    ut::vec2_operator_minus_other<double>(26.75, 90.75, 12.5f, 20.25f, 14.25, 70.5);
    ut::vec2_operator_minus_other<long double>(26.75, 90.75, 12.5f, 20.25f, 14.25, 70.5);
}

TEST(vec2_tests, vec2_operator_multiplies_equal)
{
    ut::vec2_operator_multiplies_equal<uint8_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies_equal<uint16_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies_equal<uint32_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies_equal<uint64_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies_equal<int8_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies_equal<int16_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies_equal<int32_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies_equal<int64_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies_equal<float>(26.75, 90.75, 2.5, 66.875, 226.875);
    ut::vec2_operator_multiplies_equal<double>(26.75, 90.75, 2.5, 66.875, 226.875);
    ut::vec2_operator_multiplies_equal<long double>(26.75, 90.75, 2.5, 66.875, 226.875);
}

TEST(vec2_tests, vec2_operator_multiplies_equal_other)
{
    ut::vec2_operator_multiplies_equal_other<uint8_t>(30, 2, 2.5, 75, 5);
    ut::vec2_operator_multiplies_equal_other<uint16_t>(30, 2, 2.5, 75, 5);
    ut::vec2_operator_multiplies_equal_other<uint32_t>(30, 2, 2.5, 75, 5);
    ut::vec2_operator_multiplies_equal_other<uint64_t>(30, 2, 2.5, 75, 5);
    ut::vec2_operator_multiplies_equal_other<int8_t>(30, 2, 2.5, 75, 5);
    ut::vec2_operator_multiplies_equal_other<int16_t>(30, 2, 2.5, 75, 5);
    ut::vec2_operator_multiplies_equal_other<int32_t>(30, 2, 2.5, 75, 5);
    ut::vec2_operator_multiplies_equal_other<int64_t>(30, 2, 2.5, 75, 5);
    ut::vec2_operator_multiplies_equal_other<float>(26.75, 90.75, 2.5, 66.875, 226.875);
    ut::vec2_operator_multiplies_equal_other<double>(26.75, 90.75, 2.5f, 66.875, 226.875);
    ut::vec2_operator_multiplies_equal_other<long double>(26.75, 90.75, 2.5f, 66.875, 226.875);
}

TEST(vec2_tests, vec2_operator_multiplies)
{
    ut::vec2_operator_multiplies<uint8_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies<uint16_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies<uint32_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies<uint64_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies<int8_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies<int16_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies<int32_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies<int64_t>(47, 35, 2, 94, 70);
    ut::vec2_operator_multiplies<float>(26.75, 90.75, 2.5, 66.875, 226.875);
    ut::vec2_operator_multiplies<double>(26.75, 90.75, 2.5, 66.875, 226.875);
    ut::vec2_operator_multiplies<long double>(26.75, 90.75, 2.5, 66.875, 226.875);
}

TEST(vec2_tests, vec2_operator_multiplies_other)
{
    ut::vec2_operator_multiplies_other<uint8_t>(7, 3, 2.5, 17.5, 7.5);
    ut::vec2_operator_multiplies_other<uint16_t>(7, 3, 2.5, 17.5, 7.5);
    ut::vec2_operator_multiplies_other<uint32_t>(7, 3, 2.5, 17.5, 7.5);
    ut::vec2_operator_multiplies_other<uint64_t>(7, 3, 2.5, 17.5, 7.5);
    ut::vec2_operator_multiplies_other<int8_t>(7, 3, 2.5, 17.5, 7.5);
    ut::vec2_operator_multiplies_other<int16_t>(7, 3, 2.5, 17.5, 7.5);
    ut::vec2_operator_multiplies_other<int32_t>(7, 3, 2.5, 17.5, 7.5);
    ut::vec2_operator_multiplies_other<int64_t>(7, 3, 2.5, 17.5, 7.5);
    ut::vec2_operator_multiplies_other<float>(26.75, 90.75, 2.5, 66.875, 226.875);
    ut::vec2_operator_multiplies_other<double>(26.75, 90.75, 2.5f, 66.875, 226.875);
    ut::vec2_operator_multiplies_other<long double>(26.75, 90.75, 2.5f, 66.875, 226.875);
}

TEST(vec2_tests, vec2_operator_divides_equal)
{
    ut::vec2_operator_divides_equal<uint8_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides_equal<uint16_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides_equal<uint32_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides_equal<uint64_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides_equal<int8_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides_equal<int16_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides_equal<int32_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides_equal<int64_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides_equal<float>(66.875, 226.875, 2.5, 26.75, 90.75);
    ut::vec2_operator_divides_equal<double>(66.875, 226.875, 2.5, 26.75, 90.75);
    ut::vec2_operator_divides_equal<long double>(66.875, 226.875, 2.5, 26.75, 90.75);
}

TEST(vec2_tests, vec2_operator_divides_equal_other)
{
    ut::vec2_operator_divides_equal_other<uint8_t>(75, 5, 2.5, 30, 2);
    ut::vec2_operator_divides_equal_other<uint16_t>(75, 5, 2.5, 30, 2);
    ut::vec2_operator_divides_equal_other<uint32_t>(75, 5, 2.5, 30, 2);
    ut::vec2_operator_divides_equal_other<uint64_t>(75, 5, 2.5, 30, 2);
    ut::vec2_operator_divides_equal_other<int8_t>(75, 5, 2.5, 30, 2);
    ut::vec2_operator_divides_equal_other<int16_t>(75, 5, 2.5, 30, 2);
    ut::vec2_operator_divides_equal_other<int32_t>(75, 5, 2.5, 30, 2);
    ut::vec2_operator_divides_equal_other<int64_t>(75, 5, 2.5, 30, 2);
    ut::vec2_operator_divides_equal_other<float>(66.875, 226.875, 2.5, 26.75, 90.75);
    ut::vec2_operator_divides_equal_other<double>(66.875, 226.875, 2.5f, 26.75, 90.75);
    ut::vec2_operator_divides_equal_other<long double>(66.875, 226.875, 2.5f, 26.75, 90.75);
}

TEST(vec2_tests, vec2_operator_divides)
{
    ut::vec2_operator_divides<uint8_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides<uint16_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides<uint32_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides<uint64_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides<int8_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides<int16_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides<int32_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides<int64_t>(94, 70, 2, 47, 35);
    ut::vec2_operator_divides<float>(66.875, 226.875, 2.5, 26.75, 90.75);
    ut::vec2_operator_divides<double>(66.875, 226.875, 2.5, 26.75, 90.75);
    ut::vec2_operator_divides<long double>(66.875, 226.875, 2.5, 26.75, 90.75);
}

TEST(vec2_tests, vec2_operator_divides_other)
{
    ut::vec2_operator_divides_other<uint8_t>(17, 5, 2., 8.5, 2.5);
    ut::vec2_operator_divides_other<uint16_t>(17, 5, 2., 8.5, 2.5);
    ut::vec2_operator_divides_other<uint32_t>(17, 5, 2., 8.5, 2.5);
    ut::vec2_operator_divides_other<uint64_t>(17, 5, 2., 8.5, 2.5);
    ut::vec2_operator_divides_other<int8_t>(17, 5, 2., 8.5, 2.5);
    ut::vec2_operator_divides_other<int16_t>(17, 5, 2., 8.5, 2.5);
    ut::vec2_operator_divides_other<int32_t>(17, 5, 2., 8.5, 2.5);
    ut::vec2_operator_divides_other<int64_t>(17, 5, 2., 8.5, 2.5);
    ut::vec2_operator_divides_other<float>(66.875, 226.875, 2.5, 26.75, 90.75);
    ut::vec2_operator_divides_other<double>(66.875, 226.875, 2.5f, 26.75, 90.75);
    ut::vec2_operator_divides_other<long double>(66.875, 226.875, 2.5f, 26.75, 90.75);
}

TEST(vec2_tests, vec2_operator_modulo_equal)
{
    ut::vec2_operator_modulo_equal<uint8_t>(25, 31, 8, 1, 7);
    ut::vec2_operator_modulo_equal<uint16_t>(25, 31, 8, 1, 7);
    ut::vec2_operator_modulo_equal<uint32_t>(25, 31, 8, 1, 7);
    ut::vec2_operator_modulo_equal<uint64_t>(25, 31, 8, 1, 7);
    ut::vec2_operator_modulo_equal<int8_t>(25, 31, 8, 1, 7);
    ut::vec2_operator_modulo_equal<int16_t>(25, 31, 8, 1, 7);
    ut::vec2_operator_modulo_equal<int32_t>(25, 31, 8, 1, 7);
    ut::vec2_operator_modulo_equal<int64_t>(25, 31, 8, 1, 7);
}

TEST(vec2_tests, vec2_operator_modulo)
{
    ut::vec2_operator_modulo<uint8_t>(25, 31, 8, 1, 7);
    ut::vec2_operator_modulo<uint16_t>(25, 31, 8, 1, 7);
    ut::vec2_operator_modulo<uint32_t>(25, 31, 8, 1, 7);
    ut::vec2_operator_modulo<uint64_t>(25, 31, 8, 1, 7);
    ut::vec2_operator_modulo<int8_t>(25, 31, 8, 1, 7);
    ut::vec2_operator_modulo<int16_t>(25, 31, 8, 1, 7);
    ut::vec2_operator_modulo<int32_t>(25, 31, 8, 1, 7);
    ut::vec2_operator_modulo<int64_t>(25, 31, 8, 1, 7);
}

TEST(vec2_tests, vec2_operator_negative)
{
    ut::vec2_operator_negative<int8_t>(25, 31);
    ut::vec2_operator_negative<int16_t>(25, 31);
    ut::vec2_operator_negative<int32_t>(25, 31);
    ut::vec2_operator_negative<int64_t>(25, 31);
    ut::vec2_operator_negative<float>(66.875, 226.25);
    ut::vec2_operator_negative<double>(66.875, 226.25);
    ut::vec2_operator_negative<long double>(66.875, 226.25);
}

TEST(vec2_tests, vec2_hash)
{
    ut::vec2_hash<uint8_t>(25, 31);
    ut::vec2_hash<uint16_t>(25, 31);
    ut::vec2_hash<uint32_t>(25, 31);
    ut::vec2_hash<uint64_t>(25, 31);
    ut::vec2_hash<int8_t>(25, 31);
    ut::vec2_hash<int16_t>(25, 31);
    ut::vec2_hash<int32_t>(25, 31);
    ut::vec2_hash<int64_t>(25, 31);
    ut::vec2_hash<float>(66.875, 226.25);
    ut::vec2_hash<double>(66.875, 226.25);
    ut::vec2_hash<long double>(66.875, 226.25);
    math::vec2<uint8_t> vu8(25, 31);
    math::vec2<uint16_t> vu16(25, 31);
    ASSERT_NE(std::hash<math::vec2<uint8_t>>{}(vu8), std::hash<math::vec2<uint16_t>>{}(vu16));
    math::vec2<uint8_t> vu8bis(25, 31);
    ASSERT_EQ(std::hash<math::vec2<uint8_t>>{}(vu8), std::hash<math::vec2<uint8_t>>{}(vu8bis));
}

TEST(vec2_tests, vec2_format)
{
    ut::vec2_format<uint8_t>(25, 31);
    ut::vec2_format<uint16_t>(25, 31);
    ut::vec2_format<uint32_t>(25, 31);
    ut::vec2_format<uint64_t>(25, 31);
    ut::vec2_format<int8_t>(25, 31);
    ut::vec2_format<int16_t>(25, 31);
    ut::vec2_format<int32_t>(25, 31);
    ut::vec2_format<int64_t>(25, 31);
    ut::vec2_format<float>(66.875, 226.25);
    ut::vec2_format<double>(66.875, 226.25);
    ut::vec2_format<long double>(66.875, 226.25);
}
