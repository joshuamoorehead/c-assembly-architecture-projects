.data #can declare numbers before main
	test: .asciiz "Hello, World!"
	newLine: .asciiz "\n"
	userprompt: .asciiz "Type in a number"

.text
	li $v0, 4
	la $a0, test
	syscall
	#print newline
	
	li $v0, 4 #pseudocode for add
	la $a0, newLine
	syscall
	la $a0, userprompt
	syscall

	#get input from user
	
	la $v0, 5 #la is pseudocode for addi
	
	syscall
	
	#move user input into real register
	
	li $s0, $v0