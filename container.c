#include "9cc.h"
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

void debug_show(Token *cur) {
	Token *target = cur;
	for(;;){
		if (target == NULL)break;
		printf("kind %d 0==NUM, 1==other\n", target->kind != TK_NUM);
		printf("str is %s\n", target->str);
		printf("val is %d\n", target->val);
		printf("length is %d\n", target->len);
		printf("-----------------\n");
		target = target->next;
	}
}
