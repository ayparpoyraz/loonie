#!/bin/bash

SRC="loonie/main.c loonie/lexer.c loonie/token.c"

OUT="compiler"

gcc $SRC -o $OUT -Wall -Wextra

