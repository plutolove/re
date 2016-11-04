//
// Created by meng on 16-10-30.
//

#ifndef COMPILER_NFA_H
#define COMPILER_NFA_H

#include "State.h"
#include "test.h"
#include <string>
#include <tuple>
#include <stack>
#include <iostream>
#include <cstring>

namespace meng {
    class NFA {
    public:

        std::vector<StatePtr> mem;
        int vis[1000];
        StatePtr start;
        StatePtr end;
        std::string re;
        int index = 0;
        NFA(const std::string& str) : re(str), start(nullptr), end(nullptr) { }

        void buildNFA();
        void clear_vis();
        void print_NFA(StatePtr root);
        void deleteAll();

        void PushState(std::stack<TupleStatePtr>& s, char ch);
        void Connect(std::stack<TupleStatePtr>& s);
        void Or(std::stack<TupleStatePtr>& s);
        void Closure(std::stack<TupleStatePtr>& s);
        void ClosurePlus(std::stack<TupleStatePtr>& s);
        void OneOrMore(std::stack<TupleStatePtr>& s);
    };
}

#endif //COMPILER_NFA_H
