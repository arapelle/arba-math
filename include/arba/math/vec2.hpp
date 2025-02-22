#pragma once

#include <arba/hash/murmur_hash.hpp>
#include <arba/meta/concept/arithmetic.hpp>

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

template <meta::TotallyOrderedArithmetic Number>
class vec2
{
public:
    using number = Number;

    // constructors:
    inline constexpr vec2() : x_(0), y_(0) {}
    inline constexpr vec2(const vec2& vec) = default;
    inline constexpr vec2(vec2&& vec) = default;
    inline constexpr vec2(number x, number y) : x_(std::move(x)), y_(std::move(y)) {}

    template <typename XType, typename YType>
        requires std::constructible_from<number, const XType&> && std::constructible_from<number, const YType&>
    inline constexpr vec2(const XType& x, const YType& y) : x_(x), y_(y)
    {
    }

    template <typename XType, typename YType>
        requires std::constructible_from<number, XType&&> && std::constructible_from<number, YType&&>
    inline constexpr vec2(XType&& x, YType&& y) : x_(std::forward<XType>(x)), y_(std::forward<YType>(y))
    {
    }

    template <typename OtherType>
        requires(!std::is_same_v<OtherType, number>)
    inline constexpr explicit vec2(const vec2<OtherType>& vec) : vec2(vec.x(), vec.y())
    {
    }

    template <typename OtherType>
        requires(!std::is_same_v<OtherType, number>)
    inline constexpr explicit vec2(vec2<OtherType>&& vec) : vec2(std::move(vec.x()), std::move(vec.y()))
    {
    }

    template <typename VecType>
        requires requires(const VecType& arg) {
            { Number(arg.x) };
            { Number(arg.y) };
        }
    inline constexpr explicit vec2(const VecType& vec) : vec2(vec.x, vec.y)
    {
    }

    template <typename VecType>
        requires requires(VecType&& arg) {
            { Number(std::move(arg.x)) };
            { Number(std::move(arg.y)) };
        }
    inline constexpr explicit vec2(VecType&& vec) : vec2(std::move(vec.x), std::move(vec.y))
    {
    }

    template <typename VecType>
        requires requires(const VecType& arg) {
            { Number(arg[0]) };
            { Number(arg[1]) };
        } && (!requires(const VecType& arg) {
                     { arg.x };
                 })
    inline constexpr explicit vec2(const VecType& vec) : vec2(vec[0], vec[1])
    {
    }

    template <typename VecType>
        requires requires(const VecType& arg) {
            { Number(std::move(arg[0])) };
            { Number(std::move(arg[1])) };
        } && (!requires(const VecType& arg) {
                     { arg.x };
                 })
    inline constexpr explicit vec2(VecType&& vec) : vec2(std::move(vec[0]), std::move(vec[1]))
    {
    }

    // assignment operator:
    inline vec2& operator=(const vec2& vec) = default;
    inline vec2& operator=(vec2&& vec) = default;

    template <typename OtherType>
        requires std::constructible_from<number, const OtherType&>
    inline vec2& operator=(const vec2<OtherType>& vec)
    {
        x_ = number(vec.x());
        y_ = number(vec.y());
        return *this;
    }

    template <typename OtherType>
        requires std::constructible_from<number, OtherType&&>
    inline vec2& operator=(vec2<OtherType>&& vec)
    {
        x_ = number(std::move(vec.x()));
        y_ = number(std::move(vec.y()));
        return *this;
    }

    // accessors:
    inline constexpr const number& x() const { return x_; }
    inline number& x() { return x_; }
    inline constexpr const number& y() const { return y_; }
    inline number& y() { return y_; }

    // comparison:
    inline constexpr bool operator==(const vec2& rfs) const = default;
    inline constexpr bool operator!=(const vec2& rfs) const = default;

    template <typename OtherType>
        requires(!std::is_same_v<OtherType, number>)
    inline constexpr bool operator==(const vec2<OtherType>& rfs) const
    {
        return x_ == rfs.x() && y_ == rfs.y();
    }

    template <typename OtherType>
        requires(!std::is_same_v<OtherType, number>)
    inline constexpr bool operator!=(const vec2<OtherType>& rfs) const
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

    template <typename OtherType>
        requires meta::AdditiveAssignableWith<number, OtherType>
    inline vec2& operator+=(const vec2<OtherType>& vec)
    {
        x_ += static_cast<number>(vec.x());
        y_ += static_cast<number>(vec.y());
        return *this;
    }

    // minus:
    inline vec2& operator-=(const vec2& vec)
    {
        x_ -= vec.x();
        y_ -= vec.y();
        return *this;
    }

