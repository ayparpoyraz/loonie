#include "lexer.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

const char* keywords[] = {
    "int", "float", "if", "else", "while", "for", "return", NULL
};

static int is_keyword(const char* word) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(word, keywords[i]) == 0) return 1;
    }
    return 0;
}

void lexer_init(Lexer* lex, const char* source) {
    lex->source = source;
    lex->pos = 0;
    lex->line = 1;
    lex->column = 1;
}

static char peek(Lexer* lex) {
    return lex->source[lex->pos];
}

static char advance(Lexer* lex) {
    char c = lex->source[lex->pos];
    lex->pos++;
    if (c == '\n') {
        lex->line++;
        lex->column = 1;
    } else {
        lex->column++;
    }
    return c;
}

void skip_whitespace_and_comments(Lexer* lex) {
    while (1) {
        char c = peek(lex);
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            advance(lex);
        } else if (c == '/' && lex->source[lex->pos + 1] == '/') {

            while (peek(lex) != '\n' && peek(lex) != '\0') advance(lex);
        } else if (c == '/' && lex->source[lex->pos + 1] == '*') {



            
            advance(lex); advance(lex);
            while (!(peek(lex) == '*' && lex->source[lex->pos + 1] == '/') && peek(lex) != '\0') {
                advance(lex);
            }
            if (peek(lex) != '\0') { advance(lex); advance(lex); }
        } else {
            break;
        }
    }
}

Token get_next_token(Lexer* lex) {
    skip_whitespace_and_comments(lex);

    Token token;
    token.line = lex->line;
    token.column = lex->column;
    token.value[0] = '\0';

    char c = peek(lex);

    if (c == '\0') {
        token.type = TOKEN_EOF;
        strcpy(token.value, "EOF");
        return token;
    }

    if (isalpha(c) || c == '_') {
        int i = 0;
        while (isalnum(peek(lex)) || peek(lex) == '_') {
            token.value[i++] = advance(lex);
        }
        token.value[i] = '\0';
        token.type = is_keyword(token.value) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
        return token;
    }

   
    if (isdigit(c)) {
        int i = 0;
        while (isdigit(peek(lex))) {
            token.value[i++] = advance(lex);
        }
        if (peek(lex) == '.') {
            token.value[i++] = advance(lex);
            while (isdigit(peek(lex))) {
                token.value[i++] = advance(lex);
            }
        }
        token.value[i] = '\0';
        token.type = TOKEN_NUMBER;
        return token;
    }

    if (c == '"') {
        advance(lex); 
        int i = 0;
        while (peek(lex) != '"' && peek(lex) != '\0') {
            token.value[i++] = advance(lex);
        }
        advance(lex); 
        token.value[i] = '\0';
        token.type = TOKEN_STRING;
        return token;
    }

  
    if (c == '=' || c == '!' || c == '<' || c == '>') {
        char first = advance(lex);
        if (peek(lex) == '=') {
            char second = advance(lex);
            token.value[0] = first;
            token.value[1] = second;
            token.value[2] = '\0';
        } else {
            token.value[0] = first;
            token.value[1] = '\0';
        }
        token.type = TOKEN_OPERATOR;
        return token;
    }


    if (strchr("+-*/", c)) {
        token.value[0] = advance(lex);
        token.value[1] = '\0';
        token.type = TOKEN_OPERATOR;
        return token;
    }


    if (c == ';') { advance(lex); token.type = TOKEN_SEMICOLON; strcpy(token.value, ";"); return token; }
    if (c == '(') { advance(lex); token.type = TOKEN_LPAREN;    strcpy(token.value, "("); return token; }
    if (c == ')') { advance(lex); token.type = TOKEN_RPAREN;    strcpy(token.value, ")"); return token; }
    if (c == '{') { advance(lex); token.type = TOKEN_LBRACE;    strcpy(token.value, "{"); return token; }
    if (c == '}') { advance(lex); token.type = TOKEN_RBRACE;    strcpy(token.value, "}"); return token; }

  
    advance(lex);
    token.type = TOKEN_UNKNOWN;
    token.value[0] = c;
    token.value[1] = '\0';
    return token;
}
