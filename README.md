# **C Compiler**

bash -x test.sh # debug
# Learn
- tokenize -> skip space, add information to token
- single quote, double quote https://stackoverflow.com/questions/3683602/single-quotes-vs-double-quotes-in-c-or-c
- strtol(p, &p, 10) -> &p is other not number string, so next step working.
- usage Vim: yank https://www.softel.co.jp/blogs/tech/archives/2664
# todo
- node visualize
- error
# note
- len is NUM->-1, EOF->-2

# misc
```
expr       = equality
equality   = relational ("==" relational | "!=" relational)*
relational = add ("<" add | "<=" add | ">" add | ">=" add)*
add        = mul ("+" mul | "-" mul)*
mul        = unary ("*" unary | "/" unary)*
unary      = ("+" | "-")? term
term       = num | "(" expr ")"
```
- tokenize -> result is token -> build node using token when consume
- token is consumed by expr() 
- `new_token` = `add_token`
- token length depends on like 111111, or == or +, so it's decided when you parse it. so tokenize is decide len part. 
- split file
	- main: assembly
	- 9cc.h: util&declaration
	- parse: Node
	- codegen: to asm
	- container: misc
- 
