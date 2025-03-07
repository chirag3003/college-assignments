section .data
    dirent_size equ 280  ; Size of struct dirent on x86_64
    newl db 10
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
    buffer resb dirent_size

section .text
global _start

_start:
    ; Get directory name from command line argument
    pop r8
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

    ; Open directory
    opr 257, -100, dir_name, 0  ; 257 is the syscall number for openat
    test rax, rax
    js exit_error
    mov rbx, rax  ; Save directory file descriptor

read_dir:
    ; Read directory entries
    opr 217, rbx, buffer, dirent_size  ; 217 is the syscall number for getdents64
    test rax, rax
    jz close_dir
    js exit_error

    ; Process each entry
    mov rcx, rax
    mov rsi, buffer
process_entry:
    cmp rcx, 0
    je read_dir
    mov rdx, rsi
    add rdx, 18  ; Offset of d_name in struct dirent
    cmp byte [rdx], 0
    je next_entry

    ; Print entry name
    mov rdi, 1  ; File descriptor for stdout
    mov rsi, rdx
    call print_string

next_entry:
    add rsi, dirent_size
    sub rcx, dirent_size
    jmp process_entry

close_dir:
    ; Close directory
    opr 3, rbx, 0, 0  ; 3 is the syscall number for close
    opr 60, 0, 0, 0  ; 60 is the syscall number for exit

exit_error:
    ; Exit with error code
    opr 60, 1, 0, 0  ; 60 is the syscall number for exit

print_string:
    ; Print string from rsi to rdi
    .print_loop:
        lodsb
        test al, al
        jz .print_newline
        mov rdx, 1
        opr 1, rdi, rsi, rdx  ; 1 is the syscall number for write
        jmp .print_loop
    .print_newline:
        mov rsi, newl
        mov rdx, newl_len
        opr 1, rdi, rsi, rdx  ; 1 is the syscall number for write
    ret