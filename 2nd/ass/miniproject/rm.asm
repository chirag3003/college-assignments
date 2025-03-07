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
    file_name resb 256

section .text
global _start

_start:
    ; Get file name from command line argument
    pop r8
    pop r8
    pop r8
    mov esi, file_name
    up_fname: 
        mov al, [r8]
        cmp al, 0
        je next_fname
        mov [esi], al
        inc r8
        inc esi
        jmp up_fname
    next_fname:
        mov byte [esi], 0

    ; Unlink (delete) the file
    opr 87, file_name, 0, 0  ; 87 is the syscall number for unlink

    ; Exit the program
    opr 60, 0, 0, 0 ; 60 is the syscall number for exit