//
// Created by meng on 16-11-4.
//
#include <set>
#include "NFA.h"
namespace meng {
    void NFA::buildNFA() {//asd.f.g.b|*d?d.d.f.g...
        std::stack <TupleStatePtr> s;
        for (auto ch: re) {
            switch (ch) {
                case '*':
                    Closure(s);
                    break;
                case '.':
                    Connect(s);
                    break;
                case '|':
                    Or(s);
                    break;
                case '+':
                    ClosurePlus(s);
                    break;
                case '?':
                    OneOrMore(s);
                    break;
                default:
                    PushState(s, ch);
                    break;
            }
        }
        TupleStatePtr top = s.top();
        start = std::get<0>(top);
        end = std::get<1>(top);
    }

    void NFA::clear_vis() {
        memset(vis, 0, sizeof(vis));
    }

    void NFA::deleteAll() {
        for(auto x: mem) {
            delete x;
        }
        mem.clear();
    }

    void NFA::print_NFA(StatePtr root) {
        if (root == nullptr) return;
        if (vis[root->getId()]) return;
        vis[root->getId()] = 1;

        if (root->getOut1() != nullptr) {
            std::cout << root->getId() << "  " << root->getC1() << "  " << root->getOut1()->getId() << std::endl;
        }

        if (root->getOut2() != nullptr) {
            std::cout << root->getId() << "  " << root->getC2() << "  " << root->getOut2()->getId() << std::endl;
        }
        print_NFA(root->getOut1());
        print_NFA(root->getOut2());
    }


    void NFA::PushState(std::stack<TupleStatePtr>& s, char ch) {
        StatePtr s1 = new State(index++);
        StatePtr s2 = new State(index++);

        mem.push_back(s1); mem.push_back(s2);

        s1->setC1(ch);
        s1->setOut1(s2);
        s.push(std::make_tuple(s1, s2));
    }

    void NFA::Connect(std::stack<TupleStatePtr>& s) {
        if(s.size() < 2) {
            print_message("The regular expression is something error");
            return;
        }

        TupleStatePtr right = s.top(); s.pop();
        TupleStatePtr left = s.top(); s.pop();
        StatePtr lr = std::get<1>(left);
        StatePtr rl = std::get<0>(right);
        lr->setOut1(rl);
        lr->setC1('\\');
        s.push(std::make_tuple(std::get<0>(left), std::get<1>(right)));
    }

    void NFA::Or(std::stack<TupleStatePtr> &s) {
        if(s.size() < 2) {
            print_message("The regular expression is something error");
            return;
        }

        TupleStatePtr right = s.top(); s.pop();
        TupleStatePtr left = s.top(); s.pop();

        StatePtr nl = new State(index++);
        StatePtr nr = new State(index++);

        mem.push_back(nl); mem.push_back(nr);

        StatePtr ll = std::get<0>(left);
        StatePtr lr = std::get<1>(left);

        StatePtr rl = std::get<0>(right);
        StatePtr rr = std::get<1>(right);

        nl->setOut1(ll);
        nl->setC1('\\');

        nl->setOut2(rl);
        nl->setC2('\\');

        lr->setOut1(nr);
        lr->setC1('\\');
        rr->setOut1(nr);
        rr->setC1('\\');

        s.push(std::make_tuple(nl, nr));
    }

    void NFA::Closure(std::stack<TupleStatePtr> &s) {
        if(s.size() < 1) {
            print_message("The regular expression is something error");
            return;
        }

        TupleStatePtr top = s.top(); s.pop();

        StatePtr topl = std::get<0>(top);
        StatePtr topr = std::get<1>(top);

        StatePtr nl = new State(index++);
        StatePtr nr = new State(index++);

        mem.push_back(nl); mem.push_back(nr);

        nl->setOut1(topl);
        nl->setC1('\\');

        topr->setOut2(topl);
        topr->setC2('\\');

        topr->setOut1(nr);
        topr->setC1('\\');

        nl->setOut2(nr);
        nl->setC2('\\');

        s.push(std::make_tuple(nl, nr));
    }

    void NFA::ClosurePlus(std::stack<TupleStatePtr> &s) {
        if(s.size() < 1) {
            print_message("The regular expression is something error");
            return;
        }

        TupleStatePtr top = s.top(); s.pop();

        StatePtr topl = std::get<0>(top);
        StatePtr topr = std::get<1>(top);

        StatePtr nl = new State(index++);
        StatePtr nr = new State(index++);

        mem.push_back(nl); mem.push_back(nr);

        nl->setOut1(topl);
        nl->setC1('\\');

        topr->setOut2(topl);
        topr->setC2('\\');

        topr->setOut1(nr);
        topr->setC1('\\');

        s.push(std::make_tuple(nl, nr));
    }

    void NFA::OneOrMore(std::stack<TupleStatePtr> &s) {
        if(s.size() < 1) {
            print_message("The regular expression is something error");
            return;
        }

        TupleStatePtr top = s.top(); s.pop();

        StatePtr topl = std::get<0>(top);
        StatePtr topr = std::get<1>(top);

        StatePtr nl = new State(index++);
        StatePtr nr = new State(index++);

        mem.push_back(nl); mem.push_back(nr);

        nl->setOut1(topl);
        nl->setC1('\\');

        topr->setOut1(nr);
        topr->setC1('\\');

        nl->setOut2(nr);
        nl->setC2('\\');

        s.push(std::make_tuple(nl, nr));
    }
}