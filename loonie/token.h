#ifndef TOKEN_H
#define TOKEN_H

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

    // LOONIE
    MOD_Loonie,
    branch,
} TokenType;

typedef struct {
    TokenType type;
    char value[64];
    int line, column;
} Token;

const char* token_type_name(TokenType type);

#endif