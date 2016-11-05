//
// Created by meng on 16-11-4.
//

#ifndef RE_DFA_H
#define RE_DFA_H

#include "NFA.h"
#include "State.h"
#include "Postfix.h"
#include <set>
#include <vector>
#include <map>

namespace meng {
    class Node {
    public:
        int id;
        Node(int i) : id(i) { }
    };

    class DFA {
    public:
        char graph[50][50];
        std::set<StatePtr> s0;
        std::set<char> chset;
        NFA nfa;

        bool isend[1000];

        std::vector<std::set<StatePtr>> has;

        DFA(NFA nf) : nfa(nf) {}

        void init_s0();

        bool isequal(const std::set<StatePtr> &s1, const std::set<StatePtr> &s2);

        bool cheak_if_s0_in_has(std::set<StatePtr> &s);

        int get_id(std::set<StatePtr> &s);

        void closure(StatePtr root);

        void closure(StatePtr root, std::set<StatePtr> &st);

        void move(StatePtr root, std::set<StatePtr> &st, char ch);

        void getNodeType();

        void buildDFA();

        void print_graph();
    };
}

#endif //RE_DFA_H
