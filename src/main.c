#include "lexer.h"

int main()
{
    const char* program = "snd ++\n\tr0 name + 12";
    TokenList tokens = tokenize(program);

    del_TokenList(&tokens);
    return 0;
}
