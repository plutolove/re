//
// Created by meng on 16-10-30.
//

#ifndef COMPILER_STATE_H
#define COMPILER_STATE_H
#include <vector>
#include <map>
#include <tuple>

namespace meng {
    class State {
    private:
        int id;
        State* out1;
        State* out2;
        char c1, c2;

        void operator=(const State&);
        //State(const State&);
    public:
        State(int in) : out1(nullptr), out2(nullptr), id(in) { }

        int getId() { return id; }

        State* getOut1() {
            return out1;
        }
        State* getOut2() {
            return out2;
        }

        void setOut1(State* const o1) {
            this->out1 = o1;
        }
        void setOut2(State* const o2) {
            this->out2 = o2;
        }

        char getC1() { return c1; }
        char getC2() { return c2; }

        void setC1(char o1) { c1 = o1; }
        void setC2(char o2) { c2 = o2; }
    };
    typedef State* StatePtr;
    typedef std::tuple<StatePtr, StatePtr> TupleStatePtr;
}
#endif //COMPILER_STATE_H
