```asm

data segment
a db "ABC"
s db "Hello$world!", 0Dh, 0Ah, 0
;把s中字符串打印到屏幕上
data ends

main:
   mov ax, seg s
   ;ax存放s的段地址
   mov ds, ax
   mov bx, 0

```

```c

putchar(s[i]);
==
putchar(0[s+i]);

0 stands for empty pointer
    
```
    
```asm
    
    mov si, 0
    ;si存放s的偏移地址
    mov ah, 09h
    ;功能号
    mov dx, si
    ;dx存放s的偏移地址
    int 21h
    ;调用dos的21h中断
    mov ah, 4ch
    ;功能号
    int 21h
    ;调用dos的21h中断
    
    end main
    
```

&    |  ^   ~    <<  >> _rotl() _rotr()
and  or xor not shl shr  rol    ror//循环左右移