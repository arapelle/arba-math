#pragma once

#include "concepts.hpp"
#include <ostream>
#include <string>
#include <type_traits>
#include <cstdint>

namespace math
{
template <concepts::comparable_arithmetic num>
class vec2
{
public:
    using number_type = num;

    // constructors:
    inline constexpr vec2() : x_(0), y_(0) {}
    inline constexpr vec2(const vec2& vec) = default;
    inline constexpr vec2(vec2&& vec) = default;
    inline constexpr vec2(const number_type& x, const number_type& y) : x_(x), y_(y) {}

    template <concepts::comparable_arithmetic xnum, concepts::comparable_arithmetic ynum>
    requires std::is_convertible_v<xnum, number_type> && std::is_convertible_v<ynum, number_type>
    inline constexpr vec2(const xnum& x, const ynum& y) : x_(static_cast<number_type>(x)), y_(static_cast<number_type>(y)) {}

    template <concepts::comparable_arithmetic other_num>
    requires (!std::is_same_v<other_num, number_type>)
    inline constexpr explicit vec2(const vec2<other_num>& vec) : vec2(vec.x(), vec.y()) {}

    // assignment operator:
    inline vec2& operator=(const vec2& vec) = default;
    inline vec2& operator=(vec2&& vec) = default;

    template <concepts::comparable_arithmetic other_num>
    requires (!std::is_same_v<other_num, number_type>)
    inline vec2& operator=(const vec2<other_num>& vec)
    {
        x_ = static_cast<number_type>(vec.x());
        y_ = static_cast<number_type>(vec.y());
        return *this;
    }

    template <concepts::comparable_arithmetic other_num>
    requires (!std::is_same_v<other_num, number_type>)
    inline vec2& operator=(vec2<other_num>&& vec)
    {
        x_ = number_type(std::move(vec.x()));
        y_ = number_type(std::move(vec.y()));
        return *this;
    }

    // accessors:
    inline constexpr const number_type& x() const { return x_; }
    inline number_type& x() { return x_; }
    inline constexpr const number_type& y() const { return y_; }
    inline number_type& y() { return y_; }

    // comparison:
    inline constexpr bool operator==(const vec2& rfs) const = default;
    inline constexpr bool operator!=(const vec2& rfs) const = default;

    template <concepts::comparable_arithmetic other_num>
    requires (!std::is_same_v<other_num, number_type>)
    inline constexpr bool operator==(const vec2<other_num>& rfs) const
    {
        return x_ == rfs.x() && y_ == rfs.y();
    }

    template <concepts::comparable_arithmetic other_num>
    requires (!std::is_same_v<other_num, number_type>)
    inline constexpr bool operator!=(const vec2<other_num>& rfs) const
    {
        return x_ != rfs.x() || y_ != rfs.y();
    }

    // negative:
    inline constexpr vec2 operator-() const { return vec2(-x_, -y_); }

    // plus:
    inline vec2& operator+=(const vec2& vec)
    {
        x_ += vec.x();
        y_ += vec.y();
        return *this;
    }

    template <concepts::comparable_arithmetic other_num>
    inline vec2& operator+=(const vec2<other_num>& vec)
    {
        x_ += static_cast<number_type>(vec.x());
        y_ += static_cast<number_type>(vec.y());
        return *this;
    }

    // minus:
    inline vec2& operator-=(const vec2& vec)
    {
        x_ -= vec.x();
        y_ -= vec.y();
        return *this;
    }

    template <concepts::comparable_arithmetic other_num>
    inline vec2& operator-=(const vec2<other_num>& vec)
    {
        x_ -= vec.x();
        y_ -= vec.y();
        return *this;
    }

    // multiplies:
    inline vec2& operator*=(const number_type& value)
    {
        x_ *= value;
        y_ *= value;
        return *this;
    }

    template <concepts::comparable_arithmetic other_num>
    inline vec2& operator*=(const other_num& value)
    {
        x_ *= value;
        y_ *= value;
        return *this;
    }

    // divides:
    inline vec2& operator/=(const number_type& value)
    {
        x_ /= value;
        y_ /= value;
        return *this;
    }

    template <concepts::comparable_arithmetic other_num>
    inline vec2& operator/=(const other_num& value)
    {
        x_ /= value;
        y_ /= value;
        return *this;
    }

    // modulo:
    template <concepts::comparable_arithmetic other_num>
    requires concepts::is_modable<number_type, other_num>
    inline vec2& operator%=(const other_num& value)
    {
        x_ %= value;
        y_ %= value;
        return *this;
    }

private:
    number_type x_;
    number_type y_;
};

template <concepts::comparable_arithmetic left_number, concepts::comparable_arithmetic right_number>
requires concepts::are_operable<left_number, right_number>
inline constexpr auto operator+(const vec2<left_number>& lhs, const vec2<right_number>& rhs)
{
    return vec2(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}

template <concepts::comparable_arithmetic left_number, concepts::comparable_arithmetic right_number>
requires concepts::are_operable<left_number, right_number>
inline constexpr auto operator-(const vec2<left_number>& lhs, const vec2<right_number>& rhs)
{
    return vec2(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}

template <concepts::comparable_arithmetic left_number, concepts::comparable_arithmetic right_number>
requires concepts::are_operable<left_number, right_number>
inline constexpr auto operator*(const vec2<left_number>& lhs, const right_number& rhs)
{
    return vec2(lhs.x() * rhs, lhs.y() * rhs);
}

template <concepts::comparable_arithmetic left_number, concepts::comparable_arithmetic right_number>
requires concepts::are_operable<left_number, right_number>
inline constexpr auto operator/(const vec2<left_number>& lhs, const right_number& rhs)
{
    return vec2(lhs.x() / rhs, lhs.y() / rhs);
}

template <concepts::comparable_arithmetic left_number, concepts::comparable_arithmetic right_number>
requires concepts::is_modable<left_number, right_number>
inline constexpr auto operator%(const vec2<left_number>& lhs, const right_number& rhs)
{
    return vec2(lhs.x() % rhs, lhs.y() % rhs);
}

// text serialization:
template <concepts::comparable_arithmetic num>
inline std::ostream& operator<<(std::ostream& stream, const vec2<num>& vec)
{
    return stream << vec.x() << " " << vec.y();
}

template <>
inline std::ostream& operator<< <uint8_t>(std::ostream& stream, const vec2<uint8_t>& vec)
{
    return stream << static_cast<uint16_t>(vec.x()) << " " << static_cast<uint16_t>(vec.y());
}

template <>
inline std::ostream& operator<< <int8_t>(std::ostream& stream, const vec2<int8_t>& vec)
{
    return stream << static_cast<int16_t>(vec.x()) << " " << static_cast<int16_t>(vec.y());
}
}
