//
// Created by meng on 16-11-5.
//

#include "DFA.h"

namespace meng {
    void DFA::init_s0() {
        memset(isend, 0, sizeof(isend));
        memset(graph, 0, sizeof(graph));
        for(auto ch: nfa.re) {
            if(ch == '|' || ch == '.' || ch == '*' || ch == '?' || ch == '+' || ch == '^') continue;
            chset.insert(ch);
        }

        s0.clear();
        closure(nfa.start);
        has.push_back(s0);
    }

    bool DFA::isequal(const std::set<StatePtr>& s1, const std::set<StatePtr>& s2) {
        if(s1.size() != s2.size()) return false;
        for(auto ptr: s1) {
            if(s2.count(ptr) <= 0) {
                return false;
            }
        }
        return true;
    }

    bool DFA::cheak_if_s0_in_has(std::set<StatePtr>& s) {
        for(auto stset: has) {
            if(DFA::isequal(stset, s)) return true;
        }
        return false;
    }

    int DFA::get_id(std::set<StatePtr>& s) {
        int index = 0;
        for(auto stset: has) {
            if(isequal(stset, s)) return index;
            index ++;
        }
        return -1;
    }

    void DFA::closure(StatePtr root) {
        if(s0.count(root) > 0) return;
        s0.insert(root);
        if(root->getOut1() != nullptr && root->getC1() == '^') {
            closure(root->getOut1());
        }
        if(root->getOut2() != nullptr && root->getC2() == '^') {
            closure(root->getOut2());
        }
    }

    void DFA::closure(StatePtr root, std::set<StatePtr>& st) {
        if(st.count(root) > 0) return;
        st.insert(root);
        if(root->getOut1() != nullptr && root->getC1() == '^') {
            closure(root->getOut1(), st);
        }
        if(root->getOut2() != nullptr && root->getC2() == '^') {
            closure(root->getOut2(), st);
        }
    }

    void DFA::move(StatePtr root, std::set<StatePtr>& st, char ch) {
        if(st.count(root)) return;
        if(root->getOut1() != nullptr && root->getC1() == ch) {
            st.insert(root->getOut1());
            move(root->getOut1(), st, ch);
        }

        if(root->getOut2() != nullptr && root->getC2() == ch) {
            st.insert(root->getOut2());
            move(root->getOut2(), st, ch);
        }
    }

    void DFA::getNodeType() {
        auto id = nfa.end;
        int index = 0;
        for(auto ptr: has) {
            if(ptr.count(id)) {
                isend[index] = true;
            }
            index ++;
        }
    }

    void DFA::buildDFA() {
        s0.clear();
        bool flag = true;
        std::set<StatePtr> moveset;
        std::set<StatePtr> newset;
        int sta = 0;
        for(int i=0; i<has.size(); i++) {
            std::set<StatePtr> status = has[i];
            for(auto ch: chset) {
                moveset.clear();
                newset.clear();
                for(auto ptr: status) {
                    move(ptr, moveset, ch);
                }


                for(auto ptr: moveset) {
                    closure(ptr, newset);
                }

                std::cout<<i<<"  "<<ch<<std::endl;
                for(auto ptr: newset) {
                    print_message(ptr->getId());
                }
                puts("-------------------------|||");

                if(newset.size() == 0) continue;

                if(cheak_if_s0_in_has(newset)) {
                    int o = get_id(newset);
                    graph[sta][o] = ch;
                    continue;
                }

                has.push_back(newset);
                graph[sta][has.size() - 1] = ch;
            }
            sta ++;
        }

        getNodeType();
    }

    void DFA::print_graph() {
        for(int i=0; i<has.size(); i++) {
            for(int j=0; j<has.size(); j++) {
                if(graph[i][j] != 0) {
                    printf("graph[%d][%d] = %c  j_type: %d\n", i, j, graph[i][j], isend[j]? 1 : 0);
                }
            }
        }
    }

    bool DFA::Match(std::string &str, int index, int sta) {
        printf("%d  %d  %d\n", str.length(), index, sta);
        if(index == str.length()) {
            if(isend[sta]) {
                puts("****************");
                return true;
            }
            return false;
        }
        for(int i=0; i<50; i++) {
            if(str[index] == graph[sta][i]) {
                if(Match(str, index + 1, i)) {
                    return true;
                }
            }
        }
        return false;
    }
}