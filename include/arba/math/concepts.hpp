#pragma once

#include <concepts>
#include <type_traits>

inline namespace arba
{
namespace math::concepts
{

// clang-format off

// concept comparable_arithmetic:
template <typename num>
concept comparable_arithmetic =
        (std::is_fundamental_v<num> && std::is_arithmetic_v<num>)
        || requires(num lhs, const num& rhs)
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

// constant are_operable:
template <typename left_comparable_arithmetic, typename right_comparable_arithmetic>
inline constexpr bool are_operable = false;

template <comparable_arithmetic left_comparable_arithmetic, comparable_arithmetic right_comparable_arithmetic>
requires requires(left_comparable_arithmetic lhs, const right_comparable_arithmetic& rhs)
{
    { lhs + rhs } -> comparable_arithmetic;
    { lhs - rhs } -> comparable_arithmetic;
    { lhs * rhs } -> comparable_arithmetic;
    { lhs / rhs } -> comparable_arithmetic;
    { lhs += rhs } -> std::same_as<left_comparable_arithmetic&>;
    { lhs -= rhs } -> std::same_as<left_comparable_arithmetic&>;
    { lhs *= rhs } -> std::same_as<left_comparable_arithmetic&>;
    { lhs /= rhs } -> std::same_as<left_comparable_arithmetic&>;
    { lhs == rhs } -> std::convertible_to<bool>;
    { lhs != rhs } -> std::convertible_to<bool>;
    { lhs <  rhs } -> std::convertible_to<bool>;
    { lhs <= rhs } -> std::convertible_to<bool>;
    { lhs >  rhs } -> std::convertible_to<bool>;
    { lhs >= rhs } -> std::convertible_to<bool>;
}
inline constexpr bool are_operable<left_comparable_arithmetic, right_comparable_arithmetic> = true;

// constant is_modable:
template <typename left_comparable_arithmetic, typename right_comparable_arithmetic>
inline constexpr bool is_modable = false;

template <typename left_comparable_arithmetic, typename right_comparable_arithmetic>
requires requires(left_comparable_arithmetic lhs, const right_comparable_arithmetic& rhs)
{
    { lhs % rhs } -> comparable_arithmetic;
    { lhs %= rhs } -> std::same_as<left_comparable_arithmetic&>;
}
inline constexpr bool is_modable<left_comparable_arithmetic, right_comparable_arithmetic> = true;

// clang-format on

} // namespace math::concepts
} // namespace arba
