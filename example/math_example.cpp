#include <iostream>
#include <math/vec2.hpp>

int main()
{
    math::vec2<int> vec(32, 42);
    std::cout << vec.x() << " " << vec.y() << std::endl;
    return EXIT_SUCCESS;
}
