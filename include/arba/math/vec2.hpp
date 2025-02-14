#pragma once

#include "concepts.hpp"

#include <arba/hash/murmur_hash.hpp>

#include <array>
#include <cstdint>
#include <format>
#include <ostream>
#include <string>
#include <type_traits>

inline namespace arba
{
namespace math
{

template <ComparableArithmetic NumberType>
class vec2
{
public:
    using number_type = NumberType;

    // constructors:
    inline constexpr vec2() : x_(0), y_(0) {}
    inline constexpr vec2(const vec2& vec) = default;
    inline constexpr vec2(vec2&& vec) = default;
    inline constexpr vec2(const number_type& x, const number_type& y) : x_(x), y_(y) {}

    template <ComparableArithmetic XType, ComparableArithmetic YType>
        requires std::is_convertible_v<XType, number_type> && std::is_convertible_v<YType, number_type>
    inline constexpr vec2(const XType& x, const YType& y)
        : x_(static_cast<number_type>(x)), y_(static_cast<number_type>(y))
    {
    }

    template <ComparableArithmetic OtherNumberType>
        requires(!std::is_same_v<OtherNumberType, number_type>)
    inline constexpr explicit vec2(const vec2<OtherNumberType>& vec) : vec2(vec.x(), vec.y())
    {
    }

    // assignment operator:
    inline vec2& operator=(const vec2& vec) = default;
    inline vec2& operator=(vec2&& vec) = default;

    template <ComparableArithmetic OtherNumberType>
        requires(!std::is_same_v<OtherNumberType, number_type>)
    inline vec2& operator=(const vec2<OtherNumberType>& vec)
    {
        x_ = static_cast<number_type>(vec.x());
        y_ = static_cast<number_type>(vec.y());
        return *this;
    }

    template <ComparableArithmetic OtherNumberType>
        requires(!std::is_same_v<OtherNumberType, number_type>)
    inline vec2& operator=(vec2<OtherNumberType>&& vec)
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

    template <ComparableArithmetic OtherNumberType>
        requires(!std::is_same_v<OtherNumberType, number_type>)
    inline constexpr bool operator==(const vec2<OtherNumberType>& rfs) const
    {
        return x_ == rfs.x() && y_ == rfs.y();
    }

    template <ComparableArithmetic OtherNumberType>
        requires(!std::is_same_v<OtherNumberType, number_type>)
    inline constexpr bool operator!=(const vec2<OtherNumberType>& rfs) const
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

    template <ComparableArithmetic OtherNumberType>
    inline vec2& operator+=(const vec2<OtherNumberType>& vec)
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

    template <ComparableArithmetic OtherNumberType>
    inline vec2& operator-=(const vec2<OtherNumberType>& vec)
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

    template <ComparableArithmetic OtherNumberType>
    inline vec2& operator*=(const OtherNumberType& value)
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

    template <ComparableArithmetic OtherNumberType>
    inline vec2& operator/=(const OtherNumberType& value)
    {
        x_ /= value;
        y_ /= value;
        return *this;
    }

    // modulo:
    template <ComparableArithmetic OtherNumberType>
        requires concepts::is_modable<number_type, OtherNumberType>
    inline vec2& operator%=(const OtherNumberType& value)
    {
        x_ %= value;
        y_ %= value;
        return *this;
    }

private:
    number_type x_;
    number_type y_;
};

template <ComparableArithmetic LeftNumberType, ComparableArithmetic RightNumberType>
    requires concepts::are_operable<LeftNumberType, RightNumberType>
inline constexpr auto operator+(const vec2<LeftNumberType>& lhs, const vec2<RightNumberType>& rhs)
{
    return vec2(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}

template <ComparableArithmetic LeftNumberType, ComparableArithmetic RightNumberType>
    requires concepts::are_operable<LeftNumberType, RightNumberType>
inline constexpr auto operator-(const vec2<LeftNumberType>& lhs, const vec2<RightNumberType>& rhs)
{
    return vec2(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}

template <ComparableArithmetic LeftNumberType, ComparableArithmetic RightNumberType>
    requires concepts::are_operable<LeftNumberType, RightNumberType>
inline constexpr auto operator*(const vec2<LeftNumberType>& lhs, const RightNumberType& rhs)
{
    return vec2(lhs.x() * rhs, lhs.y() * rhs);
}

template <ComparableArithmetic LeftNumberType, ComparableArithmetic RightNumberType>
    requires concepts::are_operable<LeftNumberType, RightNumberType>
inline constexpr auto operator/(const vec2<LeftNumberType>& lhs, const RightNumberType& rhs)
{
    return vec2(lhs.x() / rhs, lhs.y() / rhs);
}

template <ComparableArithmetic LeftNumberType, ComparableArithmetic RightNumberType>
    requires concepts::is_modable<LeftNumberType, RightNumberType>
inline constexpr auto operator%(const vec2<LeftNumberType>& lhs, const RightNumberType& rhs)
{
    return vec2(lhs.x() % rhs, lhs.y() % rhs);
}

// text serialization:
template <ComparableArithmetic NumberType>
inline std::ostream& operator<<(std::ostream& stream, const vec2<NumberType>& vec)
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

// vec2<> aliases:
using vec2u8 = vec2<uint8_t>;
using vec2u16 = vec2<uint16_t>;
using vec2u32 = vec2<uint32_t>;
using vec2u64 = vec2<uint64_t>;
using vec2i8 = vec2<int8_t>;
using vec2i16 = vec2<int16_t>;
using vec2i32 = vec2<int32_t>;
using vec2i64 = vec2<int64_t>;
using vec2f = vec2<float>;
using vec2d = vec2<double>;
using vec2ld = vec2<long double>;

} // namespace math
} // namespace arba

template <::arba::math::ComparableArithmetic NumberType>
    requires std::is_fundamental_v<NumberType>
struct std::hash<::arba::math::vec2<NumberType>>
{
    std::size_t operator()(const ::arba::math::vec2<NumberType>& vec) const
    {
        if constexpr (sizeof(::arba::math::vec2<NumberType>) <= sizeof(std::size_t))
        {
            union vec_to_hash
            {
                ::arba::math::vec2<NumberType> vec;
                std::size_t hash_value;
            } hasher(vec);
            return hasher.hash_value;
        }
        else
        {
            union vec_to_bytes
            {
                ::arba::math::vec2<NumberType> vec;
                std::array<uint8_t, sizeof(::arba::math::vec2<NumberType>)> bytes;
            } vtobytes(vec);
            return ::arba::hash::murmur_hash_64(vtobytes.bytes);
        }
    }
};

template <::arba::math::ComparableArithmetic NumberType, class CharT>
struct std::formatter<::arba::math::vec2<NumberType>, CharT>
{
    template <class FormatParseContext>
    inline constexpr auto parse(FormatParseContext& ctx)
    {
        return ctx.begin();
    }

    template <class FormatContext>
    auto format(const ::arba::math::vec2<NumberType>& vec, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "{} {}", vec.x(), vec.y());
    }
};
