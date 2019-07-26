#include "9cc.h"

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "number of argument is not true.\n");
		return 1;
	}

	// tokenize
	user_input = argv[1];
	token = tokenize(user_input);
	
	// DEBUG_BEGIN
	//debug_show(token);
	//printf("----------------------\n");
	// DEBUG_END
	
	Node *node = expr();
	// assembly front part
	printf(".intel_syntax noprefix\n");
	printf(".global main\n");
	printf("main:\n");

	gen(node);

	printf("  pop rax\n");
	printf("  ret\n");
	return 0;
}
