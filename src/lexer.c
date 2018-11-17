#include "lexer.h"
#include "compiler.h"

// CONSTRUCTORS
Token con_Token(Lexem lex, LexemType type, const char* word, size_t word_len, size_t num_val){
    Token result = {lex, type, word, word_len, num_val};
    return result;
}
TokenList con_TokenList(){
    const Token* list = (const Token*)malloc(sizeof(Token));
    TokenList result = {list, 0};
    return result;
}

// DESTRUCTORS
void del_TokenList(TokenList* list){
    free(list->list);
}

// METHODS
TokenList tokenize(const char* prog){
    TokenList result = con_TokenList();

    /* 'word' is an alphanumeric char array separated by
       start / end of source stream or lexems from
       'specials' table
    */

    while(*prog){
        getWord(&prog, &result);
        getSpecial(&prog, true, &result);
    }
  
    return result;
}

void getWord(const char** prog, TokenList* list){
    size_t len = 0;
    bool is_num = true;
    const char* word = *prog;

    while(isalnum(**prog)){
        if(!isdigit(**prog)) is_num = false;
        *prog += 1;
        len++;
    } 
    
    if(len > 0){
        if(is_num)addToken(con_Token(NUMBER, OTHER, 0, 0, strtoul(word, NULL, 10)), list);
        else if(!getLexem(word, len, list))
            addToken(con_Token(NAME, OTHER, word, len, 0), list);
    }
}
bool getLexem(const char* word, size_t len, TokenList* list){
    for(size_t i = 1; i < lexems_count; i++){
        const LexemSrc* curr = lexems[i].src;
        size_t count = lexems[i].count;
        LexemType type = lexems[i].type;

        for(size_t j = 0; j < count; j++){
            const char* curr_lex = curr[j].src;
            if(!strncmp(word, curr_lex, len)){
                Token t = con_Token(curr[j].lexem, type, curr_lex, len, 0);
                addToken(t, list);
                return true;
            }
        }
    }
    
    return false;
}
void getSpecial(const char** prog, bool ignore_spaces, TokenList* list){
    char buf[2] = {**prog, *(*prog + 1)};
    size_t count = lexems[0].count;

    for(size_t i = 0; i < count; i++){
        LexemSrc curr_lex = specials[i];
        size_t curr_lex_len = strnlen(curr_lex.src, 2);

        if(!strncmp(buf, curr_lex.src, curr_lex_len)){
            Token t = con_Token(curr_lex.lexem, SPECIAL, curr_lex.src, curr_lex_len, 0);
            if(ignore_spaces){
                if(curr_lex.lexem != SPACE && curr_lex.lexem != TAB) addToken(t, list);
            } else addToken(t, list);

            *prog += curr_lex_len;
            return;
        }
    }
    throwAndExit("unexpected symbol", "Lexer");
}

void addToken(Token token, TokenList* list){
    list->list = realloc(list->list, (list->count + 1) * sizeof(Token));
    list->list[list->count++] = token;
}