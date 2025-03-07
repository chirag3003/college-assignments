section .data
newl     db  10
newl_len equ $-newl

%macro opr 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

section .bss
    buff     resb 512
    buff_len resq 1
    fhandle  resq 1
    fname    resb 512

section .text
global  _start

_start:
    pop r8
    pop r8
    pop r8
    mov esi,        fname
    up: mov al,     [r8]
    cmp al,         00
    je  next
    mov [esi],      al
    inc r8
    inc esi
    jmp up
    next:
    opr 2, fname, 000000q, 0777q ; open file
    mov [fhandle],  rax
    mov rbx,        rax
    opr 0, rbx, buff, 5111; read
    mov [buff_len], rax

    opr 1, 1, buff, [buff_len] ; write
    opr 1,1, newl, newl_len
    opr 3, [fhandle], 0, 0 ; close
    opr 60, 0, 0, 0 ; exit