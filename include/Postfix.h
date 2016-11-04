//
// Created by meng on 16-10-26.
//

#ifndef COMPILER_POSTFIX_H
#define COMPILER_POSTFIX_H
#include <string>
#include <stack>
namespace meng {
    class Postfix {
    public:
        Postfix() {}

        ~Postfix() {}

        std::string addConcatenations(const std::string &in);

        std::string in2post(const std::string &in);

    private:
        //no copy right
        Postfix(const Postfix &);

        void operator=(const Postfix &);

        int precedence(char a, char b) {
            if (isMultiplication(a)) {
                if (isMultiplication(b))
                    return 0;
                else
                    return 1;
            } else if (isConcatenation(a)) {
                if (isMultiplication(b))
                    return -1;
                else if (b == a)
                    return 0;
                else
                    return 1;
            } else if (isAlternation(a)) {
                if (a == b)
                    return 0;
                else return -1;
            }
            return -2;
        }

        bool possibleConcatenation(const std::string &in) {
            char ch = in[in.length() - 1];
            return isCharacter(ch) || isCloseParenthesis(ch) || isMultiplication(ch);
        }

        bool isCharacter(char ch) {
            return !isAnOperator(ch) && !isCloseParenthesis(ch) &&
                   !isOpenParenthesis(ch);
        }

        bool isAlternation(char a) {
            return a == '|';
        }

        bool isConcatenation(char a) {
            return a == '.';
        }

        bool isMultiplication(char a) {
            return a == '*' || a == '+' || a == '?';
        }

        bool isAnOperator(char a) {
            return a == '*' || a == '+' || a == '?' || a == '|' || a == '.';
        }

        bool isCloseParenthesis(char c) {
            return c == ')';
        }

        bool isOpenParenthesis(char c) {
            return c == '(';
        }
    };
}
#endif //COMPILER_POSTFIX_H
