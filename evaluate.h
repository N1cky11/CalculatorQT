#include <string>
#include <stack>

class Evaluate
{
public:
    int operator() (std::string tokens) ;
    int precedence(char op) ;
    int applyOp(int a, int b, char op) ;
};

