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
	andi $t1, $t1, 0xFFFE #bit0 = 0
	ori $t2, $t2, 1       #bit0 = 1
	sw $t1, TRISE($t0)
	sw $t2, TRISB($t0)
	
while:lw $t2, PORTB($t0)
	not $t2
	sw $t2, LATE($t0)

	j while
	jr $ra
