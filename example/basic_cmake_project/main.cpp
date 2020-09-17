#include <iostream>
#include <math/vec2.hpp>

int main()
{
    math::vec2<int> vec(32, 42);
    vec *= 2;
    std::cout << vec << std::endl;
    return EXIT_SUCCESS;
}
