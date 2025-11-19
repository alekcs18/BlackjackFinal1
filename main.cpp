#include <climits>
#include <cstdint>
#include <iostream>
#include <limits>

#include "homework01.hpp"

#define MAGIC(a, b, op) \
    (std::cout << "(" #a " " #op " " #b ") = " << (a op b) << std::endl)

int main(int, char **)
{
    test();
    return 0;
}
