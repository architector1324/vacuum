#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef unsigned long size_t;
typedef enum{false, true} bool;

typedef enum{
    EMPTY,
    // SPECIAL
    DOUBLE_PLUS, DOUBLE_MINUS, PLUS, MINUS, ASTERIX, SLASH, DOT, COMMA, COLON, SEMICOLON, LESS, GREATER, EQUAL, NOT_EQUAL, LESS_EQUAL, GREATER_EQUAL, L_BRACE, R_BRACE, L_SQUARE_BRACE, R_SQUARE_BRACE, L_FIGURE_BRACE, R_FIGURE_BRACE,
    // REGISTERS
    R0, R1, R2, R3, R4, R5, R6, R7,
    R32_0, R32_1, R32_2, R32_3, R32_4, R32_5, R32_6, R32_7, R32_8, R32_9, R32_10, R32_11, R32_12, R32_13, R32_14, R32_15,

    R16_0, R16_1, R16_2, R16_3, R16_4, R16_5, R16_6, R16_7, R16_8, R16_9, R16_10, R16_11, R16_12, R16_13, R16_14, R16_15,
    R16_16, R16_17, R16_18, R16_19, R16_20, R16_21, R16_22, R16_23, R16_24, R16_25, R16_26, R16_27, R16_28, R16_29, R16_30, R16_31,

    R8_0, R8_1, R8_2, R8_3, R8_4, R8_5, R8_6, R8_7, R8_8, R8_9, R8_10, R8_11, R8_12, R8_13, R8_14, R8_15,
    R8_16, R8_17, R8_18, R8_19, R8_20, R8_21, R8_22, R8_23, R8_24, R8_25, R8_26, R8_27, R8_28, R8_29, R8_30, R8_31,
    R8_32, R8_33, R8_34, R8_35, R8_36, R8_37, R8_38, R8_39, R8_40, R8_41, R8_42, R8_43, R8_44, R8_45, R8_46, R8_47,
    R8_48, R8_49, R8_50, R8_51, R8_52, R8_53, R8_54, R8_55, R8_56, R8_57, R8_58, R8_59, R8_60, R8_61, R8_62, R8_63,

    R128_0, R128_1, R128_2, R128_3, R128_4, R128_5, R128_6, R128_7,

    // MEMORY_SPEC
    REGISTERS_TEMPLATE, STACK_TEMPLATE, MEMORY_TEMPLATE, AUTO_TEMPLATE,
    // OPERATORS
    SND, CALL, RET, ADD, MUL, DIV, OR, AND, XOR, NOT, PUSH, POP, INC, DEC, GO,
    // MODIFERS
    VACUUM, VAR8, VAR16, VAR32, VAR64, VAR128, PAC, PTR, FINAL, DGT,
    // OTHER
    NAME, NUMBER, NEWLINE, SPACE, TAB, END
} Lexem;
typedef enum{SPECIAL, REGISTER, OPERATOR, MODIFER, MEM_TEMPLATE, OTHER} LexemType;

typedef struct{
    const char* src;
    Lexem lexem;
} LexemSrc;

static LexemSrc specials[] = {
    {"\n", NEWLINE},
    {" ", SPACE},
    {"\t", TAB},
    {"++", DOUBLE_PLUS},
    {"--", DOUBLE_MINUS},
    {"+", PLUS},
    {"-", MINUS},
    {"*", ASTERIX},
    {"/", SLASH},
    {".", DOT},
    {",", COMMA},
    {":", COLON},
    {";", SEMICOLON},
    {"!=", NOT_EQUAL},
    {"<=", LESS_EQUAL},
    {">=", GREATER_EQUAL},
    {"<", LESS},
    {">", GREATER},
    {"=", EQUAL},
    {"(", L_BRACE},
    {")", R_BRACE},
    {"[", L_SQUARE_BRACE},
    {"]", R_SQUARE_BRACE},
    {"{", L_FIGURE_BRACE},
    {"}", R_FIGURE_BRACE}
};

