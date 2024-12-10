.386
data segment use16
sth db 10h dup(0)
n dw 0FFF0h   
s db 10h dup(0)
data ends

code segment use16
assume cs:code, ds:data
;void f(short int n, char s[])
;注意f()的参数通过堆栈传递,其中n就是[bp+4], s就是[bp+6]。
;在函数f()中不可直接引用data段中的变量n及数组s, 否则会产生编译错误。
f proc near
   push bp
   mov bp, sp
;请在#1_begin和#1_end之间补充代码实现以下功能:
;把16位符号数n转化成十进制字符串保存到数组s中,并在字符串后面填充'$'
;例如,当n=0FFF0h时, s的内容为: '-', '1', '6', '$'
;#1_begin-----------=========------------------
    mov ax, [bp+4]    ; 获取参数n
    mov di, [bp+6]    ; 获取参数s的地址
    mov bx, di        ; 保存字符串起始地址
    
    ; 检查是否为负数
    test ax, ax
    jns positive
    neg ax            ; 如果是负数，转为正数
    mov byte ptr [di], '-'  ; 写入负号
    inc di            ; 移动指针
    
positive:
    mov cx, 0         ; 用于计数
    mov si, 10        ; 除数为10

divide:
    xor dx, dx        ; 清空dx，准备除法
    div si            ; ax除以10，商在ax，余数在dx
    add dl, '0'       ; 转换为ASCII码
    push dx           ; 保存数字字符
    inc cx            ; 计数器加1
    test ax, ax       ; 检查商是否为0
    jnz divide        ; 不为0继续除

store:
    pop dx            ; 取出数字字符
    mov [di], dl      ; 存入字符串
    inc di            ; 移动指针
    loop store        ; 循环直到所有数字都取出

    mov byte ptr [di], '$'  ; 添加结束符
;#1_end-------------=========------------------
   pop bp
   ret
f endp

main:
   mov ax, data
   mov ds, ax
   mov ax, offset s
   push ax
   push [n]
   call f
   add sp, 4
   mov ah, 9
   mov dx, offset s
   int 21h
   mov ah, 4Ch
   int 21h
code ends
end main
