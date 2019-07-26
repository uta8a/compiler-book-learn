#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------token------------
typedef enum {
	TK_RESERVED, // symbol
	TK_EQ, // ==
	TK_NE, // !=
	TK_LE, // <=
	TK_GE, // >=
	TK_NUM,		 // number token
	TK_EOF,		 // end of input token
} TokenKind;

typedef struct Token Token;

struct Token {
	TokenKind kind;
	Token *next;
	int val;
	char *str;
	int len;
};

Token *token;

// ----------Node--------------
typedef enum {
	ND_ADD, // +
	ND_SUB, // -
	ND_MUL, // *
	ND_DIV, // /
	ND_NUM, // number
	ND_EQ, // ==
	ND_NE, //!=
	ND_LT, // <
	ND_GT, // >
	ND_LE, // <=
	ND_GE, // >=
} NodeKind;

typedef struct Node Node;

struct Node {
	NodeKind kind;
	Node *lhs;
	Node *rhs;
	int val;
};

Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *term();
// -------------error---------------------
char *user_input;
void error_at(char *loc, char *fmt, ...);
// --------------debug_util---------------
void debug_show(Token *cur);
// --------------token--------------------
Token *new_token(TokenKind kind, Token *cur, char *str, int len);
Token *tokenize(char *p);
// --------------codegen------------------
void gen(Node *node);
