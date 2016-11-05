//
// Created by meng on 16-11-4.
//

#include "test.h"
#include "NFA.h"
#include "Postfix.h"
#include "DFA.h"

namespace meng {
    void testDFA(std::string re) {
        Postfix tmp;
        std::string post = tmp.in2post(re);
        NFA nfa(post);

        nfa.buildNFA();

        DFA dfa(nfa);

        //dfa.closure(dfa.nfa.start);

        dfa.init_s0();
        std::set<StatePtr > s;

        dfa.buildDFA();
        dfa.print_graph();

        std::string str = "abdf";
        if(dfa.Match(str, 0, 0)) {
            puts("-------------");
            print_message("successful");
        }

        nfa.clear_vis();
        nfa.print_NFA(nfa.start);
        nfa.deleteAll();
    }
}

int main() {
    meng::testDFA("(a|b)*dfg");
    return 0;
}