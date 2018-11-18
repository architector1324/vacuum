#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

struct Node;

typedef struct{
    struct Node** list;
    ssize_t count;
} NodeList;

typedef struct Node{
    NodeList childs;
    const Token* value;
} Node;

// CONSTRUCTORS
Node con_Node(const Token* value, NodeList childs);
Node* new_Node(const Token* value, NodeList childs);

NodeList con_NodeList();

// DESTRUCTORS
void del_NodeList(NodeList* list);
void del_Node(Node* node);

// METHODS
Node* parse(const TokenList* list);
void addNode(Node* node, NodeList* list);

#endif // PARSER_H