static LexemSrc registers[] = {
    {"r0", R0},
    {"r1", R1},
    {"r2", R2},
    {"r3", R3},
    {"r4", R4},
    {"r5", R5},
    {"r6", R6},
    {"r7", R7},

    {"r32_0", R32_0},
    {"r32_1", R32_1},
    {"r32_2", R32_2},
    {"r32_3", R32_3},
    {"r32_4", R32_4},
    {"r32_5", R32_5},
    {"r32_6", R32_6},
    {"r32_7", R32_7},
    {"r32_8", R32_8},
    {"r32_9", R32_9},
    {"r32_10", R32_10},
    {"r32_11", R32_11},
    {"r32_12", R32_12},
    {"r32_13", R32_13},
    {"r32_14", R32_14},
    {"r32_15", R32_15},

    {"r16_0", R16_0},
    {"r16_1", R16_1},
    {"r16_2", R16_2},
    {"r16_3", R16_3},
    {"r16_4", R16_4},
    {"r16_5", R16_5},
    {"r16_6", R16_6},
    {"r16_7", R16_7},
    {"r16_8", R16_8},
    {"r16_9", R16_9},
    {"r16_10", R16_10},
    {"r16_11", R16_11},
    {"r16_12", R16_12},
    {"r16_13", R16_13},
    {"r16_14", R16_14},
    {"r16_15", R16_15},
    {"r16_16", R16_16},
    {"r16_17", R16_17},
    {"r16_18", R16_18},
    {"r16_19", R16_19},
    {"r16_20", R16_20},
    {"r16_21", R16_21},
    {"r16_22", R16_22},
    {"r16_23", R16_23},
    {"r16_24", R16_24},
    {"r16_25", R16_25},
    {"r16_26", R16_26},
    {"r16_27", R16_27},
    {"r16_28", R16_28},
    {"r16_29", R16_29},
    {"r16_30", R16_30},
    {"r16_31", R16_31},

    {"r8_0", R8_0},
    {"r8_1", R8_1},
    {"r8_2", R8_2},
    {"r8_3", R8_3},
    {"r8_4", R8_4},
    {"r8_5", R8_5},
    {"r8_6", R8_6},
    {"r8_7", R8_7},
    {"r8_8", R8_8},
    {"r8_9", R8_9},
    {"r8_10", R8_10},
    {"r8_11", R8_11},
    {"r8_12", R8_12},
    {"r8_13", R8_13},
    {"r8_14", R8_14},
    {"r8_15", R8_15},
    {"r8_16", R8_16},
    {"r8_17", R8_17},
    {"r8_18", R8_18},
    {"r8_19", R8_19},
    {"r8_20", R8_20},
    {"r8_21", R8_21},
    {"r8_22", R8_22},
    {"r8_23", R8_23},
    {"r8_24", R8_24},
    {"r8_25", R8_25},
    {"r8_26", R8_26},
    {"r8_27", R8_27},
    {"r8_28", R8_28},
    {"r8_29", R8_29},
    {"r8_30", R8_30},
    {"r8_31", R8_31},
    {"r8_32", R8_32},
    {"r8_33", R8_33},
    {"r8_34", R8_34},
    {"r8_35", R8_35},
    {"r8_36", R8_36},
    {"r8_37", R8_37},
    {"r8_38", R8_38},
    {"r8_39", R8_39},
    {"r8_40", R8_40},
    {"r8_41", R8_41},
    {"r8_42", R8_42},
    {"r8_43", R8_43},
    {"r8_44", R8_44},
    {"r8_45", R8_45},
    {"r8_46", R8_46},
    {"r8_47", R8_47},
    {"r8_48", R8_48},
    {"r8_49", R8_49},
    {"r8_50", R8_50},
    {"r8_51", R8_51},
    {"r8_52", R8_52},
    {"r8_53", R8_53},
    {"r8_54", R8_54},
    {"r8_55", R8_55},
    {"r8_56", R8_56},
    {"r8_57", R8_57},
    {"r8_58", R8_58},
    {"r8_59", R8_59},
    {"r8_60", R8_60},
    {"r8_61", R8_61},
    {"r8_62", R8_62},
    {"r8_63", R8_63},

    {"r128_0", R128_0},
    {"r128_1", R128_1},
    {"r128_2", R128_2},
    {"r128_3", R128_3},
    {"r128_4", R128_4},
    {"r128_5", R128_5},
    {"r128_6", R128_6},
    {"r128_7", R128_7},
};

static LexemSrc operators[] = {
    {"snd", SND},
    {"call", CALL},
    {"ret", RET},
    {"add", ADD},
    {"mul", MUL},
    {"div", DIV},
    {"or", OR},
    {"and", AND},
    {"xor", XOR},
    {"not", NOT},
    {"push", PUSH},
    {"pop", POP},
    {"inc", INC},
    {"dec", DEC},
    {"go", GO}
};

static LexemSrc modifers[] = {
    {"vacuum", VACUUM},
    {"var8", VAR8},
    {"var16", VAR16},
    {"var32", VAR32},
    {"var64", VAR64},
    {"var128", VAR128},
    {"pac", PAC},
    {"ptr", PTR},
    {"final", FINAL},
    {"dgt", DGT}
};

static LexemSrc memory_templates[] = {
    {"r", REGISTERS_TEMPLATE},
    {"s", STACK_TEMPLATE},
    {"m", MEMORY_TEMPLATE},
    {"a", AUTO_TEMPLATE}
};

static struct{
    LexemType type;
    const LexemSrc* src;
    size_t count;
} lexems[] = {
    {SPECIAL, specials, 25},
    {REGISTER, registers, 128},
    {OPERATOR, operators, 15},
    {MODIFER, modifers, 10},
    {MEM_TEMPLATE, memory_templates, 4}
};
static size_t lexems_count = 5;

typedef struct{
    Lexem lex;
    LexemType lex_type;

    const char* word;
    size_t word_len;

    size_t num_val;
} Token;

typedef struct{
    Token* list;
    size_t count;
} TokenList;

// CONSTRUCTORS
Token con_Token(Lexem lex, LexemType type, const char* word, size_t word_len, size_t num_val);
TokenList con_TokenList();

// DESTRUCTORS
void del_TokenList(TokenList* list);

// METHODS
TokenList tokenize(const char* prog); // create a list of tokens from source code

void getWord(const char** prog, TokenList* list);
bool getLexem(const char* word, size_t len, TokenList* list);
void getSpecial(const char** prog, bool ignore_spaces, TokenList* list);

void addToken(Token token, TokenList* list);

#endif // LEXER_H
