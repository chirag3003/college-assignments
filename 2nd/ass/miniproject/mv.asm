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
    src_fhandle  resq 1
    dst_fhandle  resq 1
    src_fname    resb 256
    dst_fname    resb 256

section .text
global  _start

_start:
    ; Get source file name
    pop r8
    pop r8
    pop r8
    mov esi, src_fname
up_src: 
    mov al, [r8]
    cmp al, 0
    je next_src
    mov [esi], al
    inc r8
    inc esi
    jmp up_src
next_src:
    mov byte [esi], 0

    ; Get destination file name
    pop r8
    mov esi, dst_fname
up_dst: 
    mov al, [r8]
    cmp al, 0
    je next_dst
    mov [esi], al
    inc r8
    inc esi
    jmp up_dst
next_dst:
    mov byte [esi], 0

    ; Open source file
    opr 2, src_fname, 0, 0 ; 2 is the syscall number for open
    test rax, rax
    js exit_error
    mov [src_fhandle], rax

    ; Create destination file
    opr 85, dst_fname, 577, 0644  ; 85 is the syscall number for open with O_CREAT | O_WRONLY
    test rax, rax
    js exit_error
    mov [dst_fhandle], rax

copy_loop:
    ; Read from source file
    mov rdi, [src_fhandle]
    mov rsi, buff
    mov rdx, 512
    opr 0, rdi, rsi, rdx  ; 0 is the syscall number for read
    test rax, rax
    jz close_files
    js exit_error
    mov [buff_len], rax

    ; Write to destination file
    mov rdi, [dst_fhandle]
    mov rsi, buff
    mov rdx, [buff_len]
    opr 1, rdi, rsi, rdx  ; 1 is the syscall number for write
    test rax, rax
    js exit_error

    jmp copy_loop

close_files:
    ; Close source file
    mov rdi, [src_fhandle]
    opr 3, rdi, 0, 0 ; 3 is the syscall number for close

    ; Close destination file
    mov rdi, [dst_fhandle]
    opr 3, rdi, 0, 0  ; 3 is the syscall number for close

    ; Delete source file
    opr 87, src_fname, 0, 0  ; 87 is the syscall number for unlink

    ; Exit the program
    opr 60, 0, 0, 0  ; 60 is the syscall number for exit

exit_error:
    ; Exit with error code
    opr 60, 1, 0, 0 ; 60 is the syscall number for exit