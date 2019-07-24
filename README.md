bash -x test.sh # debug
# NEXT
- step3

# Learn
- tokenize -> skip space, add information to token

# todo
- node visualize
- error

# note

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
