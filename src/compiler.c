#include "compiler.h"

void throwAndExit(const char* msg, const char* who){
    printf("%s: %s\n", who, msg);
    exit(0);
}