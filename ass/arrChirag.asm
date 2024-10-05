


section .data
Num_array db 11h,12h,13h,14h,15h

msg db"result of array addition is ", 10
msglen equ $-msg


section .bss

result  resw 1
temp    resw 1


%macro rw 4
  mov rax, %1
  mov rdi, %2
  mov rsi, %3
  mov rdx, %4
  syscall
  %endmacro



section .text
global  _start
_start:
rw 1,1,msg,msglen
  mov rsi, Num_array
  mov ax,  00h
  mov bx,  00h
  mov cx,  5
  
  up2:mov bl, byte[rsi]
      add ax, bx
      jnc skip
      inc ah
        skip:
        inc rsi
        dec cx
        jnz up2
          mov word[result], ax
          
          
          
          mov    ax, word[result]
          mov    bp, 4
          up:rol ax, 4
            mov bx, ax
            and ax, 0fh
            cmp al, 09
            jbe down
               add   al,         07h
               down: Add al,     30h
               mov   byte[temp], al
               rw 1,1,temp,1
               mov   ax,         bx
               dec   bp
               jnz   up
               rw 60,0,0,0
          
          
          
          
          
          
          
          
          
  
