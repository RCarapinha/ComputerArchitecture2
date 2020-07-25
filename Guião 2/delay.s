          .equ READ_CORE_TIMER,11 
          .equ RESET_CORE_TIMER,12 
          .equ PUT_CHAR,3 
          .equ GET_CHAR,2
          .equ PRINT_INT,6 
          .data 
          .text 
          .globl  main 
main:     li $v0, GET_CHAR
          syscall
	  move $a0, $v0
          li $v0, PUT_CHAR
	  syscall 
          li $t1, 20000000
          div $t1, $a0
          mflo $t1
while:    li $v0,READ_CORE_TIMER 
          syscall                  
          bge $v0,$t1,endwhile
          li $v0,RESET_CORE_TIMER
          syscall 
          li $a0,' '              
          li $v0,PUT_CHAR         
          syscall                      
          addi $t0,$t0,1            
          move $a0,$t0              
          li $a1,10               
          li $v0,PRINT_INT        
          syscall                      
       	  j while                  
endwhile: jr $ra                  
