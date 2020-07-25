          .equ printStr, 8 
	  .equ readInt10, 5
	  .equ printInt, 6
	  .equ printInt10, 7
          .data 
          .text 
msg1:     .asciiz "\nIntroduza um numero (sinal e módulo):  "
msg2:     .asciiz "\nValor lido em base 2:  "
msg3:     .asciiz "\nValor lido em base 10 (unsigned):  "
msg4:     .asciiz "\nValor lido em base 10 (signed):  "
msg5:     .asciiz "\nValor lido em base 16:  "
          .globl main 
main:     
while:    beq $0,1,endwhile 
          
	  la $a0, msg1
	  ori $v0,$0,printStr
	  syscall
 	
          ori $v0,$0,readInt10
	  syscall
	  or $t0, $0, $v0

	  la $a0, msg2
	  ori $v0,$0,printStr
	  syscall

          or $a0, $t0, $0
	  li $a1, 2
	  ori $v0,$0,printStr
	  syscall

	  la $a0, msg5
	  ori $v0,$0,printStr
	  syscall

          or $a0, $t0, $0
	  li $a1, 16
	  ori $v0,$0,printStr
	  syscall

	  la $a0, msg3
	  ori $v0,$0,printStr
	  syscall

          or $a0, $t0, $0
	  li $a1, 10
	  ori $v0,$0,printStr
	  syscall

	  la $a0, msg4
	  ori $v0,$0,printStr
	  syscall

          or $a0, $t0, $0
	  ori $v0,$0,printInt10
	  syscall
	  j while
endwhile: jr     $ra 
