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
        std::vector<std::tuple<char, int>> edge;
        Node(int i) : id(i) { }
    };

    class DFA {
    public:
        char graph[1000][1000];
        std::set<StatePtr> s0;
        std::set<char> chset;
        NFA nfa;

        bool isend[1000];

        std::vector<std::set<StatePtr>> has;

        DFA(NFA nf) : nfa(nf) { }

        void init_s0() {
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

        bool isequal(const std::set<StatePtr>& s1, const std::set<StatePtr>& s2) {
            if(s1.size() != s2.size()) return false;
            for(auto ptr: s1) {
                if(s2.count(ptr) <= 0) {
                    return false;
                }
            }
            return true;
        }

        bool cheak_if_s0_in_has(std::set<StatePtr>& s) {
            for(auto stset: has) {
                if(isequal(stset, s)) return true;
            }
            return false;
        }

        int get_id(std::set<StatePtr>& s) {
            int index = 0;
            for(auto stset: has) {
                if(isequal(stset, s)) return index;
                index ++;
            }
            return -1;
        }

        void closure(StatePtr root) {
            if(s0.count(root) > 0) return;
            s0.insert(root);
            if(root->getOut1() != nullptr && root->getC1() == '^') {
                closure(root->getOut1());
            }
            if(root->getOut2() != nullptr && root->getC2() == '^') {
                closure(root->getOut2());
            }
        }

        void closure(StatePtr root, std::set<StatePtr>& st) {
            if(st.count(root) > 0) return;
            st.insert(root);
            if(root->getOut1() != nullptr && root->getC1() == '^') {
                closure(root->getOut1(), st);
            }
            if(root->getOut2() != nullptr && root->getC2() == '^') {
                closure(root->getOut2(), st);
            }
        }

        void move(StatePtr root, std::set<StatePtr>& st, char ch) {
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

        void getNodeType() {
            auto id = nfa.end;
            int index = 0;
            for(auto ptr: has) {
                if(ptr.count(id)) {
                    isend[index] = true;
                }
                index ++;
            }
        }

        void buildDFA() {
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

        void print_graph() {
            for(int i=0; i<has.size(); i++) {
                for(int j=0; j<has.size(); j++) {
                    if(graph[i][j] != 0) {
                        printf("graph[%d][%d] = %c  j_type: %d\n", i, j, graph[i][j], isend[j]? 1 : 0);
                    }
                }
            }
        }
    };
}

#endif //RE_DFA_H
