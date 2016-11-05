//
// Created by meng on 16-10-26.
//

#include <iostream>
#include "Postfix.h"
#include "test.h"
#include "NFA.h"

namespace meng {
    void testPostfix(const std::string& re) {
        Postfix tmp;
        print_message(tmp.addConcatenations(re));
        print_message(tmp.in2post(re));
    }
    void testNFA(const std::string& re) {
        Postfix tmp;
        std::string post = tmp.in2post(re);
        NFA nfa(post);

        nfa.buildNFA();
        nfa.clear_vis();
        nfa.print_NFA(nfa.start);
        nfa.deleteAll();
    }
}
int main() {
    meng::testPostfix("(a|b)cd");
    meng::testNFA("(a|b|c)*c?d+");
    return 0;
}