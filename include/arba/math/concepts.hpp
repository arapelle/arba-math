#pragma once

#include <concepts>
#include <type_traits>

inline namespace arba
{
namespace math
{
inline namespace concepts
{
// clang-format off

// concept comparable_arithmetic:
template <typename NumberType>
concept ComparableArithmetic =
        (std::is_fundamental_v<NumberType> && std::is_arithmetic_v<NumberType>)
        || requires(NumberType lhs, const NumberType& rhs)
{
    { lhs + rhs } -> std::convertible_to<NumberType>;
    { lhs - rhs } -> std::convertible_to<NumberType>;
    { lhs * rhs } -> std::convertible_to<NumberType>;
    { lhs / rhs } -> std::convertible_to<NumberType>;
    { -lhs } -> std::same_as<NumberType>;
    { lhs += rhs } -> std::same_as<NumberType&>;
    { lhs -= rhs } -> std::same_as<NumberType&>;
    { lhs *= rhs } -> std::same_as<NumberType&>;
    { lhs /= rhs } -> std::same_as<NumberType&>;
    { lhs == rhs } -> std::convertible_to<bool>;
    { lhs != rhs } -> std::convertible_to<bool>;
    { lhs <  rhs } -> std::convertible_to<bool>;
    { lhs <= rhs } -> std::convertible_to<bool>;
    { lhs >  rhs } -> std::convertible_to<bool>;
    { lhs >= rhs } -> std::convertible_to<bool>;
};

// constant are_operable:
template <typename LeftComparableArithmetic, typename RightComparableArithmetic>
inline constexpr bool are_operable = false;

template <ComparableArithmetic LeftComparableArithmetic, ComparableArithmetic RightComparableArithmetic>
requires requires(LeftComparableArithmetic lhs, const RightComparableArithmetic& rhs)
{
    { lhs + rhs } -> ComparableArithmetic;
    { lhs - rhs } -> ComparableArithmetic;
    { lhs * rhs } -> ComparableArithmetic;
    { lhs / rhs } -> ComparableArithmetic;
    { lhs += rhs } -> std::same_as<LeftComparableArithmetic&>;
    { lhs -= rhs } -> std::same_as<LeftComparableArithmetic&>;
    { lhs *= rhs } -> std::same_as<LeftComparableArithmetic&>;
    { lhs /= rhs } -> std::same_as<LeftComparableArithmetic&>;
    { lhs == rhs } -> std::convertible_to<bool>;
    { lhs != rhs } -> std::convertible_to<bool>;
    { lhs <  rhs } -> std::convertible_to<bool>;
    { lhs <= rhs } -> std::convertible_to<bool>;
    { lhs >  rhs } -> std::convertible_to<bool>;
    { lhs >= rhs } -> std::convertible_to<bool>;
}
inline constexpr bool are_operable<LeftComparableArithmetic, RightComparableArithmetic> = true;

// constant is_modable:
template <typename LeftComparableArithmetic, typename RightComparableArithmetic = LeftComparableArithmetic>
inline constexpr bool is_modable = false;

template <typename LeftComparableArithmetic, typename RightComparableArithmetic>
requires requires(LeftComparableArithmetic lhs, const RightComparableArithmetic& rhs)
{
    { lhs % rhs } -> ComparableArithmetic;
    { lhs %= rhs } -> std::same_as<LeftComparableArithmetic&>;
}
inline constexpr bool is_modable<LeftComparableArithmetic, RightComparableArithmetic> = true;

// clang-format on

} // namespace concepts
} // namespace math
} // namespace arba
