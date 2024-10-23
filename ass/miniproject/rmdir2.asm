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
    path resb 512

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

    ; Call recursive delete function
    mov rdi, dir_name
    call delete_dir

    ; Exit the program
    opr 60, 0, 0,0 ; 60 is the syscall number for exit

delete_dir:
    ; Open directory
    opr 257, rdi, 0, 0  ; 257 is the syscall number for openat
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
    lea rdx, [rsi+18]  ; Offset of d_name in struct dirent
    cmp byte [rdx], 0
    je next_entry
        cmp byte [rdx], '.'
        je check_double_dot
        jmp process_entry
    
    check_double_dot:
        cmp byte [rdx+1], 0
        je skip_entry
        cmp byte [rdx+1], '.'
        je skip_entry

    ; Construct full path
    mov rdi, path
    mov rsi, dir_name
    call strcpy
    mov rsi, rdx
    call strcat

    ; Check if entry is a directory
    movzx rax, byte [rsi+16]  ; Offset of d_type in struct dirent
    test rax, rax
    jz next_entry
    cmp rax, 4  ; DT_DIR
    je recurse_dir

    ; Delete file
    opr 87, path, 0, 0  ; 87 is the syscall number for unlink
    jmp next_entry

recurse_dir:
    ; Recursively delete subdirectory
    mov rdi, path
    call delete_dir

    ; Delete empty directory
    opr 84, path, 0, 0  ; 84 is the syscall number for rmdir

next_entry:
    add rsi, dirent_size
    sub rcx, dirent_size
    jmp process_entry

skip_entry:
    add rsi, dirent_size
    sub rcx, dirent_size
    jmp process_entry
 
close_dir:
    ; Close directory
    opr 3, rbx, 0, 0  ; 3 is the syscall number for close
    ret

exit_error:
    ; Exit with error code
    opr 60, 1, 0, 0  ; 60 is the syscall number for exit

strcpy:
    ; Copy string from rsi to rdi
    .copy_loop:
        lodsb
        stosb
        test al, al
        jnz .copy_loop
    ret

strcat:
    ; Concatenate string from rsi to rdi
    .find_end:
        lodsb
        test al, al
        jnz .find_end
    dec rdi
    .concat_loop:
        lodsb
        stosb
        test al, al
        jnz .concat_loop
    ret