.data
	prompt: .asciiz "Enter a number: "
	newline: .asciiz "\n"
	message: .asciiz "Your number will be multiplied by 2."
	message2: .asciiz "Your new number is: "
	
	 	
.text

	#for loop. printing through 10
	li $s0, 10 #i < 10
	li $t0, 0 #i
loop: 
	beq $t0, $s0, quit
	#hoskins checks if loop works before code
	li $v0, 1
	move $a0, $t0
	syscall
	
	li $v0, 4
	la $a0, newline
	syscall
	
	addi $t0, $t0, 1
	j loop


quit:
	#just label to leave
















	li $v0, 4
	la $a0, prompt
	syscall
	
	#reading input
	li $v0, 5
	syscall
	move $t0, $v0
	
	#second message
	
	li $v0, 4
	la $a0, message
	syscall
	
	li $v0, 4
	la $a0, newline
	syscall
	
	li $v0, 4
	la $a0, message2
	syscall
	
	sll $t0, $t0, 1 #shifting by 1 left to multiply number
	
	li $v0, 1
	move $a0, $t0
	syscall
	j exit
	
exit: 
	li $v0, 10
	syscall
	
