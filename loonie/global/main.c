#include <stdio.h>
#include "lexer.h"
#include "token.h"

int main() {
    const char* source =
        "int x = 5 + y;\n"
        "if (x <= 10) {\n"
        "    return x;\n"
        "}\n";

    Lexer lex;
    lexer_init(&lex, source);

    Token token;
    do {
        token = get_next_token(&lex);
        printf("[%-10s] value=\"%s\" (line %d, col %d)\n",
               token_type_name(token.type), token.value, token.line, token.column);
    } while (token.type != TOKEN_EOF);

    return 0;
}