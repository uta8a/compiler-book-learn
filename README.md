bash -x test.sh # debug

# NEXT
- step3

# Learn
- tokenize -> skip space, add information to token
# todo
- step3 syntax learn, understand
- error awesome, dig to learn

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

