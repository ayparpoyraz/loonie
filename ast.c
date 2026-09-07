typedef enum{
    LOO_NUMBER,
    LOO_BINARY_OP,
    LOO_ASSIGMENT,
    LOO_IF,
    LOO_RETURN,
    LOO_BLOCK
}LOO_TYPE;

typedef struct ASTNode
{

    LOO_TYPE looType;

    // i - u  //identifier
    char value[64];

    struct ASTNode* left;
    struct ASTNode* right;

    char op[3];
    struct ASTNode* condition;
    struct ASTNode* body;

    struct ASTNode** statements;
    int statement_count;

};
