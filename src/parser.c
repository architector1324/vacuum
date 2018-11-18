#include "parser.h"

// CONSTRUCTORS
Node con_Node(const Token* value, NodeList childs){
    Node result = {childs, value};
    return result;
}
Node* new_Node(const Token* value, NodeList childs){
    Node* result = (Node*)malloc(sizeof(Node));
    *result = con_Node(value, childs);
    return result;
}

NodeList con_NodeList(){
    Node** list = (Node**)malloc(sizeof(Node*)); 
    NodeList result = {list, 0};
    return result;
}
// DESTRUCTORS
void del_NodeList(NodeList* list){
    size_t count = list->count;
    for(size_t i = 0; i < count; i++){
        Node* curr = list->list[i];
        if(curr != NULL) del_Node(curr);
    }
    free(list->list);
}
void del_Node(Node* node){
    del_NodeList(&node->childs);
    free(node);
}

// METHODS
Node* parse(const TokenList* list){
    Node* root = new_Node(NULL, con_NodeList());


    return root;
}

void addNode(Node* node, NodeList* list){
    list->list = realloc(list->list, (list->count + 1) * sizeof(Node*));
    list->list[list->count++] = node;
}