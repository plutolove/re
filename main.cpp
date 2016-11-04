//
// Created by meng on 16-10-26.
//

#include <iostream>
#include "Postfix.h"

void testPostfix(const std::string& re) {
    Postfix tmp;
    std::cout<<tmp.addConcatenations(re)<<std::endl;
}

int main() {
    testPostfix("a(dd|b)*c(0|1|2|3|4|5|6|7|8|9)*");
    return 0;
}