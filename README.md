# Concept

A tiny C++ library providing useful math tools.

- vec2

# Install

## Requirements

Binaries:

- A C++20 compiler (ex: g++-13)
- CMake 3.26 or later

Libraries:

- [arba-core](https://github.com/arapelle/arba-core) 0.4.0 or later

Testing Libraries (optional):

- [Google Test](https://github.com/google/googletest) 1.13 or later (optional)

## Clone

```
git clone https://github.com/arapelle/arba-math --recurse-submodules
```

## Quick Install

There is a cmake script at the root of the project which builds the library in *Release* mode and install it (default options are used).

```
cd /path/to/math
cmake -P cmake/scripts/quick_install.cmake
```

Use the following to quickly install a different mode.

```
cmake -P cmake/scripts/quick_install.cmake -- TESTS BUILD Debug DIR /tmp/local
```

## Uninstall

There is a uninstall cmake script created during installation. You can use it to uninstall properly this library.

```
cd /path/to/installed-arba-math/
cmake -P uninstall.cmake
```

# How to use

## Example - Create *math* settings

```c++
#include <iostream>
#include <arba/math/vec2.hpp>

int main()
{
    math::vec2<int> vec(32, 42);
    vec *= 2;
    std::cout << vec << std::endl;
    return EXIT_SUCCESS;
}
```

## Example - Using *arba-math* in a CMake project

See *basic_cmake_project* example, and more specifically the *CMakeLists.txt* to see how to use *arba-math* in your CMake projects.

# License

[MIT License](./LICENSE.md) © arba-math
