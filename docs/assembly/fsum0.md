;本题要求:
;完成3项程序填空,调用函数f()求1+2+3+...+n之和并保存到变量sum中,
;注意sum不会超过0FFFFh,故在计算过程中不需要考虑加法溢出
;==========请把在完成填空后把本文件保存到src\main.asm==================
;==========选中main.sh及src文件夹->右键->压缩成submit.zip提交==========
.386
data segment use16
sth db 10h dup(0)    ; 定义一个长度为10h的字节数组，初始值为0
n dw 3               ; 定义一个字变量n，初始值为3
sum dw 0             ; 定义一个字变量sum，初始值为0
data ends

code segment use16
assume cs:code, ds:data
;函数f()原型:
;   short int f(short int n, short int *psum);
;函数f()功能:
;   计算1+2+3+...n的和, 并把和保存到*psum中。例如当n=3时, *psum=6。
;提示:
;   f()的参数通过堆栈传递, 其中n就是[bp+4], psum就是[bp+6]。
;注意:
;   在函数f()中不可直接引用data段中的变量n及sum, 否则会编译失败
f proc near
   push bp           ; 保存当前的BP寄存器值
   mov bp, sp        ; 将SP寄存器的值赋给BP寄存器，建立栈帧
   mov bx, 0         ; 初始化BX寄存器为0
   mov cx, 0         ; 初始化CX寄存器为0
;#1_begin--------
   mov cx, [bp+4]    ; 从堆栈获取参数n到CX作为循环计数器
   inc cx            ; 因为loop指令会先减1再判断，所以这里先加1
;#1_end----------
   mov bx, [bp+6]    ; 从堆栈获取参数*psum的地址到BX
   xor ax, ax        ; 将AX寄存器清零
next:
   add ax, cx        ; 将CX的值加到AX中
   loop next         ; 循环直到CX为0
;#2_begin------
   mov [bx], ax      ; 将计算结果保存到*psum指向的内存位置
;#2_end--------
   pop bp            ; 恢复之前保存的BP寄存器值
   ret               ; 返回调用者
f endp

main:
   mov ax, data      ; 将data段的段地址加载到AX寄存器
   mov ds, ax        ; 将AX寄存器的值加载到DS寄存器，设置数据段
   mov ax, offset sum; 将sum的偏移地址加载到AX寄存器
;#3_begin------------
   push ax           ; 压入sum的地址作为第二个参数
;#3_end--------------
   push [n]          ; 传递n的值给函数f()
   call f            ; 调用函数f()
   add sp, 4         ; 清除堆栈上的2个参数
   mov ax, [sum]     ; 将sum的值加载到AX寄存器，跟踪时请检查当n=3时,ax应该等于6
   mov ah, 4Ch       ; 设置功能号为4Ch，表示终止程序
   int 21h           ; 调用DOS中断21h，终止程序
code ends
end main
;==========请在完成填空后把本文件保存到src\main.asm================
