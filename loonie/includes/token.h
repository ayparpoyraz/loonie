#ifndef TOKEN_H
#define TOKEN_H

#include <stdint.h>


/*
THIS HEADER: FILE FOR TOKENS
GLOBAL_TOKENS: {MOD_Loonie - branch}
*/

typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_OPERATOR,
    TOKEN_SEMICOLON,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_EOF,
    TOKEN_UNKNOWN,

    // GLOBAL V_TOKENS
    MOD_LOONIE,
    branch,
} TokenType;


typedef struct {
    TokenType type;

    const char *value;

    uint32_t line;
    uint32_t column;
} Token;

const char* token_type_name(TokenType type);

#endif