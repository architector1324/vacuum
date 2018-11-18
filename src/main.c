#include "parser.h"

int main()
{
    const char* program = "snd ++\n\tr0 name + 12";
    TokenList tokens = tokenize(program);
    const Node* ast = parse(&tokens);

    del_TokenList(&tokens);
    del_Node(ast);
    
    return 0;
}
