#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct {
    const char* source;
    int pos;
    int line;
    int column;
} Lexer;

void lexer_init(Lexer* lex, const char* source);
Token get_next_token(Lexer* lex);

#endif