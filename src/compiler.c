#include "compiler.h"

void next(const char* word){
    curr_word++;
    curr_token++;
    if(word[0] == '\n'){
        curr_word = 0;
        curr_line++;
    }
}
void throwAndExit(const char* msg, const char* who){
    printf("%s: %s (%zu line %zu word)\n", who, msg, curr_line + 1, curr_word);
    exit(0);
}