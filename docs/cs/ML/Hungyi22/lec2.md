**(Link)[https://www.bilibili.com/video/BV1Wv411h7kN?p=18]**

!!! note
    - Distinguish
        - Model bias: the needle isn't in the haystack,too small,inflexible
        - Optimization issue:  flexible enough,but if Deeper network < smaller network


## Proj 4 Scheme

### Problem 3 Implement the missing part of scheme_eval

```python
def scheme_eval(expr, env, _=None): # Optional third argument is ignored
    """Evaluate Scheme expression EXPR in Frame ENV.
        scheme_eval 在给定环境中求值一个 Scheme 表达式。
        scheme_eval 将评估重定向至在 scheme_forms.py 中找到的适当 do_?_form 函数
        scheme_apply 对某些参数应用一个过程。
    >>> expr = read_line('(+ 2 2)')
    >>> expr
    Pair('+', Pair(2, Pair(2, nil)))
    >>> scheme_eval(expr, create_global_frame())
    4
    """
    # 1. 处理原子符号 (Scheme 符号或自我评估的表达式)
    if scheme_symbolp(expr):
        return env.lookup(expr)  # 查找符号在环境中的值
    
    # 2. 处理自我评估的表达式
    elif self_evaluating(expr):
        return expr  # 直接返回表达式（例如数字、字符串等）

    # 3. 处理非原子表达式（即列表）
    if not scheme_listp(expr):
        raise SchemeError('malformed list: {0}'.format(repl_str(expr)))  # 如果不是列表，抛出错误
    
    first, rest = expr.first, expr.rest  # 获取表达式的第一个元素和其余部分

    # 4. 如果第一个元素是特殊形式（例如 `if`, `define` 等），使用相应的处理函数
    if scheme_symbolp(first) and first in scheme_forms.SPECIAL_FORMS:
        return scheme_forms.SPECIAL_FORMS[first](rest, env)  # 调用特殊形式的处理函数
    
    else:
        # 5. 一般的组合式，首先求值操作符，然后求值参数，最后应用操作符到参数
        # 假设我们有表达式 (+ 2 2)，
        # first = +，这时 procedure = scheme_eval(first, env) 会返回 `+` 操作符，
        # rest = (2 2)，这时 args = rest.map(lambda exp: scheme_eval(exp, env)) 会返回 [2, 2]，即两个数字 2。
        # 最后，scheme_apply(procedure, args, env) 会执行 `+` 操作符，传入参数 [2, 2]，结果为 4

        # BEGIN PROBLEM 3
        procedure = scheme_eval(first, env)  # 求值操作符
        args = rest.map(lambda exp: scheme_eval(exp, env))  # 求值所有参数
        return scheme_apply(procedure, args, env)  # 应用操作符到参数
        # END PROBLEM 3
```