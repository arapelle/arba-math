#pragma once

#include <concepts>
#include <type_traits>

namespace math::concepts
{
template <typename num>
concept comparable_arithmetic =
        (std::is_fundamental_v<num> && std::is_arithmetic_v<num>)
        || requires(const num& lhs, const num& rhs)
{
    { lhs + rhs } -> std::convertible_to<num>;
    { lhs - rhs } -> std::convertible_to<num>;
    { lhs * rhs } -> std::convertible_to<num>;
    { lhs / rhs } -> std::convertible_to<num>;
    { -lhs } -> std::same_as<num>;
    { lhs += rhs } -> std::same_as<num&>;
    { lhs -= rhs } -> std::same_as<num&>;
    { lhs *= rhs } -> std::same_as<num&>;
    { lhs /= rhs } -> std::same_as<num&>;
    { lhs == rhs } -> std::convertible_to<bool>;
    { lhs != rhs } -> std::convertible_to<bool>;
    { lhs <  rhs } -> std::convertible_to<bool>;
    { lhs <= rhs } -> std::convertible_to<bool>;
    { lhs >  rhs } -> std::convertible_to<bool>;
    { lhs >= rhs } -> std::convertible_to<bool>;
};

template <typename left_comparable_arithmetic, typename right_comparable_arithmetic>
inline constexpr bool are_operable = false;

template <comparable_arithmetic left_comparable_arithmetic, comparable_arithmetic right_comparable_arithmetic>
requires requires(const left_comparable_arithmetic& lhs, const right_comparable_arithmetic& rhs)
{
    { lhs + rhs } -> comparable_arithmetic;
    { lhs - rhs } -> comparable_arithmetic;
    { lhs * rhs } -> comparable_arithmetic;
    { lhs / rhs } -> comparable_arithmetic;
    { lhs += rhs } -> comparable_arithmetic;
    { lhs -= rhs } -> comparable_arithmetic;
    { lhs *= rhs } -> comparable_arithmetic;
    { lhs /= rhs } -> comparable_arithmetic;
    { lhs == rhs } -> std::convertible_to<bool>;
    { lhs != rhs } -> std::convertible_to<bool>;
    { lhs <  rhs } -> std::convertible_to<bool>;
    { lhs <= rhs } -> std::convertible_to<bool>;
    { lhs >  rhs } -> std::convertible_to<bool>;
    { lhs >= rhs } -> std::convertible_to<bool>;
}
inline constexpr bool are_operable<left_comparable_arithmetic, right_comparable_arithmetic> = true;

template <typename left_comparable_arithmetic, typename right_comparable_arithmetic>
inline constexpr bool is_modable = false;

template <typename left_comparable_arithmetic, typename right_comparable_arithmetic>
requires requires(const left_comparable_arithmetic& lhs, const right_comparable_arithmetic& rhs)
{
    { lhs % rhs } -> comparable_arithmetic;
}
inline constexpr bool is_modable<left_comparable_arithmetic, right_comparable_arithmetic> = true;

}
