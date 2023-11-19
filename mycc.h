#ifndef MYCC_H
#define MYCC_H

typedef enum {
    TK_RESERVED, // operator
    TK_IDENT, // identifier
    TK_NUM, // int
    TK_EOF, // end
} TokenKind;

typedef struct Token Token;

struct Token {
    TokenKind kind;
    Token *next;
    int val;
    char *str;
    int len;
};

typedef enum {
    ND_ADD, // +
    ND_SUB, // -
    ND_MUL, // *
    ND_DIV, // /
    ND_EQ, // ==
    ND_NE, // !=
    ND_LT, // <
    ND_LE, // <=
    ND_NUM, // int
    ND_ASSIGN, // var assign
    ND_LVAR, // local var
} NodeKind;

typedef struct Node Node;

struct Node {
    NodeKind kind;
    Node *lhs;
    Node *rhs;
    int val;
    int offset; // offset from rbp
};

void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
bool consume(char *op);
Token *consume_ident();
void expect(char *op);
int expect_number();
bool at_eof();
Token *new_token(TokenKind kind, Token *cur, char *str, int len);
bool startsWith(char *p, char *q);
Token *tokenize(char *p);

Node *new_node(NodeKind kind, Node *lhs, Node *rhs);
Node *new_node_num(int val);
Node *assign();
Node *expr();
Node *stmt();
void program();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *primary();
Node *unary();
void gen_lvar(Node *node);
void gen(Node *node);

extern Token *token;
extern char *user_input;
extern Node *code[100];

#endif