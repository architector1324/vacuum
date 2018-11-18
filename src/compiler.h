#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>

static size_t curr_word = 0;
static size_t curr_line = 0;
static size_t curr_token = 0;

void next(const char* word);
void throwAndExit(const char* msg, const char* who);

#endif // COMPILER_H