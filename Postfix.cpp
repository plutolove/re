//
// Created by meng on 16-10-26.
//

#include <iostream>
#include "Postfix.h"
namespace meng {
    std::string Postfix::addConcatenations(const std::string &in) {
        std::string res = "";
        res += in[0];
        for (int i = 1; i < in.length(); i++) {
            if (possibleConcatenation(res) && (isCharacter(in[i]) || isOpenParenthesis(in[i]))) {
                res += ".";
            }
            res += in[i];
        }
        return res;
    }

    std::string Postfix::in2post(const std::string &in) {
        std::string res = "";
        std::string input = addConcatenations(in);
        std::stack<char> st;
        for (int i = 0; i < input.length(); i++) {
            char curr = input[i];
            if (isAnOperator(curr)) {
                if (st.empty()) {
                    st.push(curr);
                } else {
                    char top = st.top();
                    if (isAnOperator(top)) {
                        if (precedence(curr, top) <= 0) {
                            st.pop();
                            res += top;
                        }
                    }
                    st.push(curr);
                }
            } else if (isOpenParenthesis(curr)) {
                st.push(curr);
            } else if (isCloseParenthesis(curr)) {
                char topOfStack = st.top();
                st.pop();
                while (!isOpenParenthesis(topOfStack)) {
                    res += topOfStack;
                    topOfStack = st.top();
                    st.pop();
                }
            } else {
                res += curr;
            }
        }
        while (!st.empty()) {
            char ch = st.top();
            st.pop();
            res += ch;
        }
        return res;
    }
}