## Format of the stack segment

```asm

stk segment stack;
db 200h dup('S');
stk ends

```
!!! Info
    为什么设成S?
    为了在出现一堆S时认出这是栈区，而不是数据区。

```asm

push abc[0]

Assume:
ss=1000h, sp=200h
1.sp-=2
指针向上移动两个字节，指向栈顶
2.word ptr ss:sp=abc[0]

```

```asm