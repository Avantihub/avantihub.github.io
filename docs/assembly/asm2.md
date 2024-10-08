## October 8th


```asm
data segment 
abc 
ddd dd 12345678h
data ends

code segment
assume cs:code,ds:data
main:
    mov ax,seg abc
    mov ds,ax
    ;add abc,xyz

    add abc,5678h
    mov ax,xyz
    add abc,ax
    mov ah,4Ch
    mov al,0; al==return code
    int 21h;exit 0


code ends
end main
```    