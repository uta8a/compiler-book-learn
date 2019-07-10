#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	TK_RESERVED, // symbol
	TK_NUM,		 // number token 
	TK_EOF,		 // end of input token
} TokenKind;

typedef struct Token Token;

// token type
struct Token {
	TokenKind kind;
	Token *next;
	int val;
	char *str;
};

// now focused token
Token *token;

// error report function
// like printf
char *user_input;

void error_at(char *loc, char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	int pos = loc - user_input;
	fprintf(stderr, "%s\n", user_input);
	fprintf(stderr, "%*s", pos, ""); // pos white space
	fprintf(stderr, "^ ");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

// if next token is ok symbol, progress one token and return true
// otherwise false
bool consume(char op) {
	if (token->kind != TK_RESERVED || token->str[0] != op)
		return false;
	token = token->next;
	return true;
}

void expect(char op) {
	if (token->kind != TK_RESERVED || token->str[0] != op)
		error_at(token->str, "'%c' is unexpected", op);
	token = token->next;
}

// next token is number, progress one token
// report error
int expect_number() {
	if (token->kind != TK_NUM)
		error_at(token->str, "Not a number");
	int val = token->val;
	token = token->next;
	return val;
}

bool at_eof() {
	return token->kind ==TK_EOF;
}

Token *new_token(TokenKind kind, Token *cur, char *str) {
	Token *tok = calloc(1, sizeof(Token));
	tok->kind = kind;
	tok->str = str;
	cur->next = tok;
	return tok;
}

// return tokenized
Token *tokenize(char *p) {
	Token head;
	head.next = NULL;
	Token *cur = &head;

	while (*p) {
		// whitespace skip
		if (isspace(*p)) {
			p++;
			continue;
		}

		if (*p == '+' || *p == '-') {
			cur = new_token(TK_RESERVED, cur, p++);
			continue;
		}

		if (isdigit(*p)) {
			cur = new_token(TK_NUM, cur, p);
			cur->val = strtol(p, &p, 10);
			continue;
		}

		error_at(token->str, "can't tokenize");
	}

	new_token(TK_EOF, cur, p);
	return head.next;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "number of argument is not true.\n");
		return 1;
	}

	// tokenize
	token = tokenize(argv[1]);
	user_input = argv[1];

	// assembly front part
	printf(".intel_syntax noprefix\n");
	printf(".global main\n");
	printf("main:\n");

	// formula head must be number
	// mov
	printf("  mov rax, %d\n", expect_number());

	// use `+ num` or `- num` pattern
	while(!at_eof()) {
		if (consume('+')) {
			printf("  add rax, %d\n", expect_number());
			continue;
		}

		expect('-');
		printf("  sub rax, %d\n", expect_number());
	}

	printf("  ret\n");
	return 0;
}
