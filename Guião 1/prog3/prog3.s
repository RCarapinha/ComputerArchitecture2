          .equ putChar,3 
	  .equ getChar,2
          .data 
          .text 
          .globl main 
main:     
while:    beq $0,1,endwhile 
	  ori $v0,$0,getChar
	  syscall
	  or $a0, $v0, $0
if:       beq $a0, '\n', endwhile   
	  ori $v0,$0,putChar
	  syscall
	  j while
endwhile: jr     $ra 