    template <typename OtherType>
        requires meta::AdditiveAssignableWith<number, OtherType>
    inline vec2& operator-=(const vec2<OtherType>& vec)
    {
        x_ -= vec.x();
        y_ -= vec.y();
        return *this;
    }

    // multiplies:
    inline vec2& operator*=(const number& value)
    {
        x_ *= value;
        y_ *= value;
        return *this;
    }

    template <typename OtherType>
        requires meta::MultiplicativeAssignableWith<number, OtherType>
    inline vec2& operator*=(const OtherType& value)
    {
        x_ *= value;
        y_ *= value;
        return *this;
    }

    // divides:
    inline vec2& operator/=(const number& value)
    {
        x_ /= value;
        y_ /= value;
        return *this;
    }

    template <typename OtherType>
        requires meta::MultiplicativeAssignableWith<number, OtherType>
    inline vec2& operator/=(const OtherType& value)
    {
        x_ /= value;
        y_ /= value;
        return *this;
    }

    // modulo:
    template <typename OtherType>
        requires meta::ModuloableAssignableWith<number, OtherType>
    inline vec2& operator%=(const OtherType& value)
    {
        x_ %= value;
        y_ %= value;
        return *this;
    }

private:
    number x_;
    number y_;
};

template <typename LeftNumber, typename RightNumber>
    requires meta::AddableWith<LeftNumber, RightNumber>
inline constexpr auto operator+(const vec2<LeftNumber>& lhs, const vec2<RightNumber>& rhs)
{
    return vec2(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}

template <typename LeftNumber, typename RightNumber>
    requires meta::AddableWith<LeftNumber, RightNumber>
inline constexpr auto operator-(const vec2<LeftNumber>& lhs, const vec2<RightNumber>& rhs)
{
    return vec2(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}

template <typename LeftNumber, typename RightNumber>
    requires meta::MultipliableWith<LeftNumber, RightNumber>
inline constexpr auto operator*(const vec2<LeftNumber>& lhs, const RightNumber& rhs)
{
    return vec2(lhs.x() * rhs, lhs.y() * rhs);
}

template <typename LeftNumber, typename RightNumber>
    requires meta::MultipliableWith<LeftNumber, RightNumber>
inline constexpr auto operator/(const vec2<LeftNumber>& lhs, const RightNumber& rhs)
{
    return vec2(lhs.x() / rhs, lhs.y() / rhs);
}

template <typename LeftNumber, typename RightNumber>
    requires meta::ModuloableWith<LeftNumber, RightNumber>
inline constexpr auto operator%(const vec2<LeftNumber>& lhs, const RightNumber& rhs)
{
    return vec2(lhs.x() % rhs, lhs.y() % rhs);
}

// text serialization:
template <meta::TotallyOrderedArithmetic Number>
inline std::ostream& operator<<(std::ostream& stream, const vec2<Number>& vec)
{
    return stream << vec.x() << " " << vec.y();
}

template <>
inline std::ostream& operator<< <uint8_t>(std::ostream& stream, const vec2<uint8_t>& vec)
{
    return stream << static_cast<uint16_t>(vec.x()) << ' ' << static_cast<uint16_t>(vec.y());
}

template <>
inline std::ostream& operator<< <int8_t>(std::ostream& stream, const vec2<int8_t>& vec)
{
    return stream << static_cast<int16_t>(vec.x()) << ' ' << static_cast<int16_t>(vec.y());
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

template <::arba::meta::TotallyOrderedArithmetic Number>
    requires std::is_fundamental_v<Number>
struct std::hash<::arba::math::vec2<Number>>
{
    std::size_t operator()(const ::arba::math::vec2<Number>& vec) const
    {
        if constexpr (sizeof(::arba::math::vec2<Number>) <= sizeof(std::size_t))
        {
            union vec_to_hash
            {
                ::arba::math::vec2<Number> vec;
                std::size_t hash_value;
            } hasher(vec);
            return hasher.hash_value;
        }
        else
        {
            union vec_to_bytes
            {
                ::arba::math::vec2<Number> vec;
                std::array<uint8_t, sizeof(::arba::math::vec2<Number>)> bytes;
            } vtobytes(vec);
            return ::arba::hash::murmur_hash_64(vtobytes.bytes);
        }
    }
};

template <::arba::meta::TotallyOrderedArithmetic Number, class CharT>
struct std::formatter<::arba::math::vec2<Number>, CharT>
{
    template <class FormatParseContext>
    inline constexpr auto parse(FormatParseContext& ctx)
    {
        return ctx.begin();
    }

    template <class FormatContext>
    auto format(const ::arba::math::vec2<Number>& vec, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "{} {}", vec.x(), vec.y());
    }
};
