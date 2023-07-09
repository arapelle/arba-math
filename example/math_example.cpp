#include <iostream>
#include <arba/math/vec2.hpp>
#include <arba/math/version.hpp>

int main()
{
    math::vec2<int> vec(32, 42);
    vec *= 2;
    std::cout << vec << std::endl;
    return EXIT_SUCCESS;
}
