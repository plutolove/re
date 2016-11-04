//
// Created by meng on 16-10-26.
//

#ifndef COMPILER_TEST_H
#define COMPILER_TEST_H
#include <cstdio>
#include <iostream>
namespace meng {

    template<typename Type>
    bool isequal(Type x, Type y) {
        return x == y;
    }

    template<typename Type>
    void accept(Type x, Type y) {
        if (isequal(x, y)) {
            puts("PASSED");
        } else {
            puts("FAILED");
        }
    }

    template<typename Type>
    void print_message(Type message) {
        std::cout << message << std::endl;
    }
}
#endif //COMPILER_TEST_H
