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
    opr 2, src_fname, 0, 0 ; open(src_fname, O_RDONLY)
    mov [src_fhandle], rax
    mov rbx, rax

    ; Create destination file
    opr 2, dst_fname, 577, 0666q ; open(dst_fname, O_WRONLY | O_CREAT | O_TRUNC, 0666)
    mov [dst_fhandle], rax
    mov rcx, rax

    ; Read from source and write to destination
    read_write:
        opr 0, [src_fhandle], buff, 512 ; read(src_fhandle, buff, 512)
        test rax, rax
        jz close_files
        mov rdx, rax
        opr 1, [dst_fhandle], buff, rdx ; write(dst_fhandle, buff, rdx)
        jmp read_write

    close_files:
        ; Close source file
        opr 3, [src_fhandle], 0, 0 ; close(src_fhandle)
        ; Close destination file
        opr 3, [dst_fhandle], 0, 0 ; close(dst_fhandle)
        ; Exit
        opr 60, 0, 0, 0 ; exit