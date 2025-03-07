section .data
Num_Array db  1Fh,2Fh, 3Fh, 4Fh,5Fh             ; AX = AH=01, AL =3B

msg       db  "Result of array addition is", 10
msglen    equ $-msg

section .bss
Result  resw 1
temp    resw 1

%macro rw 4
   mov rax, %1
   mov rdi, %2
   mov rsi, %3
   mov rdx, %4
   syscall
%endmacro
section .text
    global _start
  _start:
       rw 1,1,msg,msglen                  
            mov rsi, Num_Array
            mov ax,  00h
	    mov bx, 00h
	    mov cx, 05h
up2: mov bl, byte[rsi] ; bl= 11h
  	    add ax, bx
	    jnc skip
	    inc ah
skip:	 
	    inc rsi
	    dec cx
	    jnz up2
                             
        mov word[Result], ax
        mov ax,           word[Result]
mov bp,     4
up: rol ax, 4
   	mov bx, ax
  	and ax, 0Fh
   	cmp al, 09
   	jbe down
    add al, 07h
   	down: Add al, 30h ; 38h =al
     mov byte[temp], al
     rw 1,1, temp,1 
     mov ax,         bx
     dec bp
     jnz up
rw 60,0,0,0
