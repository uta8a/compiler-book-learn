#include "9cc.h"
// -------------token-----------------------

bool consume(char *op) {
	if ((token->kind != TK_RESERVED &&
		token->kind != TK_EQ &&
		token->kind != TK_NE &&
		token->kind != TK_LE &&
		token->kind != TK_GE) ||
		strlen(op) != token->len ||
		memcmp(token->str, op, token->len))
		return false;
	token = token->next;
	return true;
}
void expect(char *op) {
	if ((token->kind != TK_RESERVED &&
		token->kind != TK_EQ &&
		token->kind != TK_NE &&
		token->kind != TK_LE &&
		token->kind != TK_GE) ||
		strlen(op) != token->len ||
		memcmp(token->str, op, token->len))
		error_at(token->str, "'%c' is unexpected", op);
	token = token->next;
}
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
Token *new_token(TokenKind kind, Token *cur, char *str, int len) {
	Token *tok = calloc(1, sizeof(Token));
	tok->kind = kind;
	tok->str = str;
	tok->len = len;
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

		if (strncmp(p, "==", 2) == 0) {
			cur = new_token(TK_EQ, cur, p, 2);
			p+=2;
			continue;
		}
		if (strncmp(p, "!=", 2) == 0) {
			cur = new_token(TK_NE, cur, p, 2);
			p+=2;
			continue;
		}
		if (strncmp(p, "<=", 2) == 0) {
			cur = new_token(TK_LE, cur, p, 2);
			p+=2;
			continue;
		}
		if (strncmp(p, ">=", 2) == 0) {
			cur = new_token(TK_GE, cur, p, 2);
			p+=2;
			continue;
		}

		if (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '(' || *p == ')' || *p == '<' || *p == '>') {
			cur = new_token(TK_RESERVED, cur, p++, 1);
			continue;
		}


		if (isdigit(*p)) {
			cur = new_token(TK_NUM, cur, p, -1/* wrong? */);
			cur->val = strtol(p, &p, 10);
			continue;
		}

		error_at(token->str, "can't tokenize");
	}

	new_token(TK_EOF, cur, p, -2 /* wrong? */);
	return head.next;
}

Node *new_node(NodeKind kind, Node *lhs, Node *rhs) {
	Node *node = calloc(1,sizeof(Node));
	node->kind = kind;
	node->lhs = lhs;
	node->rhs = rhs;
	return node;
}

Node *new_node_num(int val) {
	Node *node = calloc(1, sizeof(Node));
	node->kind = ND_NUM;
	node->val = val;
	return node;
}

Node *expr() {
	Node *node = equality();
}

Node *equality() {
	Node *node = relational();

	for(;;) {
		if (consume("=="))
			node = new_node(ND_EQ, node, relational());
		else if (consume("!="))
			node = new_node(ND_NE, node, relational());
		else
			return node;
	}
}

Node *relational() {
	Node *node = add();
	for (;;) {
		if (consume("<"))
			node = new_node(ND_LT, node, add());
		else if (consume("<="))
			node = new_node(ND_LE, node, add());
		else if (consume(">"))
			node = new_node(ND_LT, add(), node);
		else if (consume(">="))
			node = new_node(ND_LE, add(), node);
		else
			return node;
	}
}

Node *add() {
	Node *node = mul();
	for(;;) {
		if (consume("+"))
			node =  new_node(ND_ADD, node, mul());
		else if (consume("-"))
			node = new_node(ND_SUB, node, mul());
		else
			return node;
	}
}

Node *mul() {
	Node *node = unary();

	for(;;) {
		if (consume("*"))
			node = new_node(ND_MUL, node, unary());
		else if (consume("/"))
			node = new_node(ND_DIV, node, unary());
		else
			return node;
	}
}

Node *unary() {
	if (consume("+"))
		return term();
	if (consume("-"))
		return new_node(ND_SUB, new_node_num(0), term());
	return term();
}

Node *term() {
	if (consume("(")) {
		Node *node = expr();
		expect(")");
		return node;
	}

	return new_node_num(expect_number());
}
