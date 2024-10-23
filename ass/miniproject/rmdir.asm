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
    dir_name resb 256

section .text
global _start

_start:
    ; Get directory name from command line argument
    pop r8
    pop r8
    mov esi, dir_name
    up_dname: 
        mov al, [r8]
        cmp al, 0
        je next_dname
        mov [esi], al
        inc r8
        inc esi
        jmp up_dname
    next_dname:
        mov byte [esi], 0

    ; Rmdir (delete) the directory
    opr 84, dir_name, 0, 0, 0  ; 84 is the syscall number for rmdir

    ; Exit the program
    opr 60, 0, 0, 0, 0  ; 60 is the syscall number for exit