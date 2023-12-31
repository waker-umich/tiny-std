#include "functional.hpp"
#include <iostream>
#include <vector>

using namespace mystd;

auto foo2() -> void { std::cout << "foo2\n"; }

struct Foo3 {
    void operator()() { std::cout << "foo1\n"; }
};

auto test_function_ref() -> auto{
    Foo3 foo1;
    // constructed by function object
    function_ref f1(foo1);
    f1();

    // constructed using function pointer
    function_ref f2(foo2);
    f2();

    // constructed by function object generated by lambda
    auto foo3 = [] { std::cout << "foo3\n"; };
    function_ref f3(foo3);
    f3();

    // copy construction
    function_ref f4 = f3;
    f4();

    // copy assignment
    f4 = f1;
    f4();

    // move assignment
    f4 = std::move(f2);
    f2();
}

consteval auto test_reference_wrapper() -> int {
    int i = 3;
    reference_wrapper ri = i;
    std::vector<reference_wrapper<int>> vec{ri};
    return vec[0];
}

static_assert(test_reference_wrapper() == 3);

auto main() -> int { test_function_ref(); }