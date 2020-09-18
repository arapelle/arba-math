# Concept

A tiny C++ library providing useful math tools.

- vec2

See [task board](https://app.gitkraken.com/glo/board/X2MtoiQxbQAR8DlZ) for future updates and features.

# Install

## Requirements

Binaries:

- A C++20 compiler (ex: g++-10)
- CMake 3.16 or later

Libraries:

- [core](https://github.com/arapelle/core) 0.4.0
- [Google Test](https://github.com/google/googletest) 1.10 or later (only for testing)

## Clone

```
git clone https://github.com/arapelle/math --recurse-submodules
```

## Quick Install

There is a cmake script at the root of the project which builds the library in *Release* mode and install it (default options are used).

```
cd /path/to/math
cmake -P cmake_quick_install.cmake
```

Use the following to quickly install a different mode.

```
cmake -DCMAKE_BUILD_TYPE=Debug -P cmake_quick_install.cmake
```

## Uninstall

There is a uninstall cmake script created during installation. You can use it to uninstall properly this library.

```
cd /path/to/installed-math/
cmake -P cmake_uninstall.cmake
```

# How to use

## Example - Create *math* settings

```c++
#include <iostream>
#include <math/vec2.hpp>

int main()
{
    math::vec2<int> vec(32, 42);
    vec *= 2;
    std::cout << vec << std::endl;
    return EXIT_SUCCESS;
}
```

## Example - Using *math* in a CMake project

See the [basic cmake project](https://github.com/arapelle/math/tree/master/example/basic_cmake_project) example, and more specifically the [CMakeLists.txt](https://github.com/arapelle/math/tree/master/example/basic_cmake_project/CMakeLists.txt) to see how to use *math* in your CMake projects.

# License

[MIT License](https://github.com/arapelle/math/blob/master/LICENSE.md) © math
