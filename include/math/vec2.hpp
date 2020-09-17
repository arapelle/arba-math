#pragma once

#include "concepts.hpp"
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
    inline constexpr vec2(const vec2<other_num>& vec) : vec2(vec.x(), vec.y()) {}

    // assignment operator:
    inline vec2& operator=(const vec2& vec) = default;
    inline vec2& operator=(vec2&& vec) = default;

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
        return x_ == static_cast<number_type>(rfs.x()) && y_ == static_cast<number_type>(rfs.y());
    }

    template <concepts::comparable_arithmetic other_num>
    requires (!std::is_same_v<other_num, number_type>)
    inline constexpr bool operator!=(const vec2<other_num>& rfs) const
    {
        return x_ != static_cast<number_type>(rfs.x()) || y_ != static_cast<number_type>(rfs.y());
    }

private:
    number_type x_;
    number_type y_;
};
}
