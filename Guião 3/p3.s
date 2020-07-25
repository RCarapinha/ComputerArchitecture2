	.equ SFR_BASE_HI, 0xBF88
	.equ TRISE, 0x6100
	.equ PORTE, 0x6110
	.equ LATE, 0x6120
	.equ TRISB, 0x6040
	.equ PORTB, 0x6050
	.equ LATB, 0x6060
	.data
	.text
	.globl main
main:	lui $t0, SFR_BASE_HI

	lw $t1, TRISE($t0)
	lw $t2, TRISB($t0)
	andi $t1, $t1, 0xFFF0 #E->bit0,1,2 e 3 = 0 (OUTPUT)
	ori $t2, $t2, 0x000F  #B->bit0,1,2 e 3 = 1 (INPUT)
	sw $t1, TRISE($t0)
	sw $t2, TRISB($t0)
	
while:	lw $t2, PORTB($t0)
	xori $t2, $t2, 9
	sw $t2, LATE($t0)

	j while
	jr $ra
