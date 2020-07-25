          .equ print_str,8 
	  .equ inkey,1
          .data 
          .text 
msg:      .asciiz "Key Pressed\n" 
          .globl main 
main:     
while:    beq $0,1,endwhile 
	  ori $v0,$0,inkey
	  syscall
	  or $a0, $v0, $0
if:       beq $a0, '\n', endwhile
	  la $a0,msg   
	  ori $v0,$0,print_str
	  syscall
	  j while
endwhile: jr     $ra 
